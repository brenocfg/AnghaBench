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
typedef  scalar_t__ PFNGLWINDOWPOS3SVARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3SARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3IVARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3IARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3FVARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3FARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3DVARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3DARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2SVARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2SARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2IVARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2IARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2FVARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2FARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2DVARBPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2DARBPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_window_pos ; 
 scalar_t__ glad_glWindowPos2dARB ; 
 scalar_t__ glad_glWindowPos2dvARB ; 
 scalar_t__ glad_glWindowPos2fARB ; 
 scalar_t__ glad_glWindowPos2fvARB ; 
 scalar_t__ glad_glWindowPos2iARB ; 
 scalar_t__ glad_glWindowPos2ivARB ; 
 scalar_t__ glad_glWindowPos2sARB ; 
 scalar_t__ glad_glWindowPos2svARB ; 
 scalar_t__ glad_glWindowPos3dARB ; 
 scalar_t__ glad_glWindowPos3dvARB ; 
 scalar_t__ glad_glWindowPos3fARB ; 
 scalar_t__ glad_glWindowPos3fvARB ; 
 scalar_t__ glad_glWindowPos3iARB ; 
 scalar_t__ glad_glWindowPos3ivARB ; 
 scalar_t__ glad_glWindowPos3sARB ; 
 scalar_t__ glad_glWindowPos3svARB ; 

__attribute__((used)) static void load_GL_ARB_window_pos(GLADloadproc load) {
	if(!GLAD_GL_ARB_window_pos) return;
	glad_glWindowPos2dARB = (PFNGLWINDOWPOS2DARBPROC)load("glWindowPos2dARB");
	glad_glWindowPos2dvARB = (PFNGLWINDOWPOS2DVARBPROC)load("glWindowPos2dvARB");
	glad_glWindowPos2fARB = (PFNGLWINDOWPOS2FARBPROC)load("glWindowPos2fARB");
	glad_glWindowPos2fvARB = (PFNGLWINDOWPOS2FVARBPROC)load("glWindowPos2fvARB");
	glad_glWindowPos2iARB = (PFNGLWINDOWPOS2IARBPROC)load("glWindowPos2iARB");
	glad_glWindowPos2ivARB = (PFNGLWINDOWPOS2IVARBPROC)load("glWindowPos2ivARB");
	glad_glWindowPos2sARB = (PFNGLWINDOWPOS2SARBPROC)load("glWindowPos2sARB");
	glad_glWindowPos2svARB = (PFNGLWINDOWPOS2SVARBPROC)load("glWindowPos2svARB");
	glad_glWindowPos3dARB = (PFNGLWINDOWPOS3DARBPROC)load("glWindowPos3dARB");
	glad_glWindowPos3dvARB = (PFNGLWINDOWPOS3DVARBPROC)load("glWindowPos3dvARB");
	glad_glWindowPos3fARB = (PFNGLWINDOWPOS3FARBPROC)load("glWindowPos3fARB");
	glad_glWindowPos3fvARB = (PFNGLWINDOWPOS3FVARBPROC)load("glWindowPos3fvARB");
	glad_glWindowPos3iARB = (PFNGLWINDOWPOS3IARBPROC)load("glWindowPos3iARB");
	glad_glWindowPos3ivARB = (PFNGLWINDOWPOS3IVARBPROC)load("glWindowPos3ivARB");
	glad_glWindowPos3sARB = (PFNGLWINDOWPOS3SARBPROC)load("glWindowPos3sARB");
	glad_glWindowPos3svARB = (PFNGLWINDOWPOS3SVARBPROC)load("glWindowPos3svARB");
}