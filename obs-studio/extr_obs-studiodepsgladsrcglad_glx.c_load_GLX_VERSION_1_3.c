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
typedef  scalar_t__ PFNGLXSELECTEVENTPROC ;
typedef  scalar_t__ PFNGLXQUERYDRAWABLEPROC ;
typedef  scalar_t__ PFNGLXQUERYCONTEXTPROC ;
typedef  scalar_t__ PFNGLXMAKECONTEXTCURRENTPROC ;
typedef  scalar_t__ PFNGLXGETVISUALFROMFBCONFIGPROC ;
typedef  scalar_t__ PFNGLXGETSELECTEDEVENTPROC ;
typedef  scalar_t__ PFNGLXGETFBCONFIGSPROC ;
typedef  scalar_t__ PFNGLXGETFBCONFIGATTRIBPROC ;
typedef  scalar_t__ PFNGLXGETCURRENTREADDRAWABLEPROC ;
typedef  scalar_t__ PFNGLXDESTROYWINDOWPROC ;
typedef  scalar_t__ PFNGLXDESTROYPIXMAPPROC ;
typedef  scalar_t__ PFNGLXDESTROYPBUFFERPROC ;
typedef  scalar_t__ PFNGLXCREATEWINDOWPROC ;
typedef  scalar_t__ PFNGLXCREATEPIXMAPPROC ;
typedef  scalar_t__ PFNGLXCREATEPBUFFERPROC ;
typedef  scalar_t__ PFNGLXCREATENEWCONTEXTPROC ;
typedef  scalar_t__ PFNGLXCHOOSEFBCONFIGPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GLX_VERSION_1_3 ; 
 scalar_t__ glad_glXChooseFBConfig ; 
 scalar_t__ glad_glXCreateNewContext ; 
 scalar_t__ glad_glXCreatePbuffer ; 
 scalar_t__ glad_glXCreatePixmap ; 
 scalar_t__ glad_glXCreateWindow ; 
 scalar_t__ glad_glXDestroyPbuffer ; 
 scalar_t__ glad_glXDestroyPixmap ; 
 scalar_t__ glad_glXDestroyWindow ; 
 scalar_t__ glad_glXGetCurrentReadDrawable ; 
 scalar_t__ glad_glXGetFBConfigAttrib ; 
 scalar_t__ glad_glXGetFBConfigs ; 
 scalar_t__ glad_glXGetSelectedEvent ; 
 scalar_t__ glad_glXGetVisualFromFBConfig ; 
 scalar_t__ glad_glXMakeContextCurrent ; 
 scalar_t__ glad_glXQueryContext ; 
 scalar_t__ glad_glXQueryDrawable ; 
 scalar_t__ glad_glXSelectEvent ; 

__attribute__((used)) static void load_GLX_VERSION_1_3(GLADloadproc load) {
	if(!GLAD_GLX_VERSION_1_3) return;
	glad_glXGetFBConfigs = (PFNGLXGETFBCONFIGSPROC)load("glXGetFBConfigs");
	glad_glXChooseFBConfig = (PFNGLXCHOOSEFBCONFIGPROC)load("glXChooseFBConfig");
	glad_glXGetFBConfigAttrib = (PFNGLXGETFBCONFIGATTRIBPROC)load("glXGetFBConfigAttrib");
	glad_glXGetVisualFromFBConfig = (PFNGLXGETVISUALFROMFBCONFIGPROC)load("glXGetVisualFromFBConfig");
	glad_glXCreateWindow = (PFNGLXCREATEWINDOWPROC)load("glXCreateWindow");
	glad_glXDestroyWindow = (PFNGLXDESTROYWINDOWPROC)load("glXDestroyWindow");
	glad_glXCreatePixmap = (PFNGLXCREATEPIXMAPPROC)load("glXCreatePixmap");
	glad_glXDestroyPixmap = (PFNGLXDESTROYPIXMAPPROC)load("glXDestroyPixmap");
	glad_glXCreatePbuffer = (PFNGLXCREATEPBUFFERPROC)load("glXCreatePbuffer");
	glad_glXDestroyPbuffer = (PFNGLXDESTROYPBUFFERPROC)load("glXDestroyPbuffer");
	glad_glXQueryDrawable = (PFNGLXQUERYDRAWABLEPROC)load("glXQueryDrawable");
	glad_glXCreateNewContext = (PFNGLXCREATENEWCONTEXTPROC)load("glXCreateNewContext");
	glad_glXMakeContextCurrent = (PFNGLXMAKECONTEXTCURRENTPROC)load("glXMakeContextCurrent");
	glad_glXGetCurrentReadDrawable = (PFNGLXGETCURRENTREADDRAWABLEPROC)load("glXGetCurrentReadDrawable");
	glad_glXQueryContext = (PFNGLXQUERYCONTEXTPROC)load("glXQueryContext");
	glad_glXSelectEvent = (PFNGLXSELECTEVENTPROC)load("glXSelectEvent");
	glad_glXGetSelectedEvent = (PFNGLXGETSELECTEDEVENTPROC)load("glXGetSelectedEvent");
}