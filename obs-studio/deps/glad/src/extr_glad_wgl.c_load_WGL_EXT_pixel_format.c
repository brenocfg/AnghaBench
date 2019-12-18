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
typedef  scalar_t__ PFNWGLGETPIXELFORMATATTRIBIVEXTPROC ;
typedef  scalar_t__ PFNWGLGETPIXELFORMATATTRIBFVEXTPROC ;
typedef  scalar_t__ PFNWGLCHOOSEPIXELFORMATEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_WGL_EXT_pixel_format ; 
 scalar_t__ glad_wglChoosePixelFormatEXT ; 
 scalar_t__ glad_wglGetPixelFormatAttribfvEXT ; 
 scalar_t__ glad_wglGetPixelFormatAttribivEXT ; 

__attribute__((used)) static void load_WGL_EXT_pixel_format(GLADloadproc load) {
	if(!GLAD_WGL_EXT_pixel_format) return;
	glad_wglGetPixelFormatAttribivEXT = (PFNWGLGETPIXELFORMATATTRIBIVEXTPROC)load("wglGetPixelFormatAttribivEXT");
	glad_wglGetPixelFormatAttribfvEXT = (PFNWGLGETPIXELFORMATATTRIBFVEXTPROC)load("wglGetPixelFormatAttribfvEXT");
	glad_wglChoosePixelFormatEXT = (PFNWGLCHOOSEPIXELFORMATEXTPROC)load("wglChoosePixelFormatEXT");
}