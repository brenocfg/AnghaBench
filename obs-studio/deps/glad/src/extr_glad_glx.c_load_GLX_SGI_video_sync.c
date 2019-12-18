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
typedef  scalar_t__ PFNGLXWAITVIDEOSYNCSGIPROC ;
typedef  scalar_t__ PFNGLXGETVIDEOSYNCSGIPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GLX_SGI_video_sync ; 
 scalar_t__ glad_glXGetVideoSyncSGI ; 
 scalar_t__ glad_glXWaitVideoSyncSGI ; 

__attribute__((used)) static void load_GLX_SGI_video_sync(GLADloadproc load) {
	if(!GLAD_GLX_SGI_video_sync) return;
	glad_glXGetVideoSyncSGI = (PFNGLXGETVIDEOSYNCSGIPROC)load("glXGetVideoSyncSGI");
	glad_glXWaitVideoSyncSGI = (PFNGLXWAITVIDEOSYNCSGIPROC)load("glXWaitVideoSyncSGI");
}