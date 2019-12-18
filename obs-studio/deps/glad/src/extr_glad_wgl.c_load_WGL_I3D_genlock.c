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
typedef  scalar_t__ PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC ;
typedef  scalar_t__ PFNWGLISENABLEDGENLOCKI3DPROC ;
typedef  scalar_t__ PFNWGLGETGENLOCKSOURCEI3DPROC ;
typedef  scalar_t__ PFNWGLGETGENLOCKSOURCEEDGEI3DPROC ;
typedef  scalar_t__ PFNWGLGETGENLOCKSOURCEDELAYI3DPROC ;
typedef  scalar_t__ PFNWGLGETGENLOCKSAMPLERATEI3DPROC ;
typedef  scalar_t__ PFNWGLGENLOCKSOURCEI3DPROC ;
typedef  scalar_t__ PFNWGLGENLOCKSOURCEEDGEI3DPROC ;
typedef  scalar_t__ PFNWGLGENLOCKSOURCEDELAYI3DPROC ;
typedef  scalar_t__ PFNWGLGENLOCKSAMPLERATEI3DPROC ;
typedef  scalar_t__ PFNWGLENABLEGENLOCKI3DPROC ;
typedef  scalar_t__ PFNWGLDISABLEGENLOCKI3DPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_WGL_I3D_genlock ; 
 scalar_t__ glad_wglDisableGenlockI3D ; 
 scalar_t__ glad_wglEnableGenlockI3D ; 
 scalar_t__ glad_wglGenlockSampleRateI3D ; 
 scalar_t__ glad_wglGenlockSourceDelayI3D ; 
 scalar_t__ glad_wglGenlockSourceEdgeI3D ; 
 scalar_t__ glad_wglGenlockSourceI3D ; 
 scalar_t__ glad_wglGetGenlockSampleRateI3D ; 
 scalar_t__ glad_wglGetGenlockSourceDelayI3D ; 
 scalar_t__ glad_wglGetGenlockSourceEdgeI3D ; 
 scalar_t__ glad_wglGetGenlockSourceI3D ; 
 scalar_t__ glad_wglIsEnabledGenlockI3D ; 
 scalar_t__ glad_wglQueryGenlockMaxSourceDelayI3D ; 

__attribute__((used)) static void load_WGL_I3D_genlock(GLADloadproc load) {
	if(!GLAD_WGL_I3D_genlock) return;
	glad_wglEnableGenlockI3D = (PFNWGLENABLEGENLOCKI3DPROC)load("wglEnableGenlockI3D");
	glad_wglDisableGenlockI3D = (PFNWGLDISABLEGENLOCKI3DPROC)load("wglDisableGenlockI3D");
	glad_wglIsEnabledGenlockI3D = (PFNWGLISENABLEDGENLOCKI3DPROC)load("wglIsEnabledGenlockI3D");
	glad_wglGenlockSourceI3D = (PFNWGLGENLOCKSOURCEI3DPROC)load("wglGenlockSourceI3D");
	glad_wglGetGenlockSourceI3D = (PFNWGLGETGENLOCKSOURCEI3DPROC)load("wglGetGenlockSourceI3D");
	glad_wglGenlockSourceEdgeI3D = (PFNWGLGENLOCKSOURCEEDGEI3DPROC)load("wglGenlockSourceEdgeI3D");
	glad_wglGetGenlockSourceEdgeI3D = (PFNWGLGETGENLOCKSOURCEEDGEI3DPROC)load("wglGetGenlockSourceEdgeI3D");
	glad_wglGenlockSampleRateI3D = (PFNWGLGENLOCKSAMPLERATEI3DPROC)load("wglGenlockSampleRateI3D");
	glad_wglGetGenlockSampleRateI3D = (PFNWGLGETGENLOCKSAMPLERATEI3DPROC)load("wglGetGenlockSampleRateI3D");
	glad_wglGenlockSourceDelayI3D = (PFNWGLGENLOCKSOURCEDELAYI3DPROC)load("wglGenlockSourceDelayI3D");
	glad_wglGetGenlockSourceDelayI3D = (PFNWGLGETGENLOCKSOURCEDELAYI3DPROC)load("wglGetGenlockSourceDelayI3D");
	glad_wglQueryGenlockMaxSourceDelayI3D = (PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC)load("wglQueryGenlockMaxSourceDelayI3D");
}