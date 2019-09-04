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
typedef  scalar_t__ PFNGLUNIFORMMATRIX4X3DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX4X2DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX4DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX3X4DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX3X2DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX3DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX2X4DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX2X3DVPROC ;
typedef  scalar_t__ PFNGLUNIFORMMATRIX2DVPROC ;
typedef  scalar_t__ PFNGLUNIFORM4DVPROC ;
typedef  scalar_t__ PFNGLUNIFORM4DPROC ;
typedef  scalar_t__ PFNGLUNIFORM3DVPROC ;
typedef  scalar_t__ PFNGLUNIFORM3DPROC ;
typedef  scalar_t__ PFNGLUNIFORM2DVPROC ;
typedef  scalar_t__ PFNGLUNIFORM2DPROC ;
typedef  scalar_t__ PFNGLUNIFORM1DVPROC ;
typedef  scalar_t__ PFNGLUNIFORM1DPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMDVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_gpu_shader_fp64 ; 
 scalar_t__ glad_glGetUniformdv ; 
 scalar_t__ glad_glUniform1d ; 
 scalar_t__ glad_glUniform1dv ; 
 scalar_t__ glad_glUniform2d ; 
 scalar_t__ glad_glUniform2dv ; 
 scalar_t__ glad_glUniform3d ; 
 scalar_t__ glad_glUniform3dv ; 
 scalar_t__ glad_glUniform4d ; 
 scalar_t__ glad_glUniform4dv ; 
 scalar_t__ glad_glUniformMatrix2dv ; 
 scalar_t__ glad_glUniformMatrix2x3dv ; 
 scalar_t__ glad_glUniformMatrix2x4dv ; 
 scalar_t__ glad_glUniformMatrix3dv ; 
 scalar_t__ glad_glUniformMatrix3x2dv ; 
 scalar_t__ glad_glUniformMatrix3x4dv ; 
 scalar_t__ glad_glUniformMatrix4dv ; 
 scalar_t__ glad_glUniformMatrix4x2dv ; 
 scalar_t__ glad_glUniformMatrix4x3dv ; 

__attribute__((used)) static void load_GL_ARB_gpu_shader_fp64(GLADloadproc load) {
	if(!GLAD_GL_ARB_gpu_shader_fp64) return;
	glad_glUniform1d = (PFNGLUNIFORM1DPROC)load("glUniform1d");
	glad_glUniform2d = (PFNGLUNIFORM2DPROC)load("glUniform2d");
	glad_glUniform3d = (PFNGLUNIFORM3DPROC)load("glUniform3d");
	glad_glUniform4d = (PFNGLUNIFORM4DPROC)load("glUniform4d");
	glad_glUniform1dv = (PFNGLUNIFORM1DVPROC)load("glUniform1dv");
	glad_glUniform2dv = (PFNGLUNIFORM2DVPROC)load("glUniform2dv");
	glad_glUniform3dv = (PFNGLUNIFORM3DVPROC)load("glUniform3dv");
	glad_glUniform4dv = (PFNGLUNIFORM4DVPROC)load("glUniform4dv");
	glad_glUniformMatrix2dv = (PFNGLUNIFORMMATRIX2DVPROC)load("glUniformMatrix2dv");
	glad_glUniformMatrix3dv = (PFNGLUNIFORMMATRIX3DVPROC)load("glUniformMatrix3dv");
	glad_glUniformMatrix4dv = (PFNGLUNIFORMMATRIX4DVPROC)load("glUniformMatrix4dv");
	glad_glUniformMatrix2x3dv = (PFNGLUNIFORMMATRIX2X3DVPROC)load("glUniformMatrix2x3dv");
	glad_glUniformMatrix2x4dv = (PFNGLUNIFORMMATRIX2X4DVPROC)load("glUniformMatrix2x4dv");
	glad_glUniformMatrix3x2dv = (PFNGLUNIFORMMATRIX3X2DVPROC)load("glUniformMatrix3x2dv");
	glad_glUniformMatrix3x4dv = (PFNGLUNIFORMMATRIX3X4DVPROC)load("glUniformMatrix3x4dv");
	glad_glUniformMatrix4x2dv = (PFNGLUNIFORMMATRIX4X2DVPROC)load("glUniformMatrix4x2dv");
	glad_glUniformMatrix4x3dv = (PFNGLUNIFORMMATRIX4X3DVPROC)load("glUniformMatrix4x3dv");
	glad_glGetUniformdv = (PFNGLGETUNIFORMDVPROC)load("glGetUniformdv");
}