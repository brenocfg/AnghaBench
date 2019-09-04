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
typedef  scalar_t__ PFNGLXSENDPBUFFERTOVIDEONVPROC ;
typedef  scalar_t__ PFNGLXRELEASEVIDEOIMAGENVPROC ;
typedef  scalar_t__ PFNGLXRELEASEVIDEODEVICENVPROC ;
typedef  scalar_t__ PFNGLXGETVIDEOINFONVPROC ;
typedef  scalar_t__ PFNGLXGETVIDEODEVICENVPROC ;
typedef  scalar_t__ PFNGLXBINDVIDEOIMAGENVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GLX_NV_video_output ; 
 scalar_t__ glad_glXBindVideoImageNV ; 
 scalar_t__ glad_glXGetVideoDeviceNV ; 
 scalar_t__ glad_glXGetVideoInfoNV ; 
 scalar_t__ glad_glXReleaseVideoDeviceNV ; 
 scalar_t__ glad_glXReleaseVideoImageNV ; 
 scalar_t__ glad_glXSendPbufferToVideoNV ; 

__attribute__((used)) static void load_GLX_NV_video_output(GLADloadproc load) {
	if(!GLAD_GLX_NV_video_output) return;
	glad_glXGetVideoDeviceNV = (PFNGLXGETVIDEODEVICENVPROC)load("glXGetVideoDeviceNV");
	glad_glXReleaseVideoDeviceNV = (PFNGLXRELEASEVIDEODEVICENVPROC)load("glXReleaseVideoDeviceNV");
	glad_glXBindVideoImageNV = (PFNGLXBINDVIDEOIMAGENVPROC)load("glXBindVideoImageNV");
	glad_glXReleaseVideoImageNV = (PFNGLXRELEASEVIDEOIMAGENVPROC)load("glXReleaseVideoImageNV");
	glad_glXSendPbufferToVideoNV = (PFNGLXSENDPBUFFERTOVIDEONVPROC)load("glXSendPbufferToVideoNV");
	glad_glXGetVideoInfoNV = (PFNGLXGETVIDEOINFONVPROC)load("glXGetVideoInfoNV");
}