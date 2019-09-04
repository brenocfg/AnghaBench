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
typedef  scalar_t__ PFNGLUNIFORM4UI64VNVPROC ;
typedef  scalar_t__ PFNGLUNIFORM4UI64NVPROC ;
typedef  scalar_t__ PFNGLUNIFORM4I64VNVPROC ;
typedef  scalar_t__ PFNGLUNIFORM4I64NVPROC ;
typedef  scalar_t__ PFNGLUNIFORM3UI64VNVPROC ;
typedef  scalar_t__ PFNGLUNIFORM3UI64NVPROC ;
typedef  scalar_t__ PFNGLUNIFORM3I64VNVPROC ;
typedef  scalar_t__ PFNGLUNIFORM3I64NVPROC ;
typedef  scalar_t__ PFNGLUNIFORM2UI64VNVPROC ;
typedef  scalar_t__ PFNGLUNIFORM2UI64NVPROC ;
typedef  scalar_t__ PFNGLUNIFORM2I64VNVPROC ;
typedef  scalar_t__ PFNGLUNIFORM2I64NVPROC ;
typedef  scalar_t__ PFNGLUNIFORM1UI64VNVPROC ;
typedef  scalar_t__ PFNGLUNIFORM1UI64NVPROC ;
typedef  scalar_t__ PFNGLUNIFORM1I64VNVPROC ;
typedef  scalar_t__ PFNGLUNIFORM1I64NVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORM4UI64VNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORM4UI64NVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORM4I64VNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORM4I64NVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORM3UI64VNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORM3UI64NVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORM3I64VNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORM3I64NVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORM2UI64VNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORM2UI64NVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORM2I64VNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORM2I64NVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORM1UI64VNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORM1UI64NVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORM1I64VNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORM1I64NVPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMI64VNVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_gpu_shader5 ; 
 scalar_t__ glad_glGetUniformi64vNV ; 
 scalar_t__ glad_glProgramUniform1i64NV ; 
 scalar_t__ glad_glProgramUniform1i64vNV ; 
 scalar_t__ glad_glProgramUniform1ui64NV ; 
 scalar_t__ glad_glProgramUniform1ui64vNV ; 
 scalar_t__ glad_glProgramUniform2i64NV ; 
 scalar_t__ glad_glProgramUniform2i64vNV ; 
 scalar_t__ glad_glProgramUniform2ui64NV ; 
 scalar_t__ glad_glProgramUniform2ui64vNV ; 
 scalar_t__ glad_glProgramUniform3i64NV ; 
 scalar_t__ glad_glProgramUniform3i64vNV ; 
 scalar_t__ glad_glProgramUniform3ui64NV ; 
 scalar_t__ glad_glProgramUniform3ui64vNV ; 
 scalar_t__ glad_glProgramUniform4i64NV ; 
 scalar_t__ glad_glProgramUniform4i64vNV ; 
 scalar_t__ glad_glProgramUniform4ui64NV ; 
 scalar_t__ glad_glProgramUniform4ui64vNV ; 
 scalar_t__ glad_glUniform1i64NV ; 
 scalar_t__ glad_glUniform1i64vNV ; 
 scalar_t__ glad_glUniform1ui64NV ; 
 scalar_t__ glad_glUniform1ui64vNV ; 
 scalar_t__ glad_glUniform2i64NV ; 
 scalar_t__ glad_glUniform2i64vNV ; 
 scalar_t__ glad_glUniform2ui64NV ; 
 scalar_t__ glad_glUniform2ui64vNV ; 
 scalar_t__ glad_glUniform3i64NV ; 
 scalar_t__ glad_glUniform3i64vNV ; 
 scalar_t__ glad_glUniform3ui64NV ; 
 scalar_t__ glad_glUniform3ui64vNV ; 
 scalar_t__ glad_glUniform4i64NV ; 
 scalar_t__ glad_glUniform4i64vNV ; 
 scalar_t__ glad_glUniform4ui64NV ; 
 scalar_t__ glad_glUniform4ui64vNV ; 

