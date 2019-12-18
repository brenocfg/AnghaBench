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
typedef  scalar_t__ PFNGLDRAWELEMENTSINDIRECTPROC ;
typedef  scalar_t__ PFNGLDRAWARRAYSINDIRECTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_draw_indirect ; 
 scalar_t__ glad_glDrawArraysIndirect ; 
 scalar_t__ glad_glDrawElementsIndirect ; 

__attribute__((used)) static void load_GL_ARB_draw_indirect(GLADloadproc load) {
	if(!GLAD_GL_ARB_draw_indirect) return;
	glad_glDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC)load("glDrawArraysIndirect");
	glad_glDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC)load("glDrawElementsIndirect");
}