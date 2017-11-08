

#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include <iostream>

float angle = 0.0;
float G=1;
float colors[9][2]={{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0},{1,0}};
int movement = 0;
bool used[9]={false,false,false,false,false,false,false,false,false};
bool player1[9]={false,false,false,false,false,false,false,false,false};
bool player2[9]={false,false,false,false,false,false,false,false,false};
bool game=true;
int winResults[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{6,4,2}};



bool checkPlayer2(int winResults[][3] , bool player[]){
    int counter=0;
    for(int x=0;x<8;x++){
        counter=0;
        for(int z=0;z<3;z++){
            if(player[winResults[x][z]] == true){
                counter++;
            }
        }
        if(counter == 3){
            return true;
        }
    }
    return false;
}

void DrawCube()
{
		glBegin(GL_QUADS);			// top face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
		glEnd();
		glBegin(GL_QUADS);			// front face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
		glEnd();
		glBegin(GL_QUADS);			// right face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();
		glBegin(GL_QUADS);			// left face
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
		glEnd();
		glBegin(GL_QUADS);			// bottom face
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
		glEnd();
		glBegin(GL_QUADS);			// back face
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();
}


void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,0,-5);
	glPushMatrix();
        glColor3f(colors[4][0],colors[4][1],0);
        DrawCube();
    glPopMatrix();
    glPushMatrix();
        glColor3f(colors[5][0],colors[5][1],0);
        glTranslatef(1.2,0,0);
        DrawCube();
    glPopMatrix();
    glPushMatrix();
        glColor3f(colors[2][0],colors[2][1],0);
        glTranslatef(1.2,1.2,0);
        DrawCube();
    glPopMatrix();
    glPushMatrix();
        glColor3f(colors[1][0],colors[1][1],0);
        glTranslatef(0,1.2,0);
        DrawCube();
    glPopMatrix();
    glPushMatrix();
        glColor3f(colors[3][0],colors[3][1],0);
        glTranslatef(-1.2,0,0);
        DrawCube();
    glPopMatrix();
    glPushMatrix();
        glColor3f(colors[8][0],colors[8][1],0);
        glTranslatef(1.2,-1.2,0);
        DrawCube();
    glPopMatrix();
    glPushMatrix();
        glColor3f(colors[7][0],colors[7][1],0);
        glTranslatef(0,-1.2,0);
        DrawCube();
    glPopMatrix();
    glPushMatrix();
        glColor3f(colors[0][0],colors[0][1],0);
        glTranslatef(-1.2,1.2,0);
        DrawCube();
    glPopMatrix();
    glPushMatrix();
        glColor3f(colors[6][0],colors[6][1],0);
        glTranslatef(-1.2,-1.2,0);
        DrawCube();
    glPopMatrix();

}


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    int loop=1;
    SDL_Event myevent;
    init();
    while (loop==1)
    {
        while (SDL_PollEvent(&myevent))
        {
            if(checkPlayer2(winResults,player1)){
                movement = 100;
                for(int x=0;x<9;x++){
                    colors[x][0]=1;
                    colors[x][1]=1;
                }
            }else if(checkPlayer2(winResults , player2)){
                movement = 100;
                for(int x=0;x<9;x++){
                    colors[x][0]=0.5;
                    colors[x][1]=1;
                }
            }
            switch(myevent.type)
            {
                case SDL_QUIT:
                loop=0;
                break;

                case SDL_KEYDOWN:
                //if (myevent.key.keysym.sym==SDLK_SPACE) angle+=30;
                if(movement<=9 && game==true){
                    switch(myevent.key.keysym.sym){
                    case SDLK_1:
                        if(used[0]!=true){
                            colors[0][1]=1;
                            movement++;
                            used[0]=true;
                            player1[0]=true;
                        }
                        break;
                    case SDLK_2:
                        if(used[1]!=true){
                            colors[1][1]=1;
                            movement++;
                            used[1]=true;
                            player1[1]=true;
                        }
                        break;
                    case SDLK_3:
                        if(used[2]!=true){
                            colors[2][1]=1;
                            movement++;
                            used[2]=true;
                            player1[2]=true;
                        }
                        break;
                    case SDLK_4:
                        if(used[3]!=true){
                            colors[3][1]=1;
                            movement++;
                            used[3]=true;
                            player1[3]=true;
                        }
                        break;
                    case SDLK_5:
                        if(used[4]!=true){
                            colors[4][1]=1;
                            movement++;
                            used[4]=true;
                            player1[4]=true;
                        }
                        break;
                    case SDLK_6:
                        if(used[5]!=true){
                            colors[5][1]=1;
                            movement++;
                            used[5]=true;
                            player1[5]=true;
                        }
                        break;
                    case SDLK_7:
                        if(used[6]!=true){
                            colors[6][1]=1;
                            movement++;
                            used[6]=true;
                            player1[6]=true;
                        }
                        break;
                    case SDLK_8:
                        if(used[7]!=true){
                            colors[7][1]=1;
                            movement++;
                            used[7]=true;
                            player1[7]=true;
                        }
                        break;
                    case SDLK_9:
                        if(used[8]!=true){
                            colors[8][1]=1;
                            movement++;
                            used[8]=true;
                            player1[8]=true;
                        }
                        break;

                    case SDLK_KP1:
                        if(used[0]!=true){
                            colors[0][1]=1;
                            colors[0][0]=0.5;
                            movement++;
                            used[0]=true;
                            player2[0]=true;
                        }
                        break;
                    case SDLK_KP2:
                        if(used[1]!=true){
                            colors[1][1]=1;
                            colors[1][0]=0.5;
                            movement++;
                            used[1]=true;
                            player2[1]=true;
                        }
                        break;
                    case SDLK_KP3:
                        if(used[2]!=true){
                            colors[2][1]=1;
                            colors[2][0]=0.5;
                            movement++;
                            used[2]=true;
                            player2[2]=true;
                        }
                        break;
                    case SDLK_KP4:
                        if(used[3]!=true){
                            colors[3][1]=1;
                            colors[3][0]=0.5;
                            movement++;
                            used[3]=true;
                            player2[3]=true;
                        }
                        break;
                    case SDLK_KP5:
                        if(used[4]!=true){
                            colors[4][1]=1;
                            colors[4][0]=0.5;
                            movement++;
                            used[4]=true;
                            player2[4]=true;
                        }
                        break;
                    case SDLK_KP6:
                        if(used[5]!=true){
                            colors[5][1]=1;
                            colors[5][0]=0.5;
                            movement++;
                            used[5]=true;
                            player2[5]=true;
                        }
                        break;
                    case SDLK_KP7:
                        if(used[6]!=true){
                            colors[6][1]=1;
                            colors[6][0]=0.5;
                            movement++;
                            used[6]=true;
                            player2[6]=true;
                        }
                        break;
                    case SDLK_KP8:
                        if(used[7]!=true){
                            colors[7][1]=1;
                            colors[7][0]=0.5;
                            movement++;
                            used[7]=true;
                            player2[7]=true;
                        }
                        break;
                    case SDLK_KP9:
                        if(used[8]!=true){
                            colors[8][1]=1;
                            colors[8][0]=0.5;
                            movement++;
                            used[8]=true;
                            player2[8]=true;
                        }

                    }
                }
                break;
            }
        }
        display();
        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
    return 0;
}
