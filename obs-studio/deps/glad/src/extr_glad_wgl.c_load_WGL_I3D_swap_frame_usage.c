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
typedef  scalar_t__ PFNWGLQUERYFRAMETRACKINGI3DPROC ;
typedef  scalar_t__ PFNWGLGETFRAMEUSAGEI3DPROC ;
typedef  scalar_t__ PFNWGLENDFRAMETRACKINGI3DPROC ;
typedef  scalar_t__ PFNWGLBEGINFRAMETRACKINGI3DPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_WGL_I3D_swap_frame_usage ; 
 scalar_t__ glad_wglBeginFrameTrackingI3D ; 
 scalar_t__ glad_wglEndFrameTrackingI3D ; 
 scalar_t__ glad_wglGetFrameUsageI3D ; 
 scalar_t__ glad_wglQueryFrameTrackingI3D ; 

__attribute__((used)) static void load_WGL_I3D_swap_frame_usage(GLADloadproc load) {
	if(!GLAD_WGL_I3D_swap_frame_usage) return;
	glad_wglGetFrameUsageI3D = (PFNWGLGETFRAMEUSAGEI3DPROC)load("wglGetFrameUsageI3D");
	glad_wglBeginFrameTrackingI3D = (PFNWGLBEGINFRAMETRACKINGI3DPROC)load("wglBeginFrameTrackingI3D");
	glad_wglEndFrameTrackingI3D = (PFNWGLENDFRAMETRACKINGI3DPROC)load("wglEndFrameTrackingI3D");
	glad_wglQueryFrameTrackingI3D = (PFNWGLQUERYFRAMETRACKINGI3DPROC)load("wglQueryFrameTrackingI3D");
}