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
typedef  scalar_t__ PFNGLPROGRAMNAMEDPARAMETER4FVNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMNAMEDPARAMETER4FNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMNAMEDPARAMETER4DVNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMNAMEDPARAMETER4DNVPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMNAMEDPARAMETERFVNVPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMNAMEDPARAMETERDVNVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_fragment_program ; 
 scalar_t__ glad_glGetProgramNamedParameterdvNV ; 
 scalar_t__ glad_glGetProgramNamedParameterfvNV ; 
 scalar_t__ glad_glProgramNamedParameter4dNV ; 
 scalar_t__ glad_glProgramNamedParameter4dvNV ; 
 scalar_t__ glad_glProgramNamedParameter4fNV ; 
 scalar_t__ glad_glProgramNamedParameter4fvNV ; 

__attribute__((used)) static void load_GL_NV_fragment_program(GLADloadproc load) {
	if(!GLAD_GL_NV_fragment_program) return;
	glad_glProgramNamedParameter4fNV = (PFNGLPROGRAMNAMEDPARAMETER4FNVPROC)load("glProgramNamedParameter4fNV");
	glad_glProgramNamedParameter4fvNV = (PFNGLPROGRAMNAMEDPARAMETER4FVNVPROC)load("glProgramNamedParameter4fvNV");
	glad_glProgramNamedParameter4dNV = (PFNGLPROGRAMNAMEDPARAMETER4DNVPROC)load("glProgramNamedParameter4dNV");
	glad_glProgramNamedParameter4dvNV = (PFNGLPROGRAMNAMEDPARAMETER4DVNVPROC)load("glProgramNamedParameter4dvNV");
	glad_glGetProgramNamedParameterfvNV = (PFNGLGETPROGRAMNAMEDPARAMETERFVNVPROC)load("glGetProgramNamedParameterfvNV");
	glad_glGetProgramNamedParameterdvNV = (PFNGLGETPROGRAMNAMEDPARAMETERDVNVPROC)load("glGetProgramNamedParameterdvNV");
}