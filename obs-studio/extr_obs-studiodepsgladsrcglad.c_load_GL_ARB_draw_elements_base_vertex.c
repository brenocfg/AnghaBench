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
typedef  scalar_t__ PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC ;
typedef  scalar_t__ PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC ;
typedef  scalar_t__ PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC ;
typedef  scalar_t__ PFNGLDRAWELEMENTSBASEVERTEXPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_draw_elements_base_vertex ; 
 scalar_t__ glad_glDrawElementsBaseVertex ; 
 scalar_t__ glad_glDrawElementsInstancedBaseVertex ; 
 scalar_t__ glad_glDrawRangeElementsBaseVertex ; 
 scalar_t__ glad_glMultiDrawElementsBaseVertex ; 

__attribute__((used)) static void load_GL_ARB_draw_elements_base_vertex(GLADloadproc load) {
	if(!GLAD_GL_ARB_draw_elements_base_vertex) return;
	glad_glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)load("glDrawElementsBaseVertex");
	glad_glDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)load("glDrawRangeElementsBaseVertex");
	glad_glDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)load("glDrawElementsInstancedBaseVertex");
	glad_glMultiDrawElementsBaseVertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)load("glMultiDrawElementsBaseVertex");
}