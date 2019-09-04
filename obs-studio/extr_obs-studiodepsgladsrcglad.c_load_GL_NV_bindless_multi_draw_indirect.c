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
typedef  scalar_t__ PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSNVPROC ;
typedef  scalar_t__ PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSNVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_bindless_multi_draw_indirect ; 
 scalar_t__ glad_glMultiDrawArraysIndirectBindlessNV ; 
 scalar_t__ glad_glMultiDrawElementsIndirectBindlessNV ; 

__attribute__((used)) static void load_GL_NV_bindless_multi_draw_indirect(GLADloadproc load) {
	if(!GLAD_GL_NV_bindless_multi_draw_indirect) return;
	glad_glMultiDrawArraysIndirectBindlessNV = (PFNGLMULTIDRAWARRAYSINDIRECTBINDLESSNVPROC)load("glMultiDrawArraysIndirectBindlessNV");
	glad_glMultiDrawElementsIndirectBindlessNV = (PFNGLMULTIDRAWELEMENTSINDIRECTBINDLESSNVPROC)load("glMultiDrawElementsIndirectBindlessNV");
}