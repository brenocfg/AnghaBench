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
typedef  scalar_t__ PFNGLXWAITXPROC ;
typedef  scalar_t__ PFNGLXWAITGLPROC ;
typedef  scalar_t__ PFNGLXUSEXFONTPROC ;
typedef  scalar_t__ PFNGLXSWAPBUFFERSPROC ;
typedef  scalar_t__ PFNGLXQUERYVERSIONPROC ;
typedef  scalar_t__ PFNGLXQUERYEXTENSIONPROC ;
typedef  scalar_t__ PFNGLXMAKECURRENTPROC ;
typedef  scalar_t__ PFNGLXISDIRECTPROC ;
typedef  scalar_t__ PFNGLXGETCURRENTDRAWABLEPROC ;
typedef  scalar_t__ PFNGLXGETCURRENTCONTEXTPROC ;
typedef  scalar_t__ PFNGLXGETCONFIGPROC ;
typedef  scalar_t__ PFNGLXDESTROYGLXPIXMAPPROC ;
typedef  scalar_t__ PFNGLXDESTROYCONTEXTPROC ;
typedef  scalar_t__ PFNGLXCREATEGLXPIXMAPPROC ;
typedef  scalar_t__ PFNGLXCREATECONTEXTPROC ;
typedef  scalar_t__ PFNGLXCOPYCONTEXTPROC ;
typedef  scalar_t__ PFNGLXCHOOSEVISUALPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GLX_VERSION_1_0 ; 
 scalar_t__ glad_glXChooseVisual ; 
 scalar_t__ glad_glXCopyContext ; 
 scalar_t__ glad_glXCreateContext ; 
 scalar_t__ glad_glXCreateGLXPixmap ; 
 scalar_t__ glad_glXDestroyContext ; 
 scalar_t__ glad_glXDestroyGLXPixmap ; 
 scalar_t__ glad_glXGetConfig ; 
 scalar_t__ glad_glXGetCurrentContext ; 
 scalar_t__ glad_glXGetCurrentDrawable ; 
 scalar_t__ glad_glXIsDirect ; 
 scalar_t__ glad_glXMakeCurrent ; 
 scalar_t__ glad_glXQueryExtension ; 
 scalar_t__ glad_glXQueryVersion ; 
 scalar_t__ glad_glXSwapBuffers ; 
 scalar_t__ glad_glXUseXFont ; 
 scalar_t__ glad_glXWaitGL ; 
 scalar_t__ glad_glXWaitX ; 

__attribute__((used)) static void load_GLX_VERSION_1_0(GLADloadproc load) {
	if(!GLAD_GLX_VERSION_1_0) return;
	glad_glXChooseVisual = (PFNGLXCHOOSEVISUALPROC)load("glXChooseVisual");
	glad_glXCreateContext = (PFNGLXCREATECONTEXTPROC)load("glXCreateContext");
	glad_glXDestroyContext = (PFNGLXDESTROYCONTEXTPROC)load("glXDestroyContext");
	glad_glXMakeCurrent = (PFNGLXMAKECURRENTPROC)load("glXMakeCurrent");
	glad_glXCopyContext = (PFNGLXCOPYCONTEXTPROC)load("glXCopyContext");
	glad_glXSwapBuffers = (PFNGLXSWAPBUFFERSPROC)load("glXSwapBuffers");
	glad_glXCreateGLXPixmap = (PFNGLXCREATEGLXPIXMAPPROC)load("glXCreateGLXPixmap");
	glad_glXDestroyGLXPixmap = (PFNGLXDESTROYGLXPIXMAPPROC)load("glXDestroyGLXPixmap");
	glad_glXQueryExtension = (PFNGLXQUERYEXTENSIONPROC)load("glXQueryExtension");
	glad_glXQueryVersion = (PFNGLXQUERYVERSIONPROC)load("glXQueryVersion");
	glad_glXIsDirect = (PFNGLXISDIRECTPROC)load("glXIsDirect");
	glad_glXGetConfig = (PFNGLXGETCONFIGPROC)load("glXGetConfig");
	glad_glXGetCurrentContext = (PFNGLXGETCURRENTCONTEXTPROC)load("glXGetCurrentContext");
	glad_glXGetCurrentDrawable = (PFNGLXGETCURRENTDRAWABLEPROC)load("glXGetCurrentDrawable");
	glad_glXWaitGL = (PFNGLXWAITGLPROC)load("glXWaitGL");
	glad_glXWaitX = (PFNGLXWAITXPROC)load("glXWaitX");
	glad_glXUseXFont = (PFNGLXUSEXFONTPROC)load("glXUseXFont");
}