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
typedef  scalar_t__ PFNGLXQUERYCHANNELRECTSGIXPROC ;
typedef  scalar_t__ PFNGLXQUERYCHANNELDELTASSGIXPROC ;
typedef  scalar_t__ PFNGLXCHANNELRECTSYNCSGIXPROC ;
typedef  scalar_t__ PFNGLXCHANNELRECTSGIXPROC ;
typedef  scalar_t__ PFNGLXBINDCHANNELTOWINDOWSGIXPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GLX_SGIX_video_resize ; 
 scalar_t__ glad_glXBindChannelToWindowSGIX ; 
 scalar_t__ glad_glXChannelRectSGIX ; 
 scalar_t__ glad_glXChannelRectSyncSGIX ; 
 scalar_t__ glad_glXQueryChannelDeltasSGIX ; 
 scalar_t__ glad_glXQueryChannelRectSGIX ; 

__attribute__((used)) static void load_GLX_SGIX_video_resize(GLADloadproc load) {
	if(!GLAD_GLX_SGIX_video_resize) return;
	glad_glXBindChannelToWindowSGIX = (PFNGLXBINDCHANNELTOWINDOWSGIXPROC)load("glXBindChannelToWindowSGIX");
	glad_glXChannelRectSGIX = (PFNGLXCHANNELRECTSGIXPROC)load("glXChannelRectSGIX");
	glad_glXQueryChannelRectSGIX = (PFNGLXQUERYCHANNELRECTSGIXPROC)load("glXQueryChannelRectSGIX");
	glad_glXQueryChannelDeltasSGIX = (PFNGLXQUERYCHANNELDELTASSGIXPROC)load("glXQueryChannelDeltasSGIX");
	glad_glXChannelRectSyncSGIX = (PFNGLXCHANNELRECTSYNCSGIXPROC)load("glXChannelRectSyncSGIX");
}