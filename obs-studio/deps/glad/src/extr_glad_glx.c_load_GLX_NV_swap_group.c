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
typedef  scalar_t__ PFNGLXRESETFRAMECOUNTNVPROC ;
typedef  scalar_t__ PFNGLXQUERYSWAPGROUPNVPROC ;
typedef  scalar_t__ PFNGLXQUERYMAXSWAPGROUPSNVPROC ;
typedef  scalar_t__ PFNGLXQUERYFRAMECOUNTNVPROC ;
typedef  scalar_t__ PFNGLXJOINSWAPGROUPNVPROC ;
typedef  scalar_t__ PFNGLXBINDSWAPBARRIERNVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GLX_NV_swap_group ; 
 scalar_t__ glad_glXBindSwapBarrierNV ; 
 scalar_t__ glad_glXJoinSwapGroupNV ; 
 scalar_t__ glad_glXQueryFrameCountNV ; 
 scalar_t__ glad_glXQueryMaxSwapGroupsNV ; 
 scalar_t__ glad_glXQuerySwapGroupNV ; 
 scalar_t__ glad_glXResetFrameCountNV ; 

__attribute__((used)) static void load_GLX_NV_swap_group(GLADloadproc load) {
	if(!GLAD_GLX_NV_swap_group) return;
	glad_glXJoinSwapGroupNV = (PFNGLXJOINSWAPGROUPNVPROC)load("glXJoinSwapGroupNV");
	glad_glXBindSwapBarrierNV = (PFNGLXBINDSWAPBARRIERNVPROC)load("glXBindSwapBarrierNV");
	glad_glXQuerySwapGroupNV = (PFNGLXQUERYSWAPGROUPNVPROC)load("glXQuerySwapGroupNV");
	glad_glXQueryMaxSwapGroupsNV = (PFNGLXQUERYMAXSWAPGROUPSNVPROC)load("glXQueryMaxSwapGroupsNV");
	glad_glXQueryFrameCountNV = (PFNGLXQUERYFRAMECOUNTNVPROC)load("glXQueryFrameCountNV");
	glad_glXResetFrameCountNV = (PFNGLXRESETFRAMECOUNTNVPROC)load("glXResetFrameCountNV");
}