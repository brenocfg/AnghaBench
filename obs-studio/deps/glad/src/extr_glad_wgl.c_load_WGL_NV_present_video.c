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
typedef  scalar_t__ PFNWGLQUERYCURRENTCONTEXTNVPROC ;
typedef  scalar_t__ PFNWGLENUMERATEVIDEODEVICESNVPROC ;
typedef  scalar_t__ PFNWGLBINDVIDEODEVICENVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_WGL_NV_present_video ; 
 scalar_t__ glad_wglBindVideoDeviceNV ; 
 scalar_t__ glad_wglEnumerateVideoDevicesNV ; 
 scalar_t__ glad_wglQueryCurrentContextNV ; 

__attribute__((used)) static void load_WGL_NV_present_video(GLADloadproc load) {
	if(!GLAD_WGL_NV_present_video) return;
	glad_wglEnumerateVideoDevicesNV = (PFNWGLENUMERATEVIDEODEVICESNVPROC)load("wglEnumerateVideoDevicesNV");
	glad_wglBindVideoDeviceNV = (PFNWGLBINDVIDEODEVICENVPROC)load("wglBindVideoDeviceNV");
	glad_wglQueryCurrentContextNV = (PFNWGLQUERYCURRENTCONTEXTNVPROC)load("wglQueryCurrentContextNV");
}