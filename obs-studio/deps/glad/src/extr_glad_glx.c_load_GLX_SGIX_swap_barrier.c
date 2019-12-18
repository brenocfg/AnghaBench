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
typedef  scalar_t__ PFNGLXQUERYMAXSWAPBARRIERSSGIXPROC ;
typedef  scalar_t__ PFNGLXBINDSWAPBARRIERSGIXPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GLX_SGIX_swap_barrier ; 
 scalar_t__ glad_glXBindSwapBarrierSGIX ; 
 scalar_t__ glad_glXQueryMaxSwapBarriersSGIX ; 

__attribute__((used)) static void load_GLX_SGIX_swap_barrier(GLADloadproc load) {
	if(!GLAD_GLX_SGIX_swap_barrier) return;
	glad_glXBindSwapBarrierSGIX = (PFNGLXBINDSWAPBARRIERSGIXPROC)load("glXBindSwapBarrierSGIX");
	glad_glXQueryMaxSwapBarriersSGIX = (PFNGLXQUERYMAXSWAPBARRIERSSGIXPROC)load("glXQueryMaxSwapBarriersSGIX");
}