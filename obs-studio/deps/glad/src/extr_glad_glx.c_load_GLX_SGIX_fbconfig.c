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
typedef  scalar_t__ PFNGLXGETVISUALFROMFBCONFIGSGIXPROC ;
typedef  scalar_t__ PFNGLXGETFBCONFIGFROMVISUALSGIXPROC ;
typedef  scalar_t__ PFNGLXGETFBCONFIGATTRIBSGIXPROC ;
typedef  scalar_t__ PFNGLXCREATEGLXPIXMAPWITHCONFIGSGIXPROC ;
typedef  scalar_t__ PFNGLXCREATECONTEXTWITHCONFIGSGIXPROC ;
typedef  scalar_t__ PFNGLXCHOOSEFBCONFIGSGIXPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GLX_SGIX_fbconfig ; 
 scalar_t__ glad_glXChooseFBConfigSGIX ; 
 scalar_t__ glad_glXCreateContextWithConfigSGIX ; 
 scalar_t__ glad_glXCreateGLXPixmapWithConfigSGIX ; 
 scalar_t__ glad_glXGetFBConfigAttribSGIX ; 
 scalar_t__ glad_glXGetFBConfigFromVisualSGIX ; 
 scalar_t__ glad_glXGetVisualFromFBConfigSGIX ; 

__attribute__((used)) static void load_GLX_SGIX_fbconfig(GLADloadproc load) {
	if(!GLAD_GLX_SGIX_fbconfig) return;
	glad_glXGetFBConfigAttribSGIX = (PFNGLXGETFBCONFIGATTRIBSGIXPROC)load("glXGetFBConfigAttribSGIX");
	glad_glXChooseFBConfigSGIX = (PFNGLXCHOOSEFBCONFIGSGIXPROC)load("glXChooseFBConfigSGIX");
	glad_glXCreateGLXPixmapWithConfigSGIX = (PFNGLXCREATEGLXPIXMAPWITHCONFIGSGIXPROC)load("glXCreateGLXPixmapWithConfigSGIX");
	glad_glXCreateContextWithConfigSGIX = (PFNGLXCREATECONTEXTWITHCONFIGSGIXPROC)load("glXCreateContextWithConfigSGIX");
	glad_glXGetVisualFromFBConfigSGIX = (PFNGLXGETVISUALFROMFBCONFIGSGIXPROC)load("glXGetVisualFromFBConfigSGIX");
	glad_glXGetFBConfigFromVisualSGIX = (PFNGLXGETFBCONFIGFROMVISUALSGIXPROC)load("glXGetFBConfigFromVisualSGIX");
}