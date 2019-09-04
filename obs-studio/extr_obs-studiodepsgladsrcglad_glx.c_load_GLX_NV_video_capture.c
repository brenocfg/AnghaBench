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
typedef  scalar_t__ PFNGLXRELEASEVIDEOCAPTUREDEVICENVPROC ;
typedef  scalar_t__ PFNGLXQUERYVIDEOCAPTUREDEVICENVPROC ;
typedef  scalar_t__ PFNGLXLOCKVIDEOCAPTUREDEVICENVPROC ;
typedef  scalar_t__ PFNGLXENUMERATEVIDEOCAPTUREDEVICESNVPROC ;
typedef  scalar_t__ PFNGLXBINDVIDEOCAPTUREDEVICENVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GLX_NV_video_capture ; 
 scalar_t__ glad_glXBindVideoCaptureDeviceNV ; 
 scalar_t__ glad_glXEnumerateVideoCaptureDevicesNV ; 
 scalar_t__ glad_glXLockVideoCaptureDeviceNV ; 
 scalar_t__ glad_glXQueryVideoCaptureDeviceNV ; 
 scalar_t__ glad_glXReleaseVideoCaptureDeviceNV ; 

__attribute__((used)) static void load_GLX_NV_video_capture(GLADloadproc load) {
	if(!GLAD_GLX_NV_video_capture) return;
	glad_glXBindVideoCaptureDeviceNV = (PFNGLXBINDVIDEOCAPTUREDEVICENVPROC)load("glXBindVideoCaptureDeviceNV");
	glad_glXEnumerateVideoCaptureDevicesNV = (PFNGLXENUMERATEVIDEOCAPTUREDEVICESNVPROC)load("glXEnumerateVideoCaptureDevicesNV");
	glad_glXLockVideoCaptureDeviceNV = (PFNGLXLOCKVIDEOCAPTUREDEVICENVPROC)load("glXLockVideoCaptureDeviceNV");
	glad_glXQueryVideoCaptureDeviceNV = (PFNGLXQUERYVIDEOCAPTUREDEVICENVPROC)load("glXQueryVideoCaptureDeviceNV");
	glad_glXReleaseVideoCaptureDeviceNV = (PFNGLXRELEASEVIDEOCAPTUREDEVICENVPROC)load("glXReleaseVideoCaptureDeviceNV");
}