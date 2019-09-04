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
typedef  scalar_t__ PFNGLPROGRAMLOCALPARAMETERSI4UIVNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMLOCALPARAMETERSI4IVNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMLOCALPARAMETERI4UIVNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMLOCALPARAMETERI4UINVPROC ;
typedef  scalar_t__ PFNGLPROGRAMLOCALPARAMETERI4IVNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMLOCALPARAMETERI4INVPROC ;
typedef  scalar_t__ PFNGLPROGRAMENVPARAMETERSI4UIVNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMENVPARAMETERSI4IVNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMENVPARAMETERI4UIVNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMENVPARAMETERI4UINVPROC ;
typedef  scalar_t__ PFNGLPROGRAMENVPARAMETERI4IVNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMENVPARAMETERI4INVPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMLOCALPARAMETERIUIVNVPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMLOCALPARAMETERIIVNVPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMENVPARAMETERIUIVNVPROC ;
typedef  scalar_t__ PFNGLGETPROGRAMENVPARAMETERIIVNVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_gpu_program4 ; 
 scalar_t__ glad_glGetProgramEnvParameterIivNV ; 
 scalar_t__ glad_glGetProgramEnvParameterIuivNV ; 
 scalar_t__ glad_glGetProgramLocalParameterIivNV ; 
 scalar_t__ glad_glGetProgramLocalParameterIuivNV ; 
 scalar_t__ glad_glProgramEnvParameterI4iNV ; 
 scalar_t__ glad_glProgramEnvParameterI4ivNV ; 
 scalar_t__ glad_glProgramEnvParameterI4uiNV ; 
 scalar_t__ glad_glProgramEnvParameterI4uivNV ; 
 scalar_t__ glad_glProgramEnvParametersI4ivNV ; 
 scalar_t__ glad_glProgramEnvParametersI4uivNV ; 
 scalar_t__ glad_glProgramLocalParameterI4iNV ; 
 scalar_t__ glad_glProgramLocalParameterI4ivNV ; 
 scalar_t__ glad_glProgramLocalParameterI4uiNV ; 
 scalar_t__ glad_glProgramLocalParameterI4uivNV ; 
 scalar_t__ glad_glProgramLocalParametersI4ivNV ; 
 scalar_t__ glad_glProgramLocalParametersI4uivNV ; 

__attribute__((used)) static void load_GL_NV_gpu_program4(GLADloadproc load) {
	if(!GLAD_GL_NV_gpu_program4) return;
	glad_glProgramLocalParameterI4iNV = (PFNGLPROGRAMLOCALPARAMETERI4INVPROC)load("glProgramLocalParameterI4iNV");
	glad_glProgramLocalParameterI4ivNV = (PFNGLPROGRAMLOCALPARAMETERI4IVNVPROC)load("glProgramLocalParameterI4ivNV");
	glad_glProgramLocalParametersI4ivNV = (PFNGLPROGRAMLOCALPARAMETERSI4IVNVPROC)load("glProgramLocalParametersI4ivNV");
	glad_glProgramLocalParameterI4uiNV = (PFNGLPROGRAMLOCALPARAMETERI4UINVPROC)load("glProgramLocalParameterI4uiNV");
	glad_glProgramLocalParameterI4uivNV = (PFNGLPROGRAMLOCALPARAMETERI4UIVNVPROC)load("glProgramLocalParameterI4uivNV");
	glad_glProgramLocalParametersI4uivNV = (PFNGLPROGRAMLOCALPARAMETERSI4UIVNVPROC)load("glProgramLocalParametersI4uivNV");
	glad_glProgramEnvParameterI4iNV = (PFNGLPROGRAMENVPARAMETERI4INVPROC)load("glProgramEnvParameterI4iNV");
	glad_glProgramEnvParameterI4ivNV = (PFNGLPROGRAMENVPARAMETERI4IVNVPROC)load("glProgramEnvParameterI4ivNV");
	glad_glProgramEnvParametersI4ivNV = (PFNGLPROGRAMENVPARAMETERSI4IVNVPROC)load("glProgramEnvParametersI4ivNV");
	glad_glProgramEnvParameterI4uiNV = (PFNGLPROGRAMENVPARAMETERI4UINVPROC)load("glProgramEnvParameterI4uiNV");
	glad_glProgramEnvParameterI4uivNV = (PFNGLPROGRAMENVPARAMETERI4UIVNVPROC)load("glProgramEnvParameterI4uivNV");
	glad_glProgramEnvParametersI4uivNV = (PFNGLPROGRAMENVPARAMETERSI4UIVNVPROC)load("glProgramEnvParametersI4uivNV");
	glad_glGetProgramLocalParameterIivNV = (PFNGLGETPROGRAMLOCALPARAMETERIIVNVPROC)load("glGetProgramLocalParameterIivNV");
	glad_glGetProgramLocalParameterIuivNV = (PFNGLGETPROGRAMLOCALPARAMETERIUIVNVPROC)load("glGetProgramLocalParameterIuivNV");
	glad_glGetProgramEnvParameterIivNV = (PFNGLGETPROGRAMENVPARAMETERIIVNVPROC)load("glGetProgramEnvParameterIivNV");
	glad_glGetProgramEnvParameterIuivNV = (PFNGLGETPROGRAMENVPARAMETERIUIVNVPROC)load("glGetProgramEnvParameterIuivNV");
}