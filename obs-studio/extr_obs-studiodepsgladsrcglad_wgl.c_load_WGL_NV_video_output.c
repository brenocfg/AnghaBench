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
typedef  scalar_t__ PFNWGLSENDPBUFFERTOVIDEONVPROC ;
typedef  scalar_t__ PFNWGLRELEASEVIDEOIMAGENVPROC ;
typedef  scalar_t__ PFNWGLRELEASEVIDEODEVICENVPROC ;
typedef  scalar_t__ PFNWGLGETVIDEOINFONVPROC ;
typedef  scalar_t__ PFNWGLGETVIDEODEVICENVPROC ;
typedef  scalar_t__ PFNWGLBINDVIDEOIMAGENVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_WGL_NV_video_output ; 
 scalar_t__ glad_wglBindVideoImageNV ; 
 scalar_t__ glad_wglGetVideoDeviceNV ; 
 scalar_t__ glad_wglGetVideoInfoNV ; 
 scalar_t__ glad_wglReleaseVideoDeviceNV ; 
 scalar_t__ glad_wglReleaseVideoImageNV ; 
 scalar_t__ glad_wglSendPbufferToVideoNV ; 

__attribute__((used)) static void load_WGL_NV_video_output(GLADloadproc load) {
	if(!GLAD_WGL_NV_video_output) return;
	glad_wglGetVideoDeviceNV = (PFNWGLGETVIDEODEVICENVPROC)load("wglGetVideoDeviceNV");
	glad_wglReleaseVideoDeviceNV = (PFNWGLRELEASEVIDEODEVICENVPROC)load("wglReleaseVideoDeviceNV");
	glad_wglBindVideoImageNV = (PFNWGLBINDVIDEOIMAGENVPROC)load("wglBindVideoImageNV");
	glad_wglReleaseVideoImageNV = (PFNWGLRELEASEVIDEOIMAGENVPROC)load("wglReleaseVideoImageNV");
	glad_wglSendPbufferToVideoNV = (PFNWGLSENDPBUFFERTOVIDEONVPROC)load("wglSendPbufferToVideoNV");
	glad_wglGetVideoInfoNV = (PFNWGLGETVIDEOINFONVPROC)load("wglGetVideoInfoNV");
}