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
typedef  scalar_t__ PFNGLUNIFORMUI64VNVPROC ;
typedef  scalar_t__ PFNGLUNIFORMUI64NVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORMUI64VNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORMUI64NVPROC ;
typedef  scalar_t__ PFNGLMAKENAMEDBUFFERRESIDENTNVPROC ;
typedef  scalar_t__ PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC ;
typedef  scalar_t__ PFNGLMAKEBUFFERRESIDENTNVPROC ;
typedef  scalar_t__ PFNGLMAKEBUFFERNONRESIDENTNVPROC ;
typedef  scalar_t__ PFNGLISNAMEDBUFFERRESIDENTNVPROC ;
typedef  scalar_t__ PFNGLISBUFFERRESIDENTNVPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMUI64VNVPROC ;
typedef  scalar_t__ PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC ;
typedef  scalar_t__ PFNGLGETINTEGERUI64VNVPROC ;
typedef  scalar_t__ PFNGLGETBUFFERPARAMETERUI64VNVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_shader_buffer_load ; 
 scalar_t__ glad_glGetBufferParameterui64vNV ; 
 scalar_t__ glad_glGetIntegerui64vNV ; 
 scalar_t__ glad_glGetNamedBufferParameterui64vNV ; 
 scalar_t__ glad_glGetUniformui64vNV ; 
 scalar_t__ glad_glIsBufferResidentNV ; 
 scalar_t__ glad_glIsNamedBufferResidentNV ; 
 scalar_t__ glad_glMakeBufferNonResidentNV ; 
 scalar_t__ glad_glMakeBufferResidentNV ; 
 scalar_t__ glad_glMakeNamedBufferNonResidentNV ; 
 scalar_t__ glad_glMakeNamedBufferResidentNV ; 
 scalar_t__ glad_glProgramUniformui64NV ; 
 scalar_t__ glad_glProgramUniformui64vNV ; 
 scalar_t__ glad_glUniformui64NV ; 
 scalar_t__ glad_glUniformui64vNV ; 

__attribute__((used)) static void load_GL_NV_shader_buffer_load(GLADloadproc load) {
	if(!GLAD_GL_NV_shader_buffer_load) return;
	glad_glMakeBufferResidentNV = (PFNGLMAKEBUFFERRESIDENTNVPROC)load("glMakeBufferResidentNV");
	glad_glMakeBufferNonResidentNV = (PFNGLMAKEBUFFERNONRESIDENTNVPROC)load("glMakeBufferNonResidentNV");
	glad_glIsBufferResidentNV = (PFNGLISBUFFERRESIDENTNVPROC)load("glIsBufferResidentNV");
	glad_glMakeNamedBufferResidentNV = (PFNGLMAKENAMEDBUFFERRESIDENTNVPROC)load("glMakeNamedBufferResidentNV");
	glad_glMakeNamedBufferNonResidentNV = (PFNGLMAKENAMEDBUFFERNONRESIDENTNVPROC)load("glMakeNamedBufferNonResidentNV");
	glad_glIsNamedBufferResidentNV = (PFNGLISNAMEDBUFFERRESIDENTNVPROC)load("glIsNamedBufferResidentNV");
	glad_glGetBufferParameterui64vNV = (PFNGLGETBUFFERPARAMETERUI64VNVPROC)load("glGetBufferParameterui64vNV");
	glad_glGetNamedBufferParameterui64vNV = (PFNGLGETNAMEDBUFFERPARAMETERUI64VNVPROC)load("glGetNamedBufferParameterui64vNV");
	glad_glGetIntegerui64vNV = (PFNGLGETINTEGERUI64VNVPROC)load("glGetIntegerui64vNV");
	glad_glUniformui64NV = (PFNGLUNIFORMUI64NVPROC)load("glUniformui64NV");
	glad_glUniformui64vNV = (PFNGLUNIFORMUI64VNVPROC)load("glUniformui64vNV");
	glad_glGetUniformui64vNV = (PFNGLGETUNIFORMUI64VNVPROC)load("glGetUniformui64vNV");
	glad_glProgramUniformui64NV = (PFNGLPROGRAMUNIFORMUI64NVPROC)load("glProgramUniformui64NV");
	glad_glProgramUniformui64vNV = (PFNGLPROGRAMUNIFORMUI64VNVPROC)load("glProgramUniformui64vNV");
}