#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GLvoid ;
typedef  scalar_t__ GLsizei ;
typedef  int GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  BuildFont () ; 
 int /*<<< orphan*/  GL_COLOR_MATERIAL ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_LESS ; 
 int /*<<< orphan*/  GL_LIGHT0 ; 
 int /*<<< orphan*/  GL_LIGHTING ; 
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  GL_SMOOTH ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glClearDepth (double) ; 
 int /*<<< orphan*/  glDepthFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glShadeModel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gluPerspective (float,int,float,float) ; 

GLvoid InitGL(GLsizei Width, GLsizei Height)
{
    // Clear The Background Color To Black
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Enables Clearing Of The Depth Buffer
    glClearDepth(1.0);

    // The Type Of Depth Test To Do
    glDepthFunc(GL_LESS);

    // Enables Depth Testing
    glEnable(GL_DEPTH_TEST);

    // Enables Smooth Color Shading
    glShadeModel(GL_SMOOTH);

    // Select The Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset The Projection Matrix
    glLoadIdentity();

    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 100.0f);

    // Select The Modelview Matrix
    glMatrixMode(GL_MODELVIEW);

    // Build The Font
    BuildFont();

    // Enable Default Light (Quick And Dirty)
    glEnable(GL_LIGHT0);

    // Enable Lighting
    glEnable(GL_LIGHTING);

    // Enable Coloring Of Material
    glEnable(GL_COLOR_MATERIAL);
}