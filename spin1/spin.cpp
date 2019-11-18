#include<GL/glut.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<sstream>

// Rotation angle and speed variables
GLfloat spinnerAngle;
GLfloat spinnerSpeed = 0.0f;
GLfloat scale = 1.0;
char snum[5];

GLfloat spinner[][3] = {
	{0.0,0.0,0.0},{-0.25,-0.2,0.0},{-1.0,0.0,0.0},{-0.25,0.2,0.0},
	{-0.2,0.25,0.0},{0.0,1.0,0.0},{0.2,0.25,0.0},{0.25,0.2,0.0},
	{1.0,0.0,0.0},{0.25,-0.2,0.0},{0.2,-0.25,0.0},{0.0,-1.0,0.0},
	{-0.2,-0.25,0.0},
	{0.0,0.03,0},{0.02,0.02,0},{0.03,0.0,0.0},{0.02,-0.02,0.0},
	{0.0,-0.03,0.0},{-0.02,-0.02,0},{-0.03,0.0,0.0},{-0.02,-0.02,0.0},{1.0,-1.0,0.0}
};

// Spinner Stick coordinates
GLfloat stick[][3] = {
	{-0.03,0.03,0.0},
	{0.03,0.03,0.0},
	{0.03,-2.0,0.0},
	{-0.03,-2.0,0.0}
};

void typecast();
float d2rgb(float);
void output(int,int,float,float,float,void*, char*);
void draw_leaf(int,int,int);
void draw_leaf_shade(int,int,int);
void draw_spinner_hole();
void draw_stick();
void draw_spinner();
void keyboard(unsigned char,int,int);
void display(void);

// Converts spinnerSpeed into RPMs
void typecast() 
{ 
    float num = spinnerSpeed; 
	if(num==0.0)
	{
		num=0.0;
		itoa(num, snum, 10);
	}
	else
	{
	    num*=10;
	    itoa(num, snum, 10);
	}
} 

// Converts decimal to RGB
float d2rgb(float rgbcolor)
{
	return rgbcolor*(1.0/255.0);
}

void output(int x, int y, float r, float g, float b,void* font, char *string)
{
  glColor3f( r, g, b );
  glRasterPos2f(x, y);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font,string[i]);
	  
  }
}

// Draws a leaf
void draw_leaf(int a, int b, int c)
{
	glBegin(GL_POLYGON);
	glVertex3fv(spinner[a]);
	glVertex3fv(spinner[b]);
	glVertex3fv(spinner[c]);
	glEnd();
}

// Draws a leaf shade
void draw_leaf_shade(int a, int b, int c)
{
	glBegin(GL_POLYGON);
	glVertex3fv(spinner[a]);
	glVertex3fv(spinner[b]);
	glVertex3fv(spinner[c]);
	glEnd();
}

// Draws spinner hole
void draw_spinner_hole()
{
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3fv(spinner[13]);
	glVertex3fv(spinner[14]);
	glVertex3fv(spinner[15]);
	glVertex3fv(spinner[16]);
	glVertex3fv(spinner[17]);
	glVertex3fv(spinner[18]);
	glVertex3fv(spinner[19]);
	glVertex3fv(spinner[20]);
	glEnd();
}

// Draws spinner stick
void draw_stick()
{
	glColor3f(d2rgb(196),d2rgb(167),d2rgb(141));
	glBegin(GL_POLYGON);
	glVertex3fv(stick[0]);
	glVertex3fv(stick[1]);
	glVertex3fv(stick[2]);
	glVertex3fv(stick[3]);
	glEnd();
}

// Draws spinner
void draw_spinner()
{
	// Draws hole
	draw_spinner_hole();

	// Leaf 1 - Top-Left
	glColor3f(d2rgb(255),d2rgb(152),d2rgb(0));
	draw_leaf_shade(0,4,5);
	glColor3f(d2rgb(255.0),d2rgb(188.0),d2rgb(0.0));
	draw_leaf(0,6,5);

	// Leaf 2 - Top-Right
	glColor3f(d2rgb(173),d2rgb(20),d2rgb(87));
	draw_leaf_shade(0,7,8);
	glColor3f(d2rgb(219.0),d2rgb(68.0),d2rgb(55.0));
	draw_leaf(0,9,8);
	
	// Leaf 3 - Bottom-Right
	glColor3f(d2rgb(51),d2rgb(102),d2rgb(211));
	draw_leaf_shade(0,10,11);
	glColor3f(d2rgb(66.0),d2rgb(133.0),d2rgb(244.0));
	draw_leaf(0,12,11);
	
	// Leaf 4 - Bottom-Left
	glColor3f(d2rgb(15),d2rgb(157),d2rgb(88));
	draw_leaf_shade(0,1,2);
	glColor3f(d2rgb(139.0),d2rgb(195.0),d2rgb(74.0));
	draw_leaf(0,3,2);

	glColor3f(d2rgb(255),d2rgb(152),d2rgb(0));
	draw_leaf_shade(9,10,21);
}

// Display function
void display(void)
{
	typecast();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	char str[100] = "CONTROLLED SPINNER RPM:";
	strcat(str,snum);
	output(0.0,1.3,0.0,1.0,0.0,GLUT_BITMAP_9_BY_15,str);
	glLoadIdentity();
	glPushMatrix();
	glScalef(scale, scale, scale);

	glTranslatef(0.0f,0.0f,0.0f); 
	glRotatef(spinnerAngle,0.0f,0.0f,1.0f);
	draw_spinner();
	glLoadIdentity();  
	glScalef(scale, scale, scale);

	draw_stick();
	spinnerAngle-=spinnerSpeed;
	glPopMatrix();
	glutPostRedisplay();
	glFlush();
	glutSwapBuffers();
}

// Reshape function
void myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-2,2,-2*(GLfloat)h/(GLfloat)w,2*(GLfloat)h/(GLfloat)w,-10,10);
	else
		glOrtho(-2,2,-2*(GLfloat)w/(GLfloat)h,2*(GLfloat)w/(GLfloat)h,-10,10);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

// Keyboard Controls
void keyboard(unsigned char key,int x, int y)
{
	if(spinnerSpeed==0)
		spinnerSpeed=0;
	if(key=='a')
		spinnerSpeed-=0.5f;
	if(key=='d')
		spinnerSpeed+=0.5f;
	if(key=='s') 
		spinnerSpeed=0.0f;
	if(key=='x') 
		scale+=0.02f;
	if(key=='z') 
		scale-=0.02f;
	display();
}

// Main function
int main(int argc, char **argv)
{
	printf("\t\t\t\t K.L.E INSTITUTE OF TECHNOLOGY\n");
	printf("\t\t\tDepartment of Computer Science and Engineering\n");
	printf("\t\t\t\t  Hubli, Karnataka - 580030\n\n\n");
	printf("\t\t\t\t   CONTROLLED SPINNER\n\n");
	printf("\t    A Mini Project for Computer Graphics and Visualization Laboratory\n\n");
    printf("\t\t\t Suraj M Janmane\t2KE16CS049\n\t\t\t Swaroop Mogali\t \t2KE16CS050\n\n");
	printf("\nKeyboard Controls: \n D : Speeds up spinning \n S : Stops spinning \n A : Slows down spinning and reverse spinning \n X : Zoom In \n Z : Zoom Out\n ");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(800,800);
	glutCreateWindow("Wind Spinner");
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutReshapeFunc(myReshape);
	glClearColor(d2rgb(28),d2rgb(8),d2rgb(12),1.0);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}