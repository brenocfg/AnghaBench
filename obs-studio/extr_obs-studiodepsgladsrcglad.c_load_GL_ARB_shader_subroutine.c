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
typedef  scalar_t__ PFNGLUNIFORMSUBROUTINESUIVPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMSUBROUTINEUIVPROC ;
typedef  scalar_t__ PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC ;
typedef  scalar_t__ PFNGLGETSUBROUTINEINDEXPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMSTAGEIVPROC ;
typedef  scalar_t__ PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC ;
typedef  scalar_t__ PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC ;
typedef  scalar_t__ PFNGLGETACTIVESUBROUTINENAMEPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_shader_subroutine ; 
 scalar_t__ glad_glGetActiveSubroutineName ; 
 scalar_t__ glad_glGetActiveSubroutineUniformName ; 
 scalar_t__ glad_glGetActiveSubroutineUniformiv ; 
 scalar_t__ glad_glGetProgramStageiv ; 
 scalar_t__ glad_glGetSubroutineIndex ; 
 scalar_t__ glad_glGetSubroutineUniformLocation ; 
 scalar_t__ glad_glGetUniformSubroutineuiv ; 
 scalar_t__ glad_glUniformSubroutinesuiv ; 

__attribute__((used)) static void load_GL_ARB_shader_subroutine(GLADloadproc load) {
	if(!GLAD_GL_ARB_shader_subroutine) return;
	glad_glGetSubroutineUniformLocation = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)load("glGetSubroutineUniformLocation");
	glad_glGetSubroutineIndex = (PFNGLGETSUBROUTINEINDEXPROC)load("glGetSubroutineIndex");
	glad_glGetActiveSubroutineUniformiv = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)load("glGetActiveSubroutineUniformiv");
	glad_glGetActiveSubroutineUniformName = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)load("glGetActiveSubroutineUniformName");
	glad_glGetActiveSubroutineName = (PFNGLGETACTIVESUBROUTINENAMEPROC)load("glGetActiveSubroutineName");
	glad_glUniformSubroutinesuiv = (PFNGLUNIFORMSUBROUTINESUIVPROC)load("glUniformSubroutinesuiv");
	glad_glGetUniformSubroutineuiv = (PFNGLGETUNIFORMSUBROUTINEUIVPROC)load("glGetUniformSubroutineuiv");
	glad_glGetProgramStageiv = (PFNGLGETPROGRAMSTAGEIVPROC)load("glGetProgramStageiv");
}