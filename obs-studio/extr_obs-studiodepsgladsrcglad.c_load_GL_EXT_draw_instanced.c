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
typedef  scalar_t__ PFNGLDRAWELEMENTSINSTANCEDEXTPROC ;
typedef  scalar_t__ PFNGLDRAWARRAYSINSTANCEDEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_draw_instanced ; 
 scalar_t__ glad_glDrawArraysInstancedEXT ; 
 scalar_t__ glad_glDrawElementsInstancedEXT ; 

__attribute__((used)) static void load_GL_EXT_draw_instanced(GLADloadproc load) {
	if(!GLAD_GL_EXT_draw_instanced) return;
	glad_glDrawArraysInstancedEXT = (PFNGLDRAWARRAYSINSTANCEDEXTPROC)load("glDrawArraysInstancedEXT");
	glad_glDrawElementsInstancedEXT = (PFNGLDRAWELEMENTSINSTANCEDEXTPROC)load("glDrawElementsInstancedEXT");
}