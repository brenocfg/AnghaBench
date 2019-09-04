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
typedef  scalar_t__ PFNWGLRESETFRAMECOUNTNVPROC ;
typedef  scalar_t__ PFNWGLQUERYSWAPGROUPNVPROC ;
typedef  scalar_t__ PFNWGLQUERYMAXSWAPGROUPSNVPROC ;
typedef  scalar_t__ PFNWGLQUERYFRAMECOUNTNVPROC ;
typedef  scalar_t__ PFNWGLJOINSWAPGROUPNVPROC ;
typedef  scalar_t__ PFNWGLBINDSWAPBARRIERNVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_WGL_NV_swap_group ; 
 scalar_t__ glad_wglBindSwapBarrierNV ; 
 scalar_t__ glad_wglJoinSwapGroupNV ; 
 scalar_t__ glad_wglQueryFrameCountNV ; 
 scalar_t__ glad_wglQueryMaxSwapGroupsNV ; 
 scalar_t__ glad_wglQuerySwapGroupNV ; 
 scalar_t__ glad_wglResetFrameCountNV ; 

__attribute__((used)) static void load_WGL_NV_swap_group(GLADloadproc load) {
	if(!GLAD_WGL_NV_swap_group) return;
	glad_wglJoinSwapGroupNV = (PFNWGLJOINSWAPGROUPNVPROC)load("wglJoinSwapGroupNV");
	glad_wglBindSwapBarrierNV = (PFNWGLBINDSWAPBARRIERNVPROC)load("wglBindSwapBarrierNV");
	glad_wglQuerySwapGroupNV = (PFNWGLQUERYSWAPGROUPNVPROC)load("wglQuerySwapGroupNV");
	glad_wglQueryMaxSwapGroupsNV = (PFNWGLQUERYMAXSWAPGROUPSNVPROC)load("wglQueryMaxSwapGroupsNV");
	glad_wglQueryFrameCountNV = (PFNWGLQUERYFRAMECOUNTNVPROC)load("wglQueryFrameCountNV");
	glad_wglResetFrameCountNV = (PFNWGLRESETFRAMECOUNTNVPROC)load("wglResetFrameCountNV");
}