__attribute__((used)) static void load_GL_NV_gpu_shader5(GLADloadproc load) {
	if(!GLAD_GL_NV_gpu_shader5) return;
	glad_glUniform1i64NV = (PFNGLUNIFORM1I64NVPROC)load("glUniform1i64NV");
	glad_glUniform2i64NV = (PFNGLUNIFORM2I64NVPROC)load("glUniform2i64NV");
	glad_glUniform3i64NV = (PFNGLUNIFORM3I64NVPROC)load("glUniform3i64NV");
	glad_glUniform4i64NV = (PFNGLUNIFORM4I64NVPROC)load("glUniform4i64NV");
	glad_glUniform1i64vNV = (PFNGLUNIFORM1I64VNVPROC)load("glUniform1i64vNV");
	glad_glUniform2i64vNV = (PFNGLUNIFORM2I64VNVPROC)load("glUniform2i64vNV");
	glad_glUniform3i64vNV = (PFNGLUNIFORM3I64VNVPROC)load("glUniform3i64vNV");
	glad_glUniform4i64vNV = (PFNGLUNIFORM4I64VNVPROC)load("glUniform4i64vNV");
	glad_glUniform1ui64NV = (PFNGLUNIFORM1UI64NVPROC)load("glUniform1ui64NV");
	glad_glUniform2ui64NV = (PFNGLUNIFORM2UI64NVPROC)load("glUniform2ui64NV");
	glad_glUniform3ui64NV = (PFNGLUNIFORM3UI64NVPROC)load("glUniform3ui64NV");
	glad_glUniform4ui64NV = (PFNGLUNIFORM4UI64NVPROC)load("glUniform4ui64NV");
	glad_glUniform1ui64vNV = (PFNGLUNIFORM1UI64VNVPROC)load("glUniform1ui64vNV");
	glad_glUniform2ui64vNV = (PFNGLUNIFORM2UI64VNVPROC)load("glUniform2ui64vNV");
	glad_glUniform3ui64vNV = (PFNGLUNIFORM3UI64VNVPROC)load("glUniform3ui64vNV");
	glad_glUniform4ui64vNV = (PFNGLUNIFORM4UI64VNVPROC)load("glUniform4ui64vNV");
	glad_glGetUniformi64vNV = (PFNGLGETUNIFORMI64VNVPROC)load("glGetUniformi64vNV");
	glad_glProgramUniform1i64NV = (PFNGLPROGRAMUNIFORM1I64NVPROC)load("glProgramUniform1i64NV");
	glad_glProgramUniform2i64NV = (PFNGLPROGRAMUNIFORM2I64NVPROC)load("glProgramUniform2i64NV");
	glad_glProgramUniform3i64NV = (PFNGLPROGRAMUNIFORM3I64NVPROC)load("glProgramUniform3i64NV");
	glad_glProgramUniform4i64NV = (PFNGLPROGRAMUNIFORM4I64NVPROC)load("glProgramUniform4i64NV");
	glad_glProgramUniform1i64vNV = (PFNGLPROGRAMUNIFORM1I64VNVPROC)load("glProgramUniform1i64vNV");
	glad_glProgramUniform2i64vNV = (PFNGLPROGRAMUNIFORM2I64VNVPROC)load("glProgramUniform2i64vNV");
	glad_glProgramUniform3i64vNV = (PFNGLPROGRAMUNIFORM3I64VNVPROC)load("glProgramUniform3i64vNV");
	glad_glProgramUniform4i64vNV = (PFNGLPROGRAMUNIFORM4I64VNVPROC)load("glProgramUniform4i64vNV");
	glad_glProgramUniform1ui64NV = (PFNGLPROGRAMUNIFORM1UI64NVPROC)load("glProgramUniform1ui64NV");
	glad_glProgramUniform2ui64NV = (PFNGLPROGRAMUNIFORM2UI64NVPROC)load("glProgramUniform2ui64NV");
	glad_glProgramUniform3ui64NV = (PFNGLPROGRAMUNIFORM3UI64NVPROC)load("glProgramUniform3ui64NV");
	glad_glProgramUniform4ui64NV = (PFNGLPROGRAMUNIFORM4UI64NVPROC)load("glProgramUniform4ui64NV");
	glad_glProgramUniform1ui64vNV = (PFNGLPROGRAMUNIFORM1UI64VNVPROC)load("glProgramUniform1ui64vNV");
	glad_glProgramUniform2ui64vNV = (PFNGLPROGRAMUNIFORM2UI64VNVPROC)load("glProgramUniform2ui64vNV");
	glad_glProgramUniform3ui64vNV = (PFNGLPROGRAMUNIFORM3UI64VNVPROC)load("glProgramUniform3ui64vNV");
	glad_glProgramUniform4ui64vNV = (PFNGLPROGRAMUNIFORM4UI64VNVPROC)load("glProgramUniform4ui64vNV");
}