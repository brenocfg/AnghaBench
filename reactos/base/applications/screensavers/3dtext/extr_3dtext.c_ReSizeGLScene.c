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
typedef  int GLsizei ;
typedef  int GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  GL_MODELVIEW ; 
 int /*<<< orphan*/  GL_PROJECTION ; 
 int /*<<< orphan*/  glLoadIdentity () ; 
 int /*<<< orphan*/  glMatrixMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gluPerspective (float,int,float,float) ; 

GLvoid ReSizeGLScene(GLsizei Width, GLsizei Height)	
{
    // Is Window Too Small (Divide By Zero Error)
    if (Height == 0)
    {
        // If So Make It One Pixel Tall
        Height = 1;
    }

    // Reset The Current Viewport And Perspective Transformation
    glViewport(0, 0, Width, Height);

    // Select The Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset The Projection Matrix
    glLoadIdentity();

    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f, (GLfloat)Width / (GLfloat)Height, 0.1f, 100.0f);

    // Select The Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
}