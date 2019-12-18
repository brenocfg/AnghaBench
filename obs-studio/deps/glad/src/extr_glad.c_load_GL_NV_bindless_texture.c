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
typedef  scalar_t__ PFNGLUNIFORMHANDLEUI64VNVPROC ;
typedef  scalar_t__ PFNGLUNIFORMHANDLEUI64NVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC ;
typedef  scalar_t__ PFNGLMAKETEXTUREHANDLERESIDENTNVPROC ;
typedef  scalar_t__ PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC ;
typedef  scalar_t__ PFNGLMAKEIMAGEHANDLERESIDENTNVPROC ;
typedef  scalar_t__ PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC ;
typedef  scalar_t__ PFNGLISTEXTUREHANDLERESIDENTNVPROC ;
typedef  scalar_t__ PFNGLISIMAGEHANDLERESIDENTNVPROC ;
typedef  scalar_t__ PFNGLGETTEXTURESAMPLERHANDLENVPROC ;
typedef  scalar_t__ PFNGLGETTEXTUREHANDLENVPROC ;
typedef  scalar_t__ PFNGLGETIMAGEHANDLENVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_bindless_texture ; 
 scalar_t__ glad_glGetImageHandleNV ; 
 scalar_t__ glad_glGetTextureHandleNV ; 
 scalar_t__ glad_glGetTextureSamplerHandleNV ; 
 scalar_t__ glad_glIsImageHandleResidentNV ; 
 scalar_t__ glad_glIsTextureHandleResidentNV ; 
 scalar_t__ glad_glMakeImageHandleNonResidentNV ; 
 scalar_t__ glad_glMakeImageHandleResidentNV ; 
 scalar_t__ glad_glMakeTextureHandleNonResidentNV ; 
 scalar_t__ glad_glMakeTextureHandleResidentNV ; 
 scalar_t__ glad_glProgramUniformHandleui64NV ; 
 scalar_t__ glad_glProgramUniformHandleui64vNV ; 
 scalar_t__ glad_glUniformHandleui64NV ; 
 scalar_t__ glad_glUniformHandleui64vNV ; 

__attribute__((used)) static void load_GL_NV_bindless_texture(GLADloadproc load) {
	if(!GLAD_GL_NV_bindless_texture) return;
	glad_glGetTextureHandleNV = (PFNGLGETTEXTUREHANDLENVPROC)load("glGetTextureHandleNV");
	glad_glGetTextureSamplerHandleNV = (PFNGLGETTEXTURESAMPLERHANDLENVPROC)load("glGetTextureSamplerHandleNV");
	glad_glMakeTextureHandleResidentNV = (PFNGLMAKETEXTUREHANDLERESIDENTNVPROC)load("glMakeTextureHandleResidentNV");
	glad_glMakeTextureHandleNonResidentNV = (PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC)load("glMakeTextureHandleNonResidentNV");
	glad_glGetImageHandleNV = (PFNGLGETIMAGEHANDLENVPROC)load("glGetImageHandleNV");
	glad_glMakeImageHandleResidentNV = (PFNGLMAKEIMAGEHANDLERESIDENTNVPROC)load("glMakeImageHandleResidentNV");
	glad_glMakeImageHandleNonResidentNV = (PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC)load("glMakeImageHandleNonResidentNV");
	glad_glUniformHandleui64NV = (PFNGLUNIFORMHANDLEUI64NVPROC)load("glUniformHandleui64NV");
	glad_glUniformHandleui64vNV = (PFNGLUNIFORMHANDLEUI64VNVPROC)load("glUniformHandleui64vNV");
	glad_glProgramUniformHandleui64NV = (PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC)load("glProgramUniformHandleui64NV");
	glad_glProgramUniformHandleui64vNV = (PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC)load("glProgramUniformHandleui64vNV");
	glad_glIsTextureHandleResidentNV = (PFNGLISTEXTUREHANDLERESIDENTNVPROC)load("glIsTextureHandleResidentNV");
	glad_glIsImageHandleResidentNV = (PFNGLISIMAGEHANDLERESIDENTNVPROC)load("glIsImageHandleResidentNV");
}