//
//  Game.cpp
//  2nd_pgm
//
//  Created by Dizhu Zheng on 6/27/17.
//  Copyright © 2017 Dizhu. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include<iostream>

class Game
{
public:
    Game();
    void run();
    
private:
    void processEvents();
    void handlePlayerInput(sf::Keyboard:: Key, bool);
    void update(sf::Time);
    void render();
    sf::Texture mTexture;
    sf::Sprite mPlayer;
    sf:: RenderWindow mWindow;
    //   sf::CircleShape mPlayer;
    const sf::Time TimePerFrame = sf::seconds(1.f/60.f);
    bool mIsMovingUp = false;
    bool mIsMovingDown = false;
    bool mIsMovingLeft = false;
    bool mIsMovingRight = false;
};

Game::Game(): mWindow(sf::VideoMode(840,680), "SFML Application"), mTexture(), mPlayer()
{
    //    mPlayer.setRadius(40.f);
    //    mPlayer.setPosition(100.f,100.f);
    //    mPlayer.setFillColor(sf::Color::Cyan);
    
    if(!mTexture.loadFromFile("spaceship.png"))
    {
        std::cout<<" Coudn't open the path."<<std::endl;
    }
    
    mPlayer.setTextureRect(sf::IntRect(20, 20, 400, 400));
    mPlayer.setTexture(mTexture);
    mPlayer.setPosition(100.f,100.f);
}

void Game::run()
{
    sf::Clock clock;
    sf:: Time timeSinceLastUpdate = sf::Time::Zero;
    
    while(mWindow.isOpen())
    {
        processEvents();//pro events cost different time
        timeSinceLastUpdate += clock.restart();
        
        while(timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        //      update(deltaTime);//so this differs, we need a fixed time tech
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code,true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code,false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    sf::Vector2f movement(0.f,0.f);
    if(mIsMovingDown)
        movement.y += 1.f;
    if(mIsMovingUp)
        movement.y -= 1.f;
    if(mIsMovingLeft)
        movement.x -= 1.f;
    if(mIsMovingRight)
        movement.x += 1.f;
    
    float speed = 800;
    mPlayer.move(movement * speed * deltaTime.asSeconds());
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::W)
        mIsMovingUp = isPressed;
    else if (key == sf:: Keyboard::A)
        mIsMovingLeft = isPressed;
    else if(key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    else if(key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
}

void printStuff(){
    std::cout <<"Hello, World!" << std::endl;
}

int main()
{
    printStuff();
    Game game;
    game.run();
}

