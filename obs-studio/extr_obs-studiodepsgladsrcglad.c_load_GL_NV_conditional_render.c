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
typedef  scalar_t__ PFNGLENDCONDITIONALRENDERNVPROC ;
typedef  scalar_t__ PFNGLBEGINCONDITIONALRENDERNVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_conditional_render ; 
 scalar_t__ glad_glBeginConditionalRenderNV ; 
 scalar_t__ glad_glEndConditionalRenderNV ; 

__attribute__((used)) static void load_GL_NV_conditional_render(GLADloadproc load) {
	if(!GLAD_GL_NV_conditional_render) return;
	glad_glBeginConditionalRenderNV = (PFNGLBEGINCONDITIONALRENDERNVPROC)load("glBeginConditionalRenderNV");
	glad_glEndConditionalRenderNV = (PFNGLENDCONDITIONALRENDERNVPROC)load("glEndConditionalRenderNV");
}