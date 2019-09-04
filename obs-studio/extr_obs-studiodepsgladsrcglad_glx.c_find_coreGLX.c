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
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/ * GLADGLXDisplay ; 
 int GLADGLXscreen ; 
 int GLAD_GLX_VERSION_1_0 ; 
 int GLAD_GLX_VERSION_1_1 ; 
 int GLAD_GLX_VERSION_1_2 ; 
 int GLAD_GLX_VERSION_1_3 ; 
 int GLAD_GLX_VERSION_1_4 ; 
 int /*<<< orphan*/  XDefaultScreenOfDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XOpenDisplay (int /*<<< orphan*/ ) ; 
 int XScreenNumberOfScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glXQueryVersion (int /*<<< orphan*/ *,int*,int*) ; 

__attribute__((used)) static void find_coreGLX(Display *dpy, int screen) {
	int major = 0, minor = 0;
	if(dpy == 0 && GLADGLXDisplay == 0) {
		dpy = XOpenDisplay(0);
		screen = XScreenNumberOfScreen(XDefaultScreenOfDisplay(dpy));
	} else if(dpy == 0) {
		dpy = GLADGLXDisplay;
		screen = GLADGLXscreen;
	}
	glXQueryVersion(dpy, &major, &minor);
	GLADGLXDisplay = dpy;
	GLADGLXscreen = screen;
	GLAD_GLX_VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
	GLAD_GLX_VERSION_1_1 = (major == 1 && minor >= 1) || major > 1;
	GLAD_GLX_VERSION_1_2 = (major == 1 && minor >= 2) || major > 1;
	GLAD_GLX_VERSION_1_3 = (major == 1 && minor >= 3) || major > 1;
	GLAD_GLX_VERSION_1_4 = (major == 1 && minor >= 4) || major > 1;
}