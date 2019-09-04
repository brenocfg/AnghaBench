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
typedef  scalar_t__ PFNWGLLOADDISPLAYCOLORTABLEEXTPROC ;
typedef  scalar_t__ PFNWGLDESTROYDISPLAYCOLORTABLEEXTPROC ;
typedef  scalar_t__ PFNWGLCREATEDISPLAYCOLORTABLEEXTPROC ;
typedef  scalar_t__ PFNWGLBINDDISPLAYCOLORTABLEEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_WGL_EXT_display_color_table ; 
 scalar_t__ glad_wglBindDisplayColorTableEXT ; 
 scalar_t__ glad_wglCreateDisplayColorTableEXT ; 
 scalar_t__ glad_wglDestroyDisplayColorTableEXT ; 
 scalar_t__ glad_wglLoadDisplayColorTableEXT ; 

__attribute__((used)) static void load_WGL_EXT_display_color_table(GLADloadproc load) {
	if(!GLAD_WGL_EXT_display_color_table) return;
	glad_wglCreateDisplayColorTableEXT = (PFNWGLCREATEDISPLAYCOLORTABLEEXTPROC)load("wglCreateDisplayColorTableEXT");
	glad_wglLoadDisplayColorTableEXT = (PFNWGLLOADDISPLAYCOLORTABLEEXTPROC)load("wglLoadDisplayColorTableEXT");
	glad_wglBindDisplayColorTableEXT = (PFNWGLBINDDISPLAYCOLORTABLEEXTPROC)load("wglBindDisplayColorTableEXT");
	glad_wglDestroyDisplayColorTableEXT = (PFNWGLDESTROYDISPLAYCOLORTABLEEXTPROC)load("wglDestroyDisplayColorTableEXT");
}