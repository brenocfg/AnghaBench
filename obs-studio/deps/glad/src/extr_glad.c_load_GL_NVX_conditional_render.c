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
typedef  scalar_t__ PFNGLENDCONDITIONALRENDERNVXPROC ;
typedef  scalar_t__ PFNGLBEGINCONDITIONALRENDERNVXPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NVX_conditional_render ; 
 scalar_t__ glad_glBeginConditionalRenderNVX ; 
 scalar_t__ glad_glEndConditionalRenderNVX ; 

__attribute__((used)) static void load_GL_NVX_conditional_render(GLADloadproc load) {
	if(!GLAD_GL_NVX_conditional_render) return;
	glad_glBeginConditionalRenderNVX = (PFNGLBEGINCONDITIONALRENDERNVXPROC)load("glBeginConditionalRenderNVX");
	glad_glEndConditionalRenderNVX = (PFNGLENDCONDITIONALRENDERNVXPROC)load("glEndConditionalRenderNVX");
}