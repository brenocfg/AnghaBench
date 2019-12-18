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
typedef  scalar_t__ PFNGLVERTEXATTRIBL1UI64VARBPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL1UI64ARBPROC ;
typedef  scalar_t__ PFNGLUNIFORMHANDLEUI64VARBPROC ;
typedef  scalar_t__ PFNGLUNIFORMHANDLEUI64ARBPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC ;
typedef  scalar_t__ PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC ;
typedef  scalar_t__ PFNGLMAKETEXTUREHANDLERESIDENTARBPROC ;
typedef  scalar_t__ PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC ;
typedef  scalar_t__ PFNGLMAKEIMAGEHANDLERESIDENTARBPROC ;
typedef  scalar_t__ PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC ;
typedef  scalar_t__ PFNGLISTEXTUREHANDLERESIDENTARBPROC ;
typedef  scalar_t__ PFNGLISIMAGEHANDLERESIDENTARBPROC ;
typedef  scalar_t__ PFNGLGETVERTEXATTRIBLUI64VARBPROC ;
typedef  scalar_t__ PFNGLGETTEXTURESAMPLERHANDLEARBPROC ;
typedef  scalar_t__ PFNGLGETTEXTUREHANDLEARBPROC ;
typedef  scalar_t__ PFNGLGETIMAGEHANDLEARBPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_bindless_texture ; 
 scalar_t__ glad_glGetImageHandleARB ; 
 scalar_t__ glad_glGetTextureHandleARB ; 
 scalar_t__ glad_glGetTextureSamplerHandleARB ; 
 scalar_t__ glad_glGetVertexAttribLui64vARB ; 
 scalar_t__ glad_glIsImageHandleResidentARB ; 
 scalar_t__ glad_glIsTextureHandleResidentARB ; 
 scalar_t__ glad_glMakeImageHandleNonResidentARB ; 
 scalar_t__ glad_glMakeImageHandleResidentARB ; 
 scalar_t__ glad_glMakeTextureHandleNonResidentARB ; 
 scalar_t__ glad_glMakeTextureHandleResidentARB ; 
 scalar_t__ glad_glProgramUniformHandleui64ARB ; 
 scalar_t__ glad_glProgramUniformHandleui64vARB ; 
 scalar_t__ glad_glUniformHandleui64ARB ; 
 scalar_t__ glad_glUniformHandleui64vARB ; 
 scalar_t__ glad_glVertexAttribL1ui64ARB ; 
 scalar_t__ glad_glVertexAttribL1ui64vARB ; 

__attribute__((used)) static void load_GL_ARB_bindless_texture(GLADloadproc load) {
	if(!GLAD_GL_ARB_bindless_texture) return;
	glad_glGetTextureHandleARB = (PFNGLGETTEXTUREHANDLEARBPROC)load("glGetTextureHandleARB");
	glad_glGetTextureSamplerHandleARB = (PFNGLGETTEXTURESAMPLERHANDLEARBPROC)load("glGetTextureSamplerHandleARB");
	glad_glMakeTextureHandleResidentARB = (PFNGLMAKETEXTUREHANDLERESIDENTARBPROC)load("glMakeTextureHandleResidentARB");
	glad_glMakeTextureHandleNonResidentARB = (PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC)load("glMakeTextureHandleNonResidentARB");
	glad_glGetImageHandleARB = (PFNGLGETIMAGEHANDLEARBPROC)load("glGetImageHandleARB");
	glad_glMakeImageHandleResidentARB = (PFNGLMAKEIMAGEHANDLERESIDENTARBPROC)load("glMakeImageHandleResidentARB");
	glad_glMakeImageHandleNonResidentARB = (PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC)load("glMakeImageHandleNonResidentARB");
	glad_glUniformHandleui64ARB = (PFNGLUNIFORMHANDLEUI64ARBPROC)load("glUniformHandleui64ARB");
	glad_glUniformHandleui64vARB = (PFNGLUNIFORMHANDLEUI64VARBPROC)load("glUniformHandleui64vARB");
	glad_glProgramUniformHandleui64ARB = (PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC)load("glProgramUniformHandleui64ARB");
	glad_glProgramUniformHandleui64vARB = (PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC)load("glProgramUniformHandleui64vARB");
	glad_glIsTextureHandleResidentARB = (PFNGLISTEXTUREHANDLERESIDENTARBPROC)load("glIsTextureHandleResidentARB");
	glad_glIsImageHandleResidentARB = (PFNGLISIMAGEHANDLERESIDENTARBPROC)load("glIsImageHandleResidentARB");
	glad_glVertexAttribL1ui64ARB = (PFNGLVERTEXATTRIBL1UI64ARBPROC)load("glVertexAttribL1ui64ARB");
	glad_glVertexAttribL1ui64vARB = (PFNGLVERTEXATTRIBL1UI64VARBPROC)load("glVertexAttribL1ui64vARB");
	glad_glGetVertexAttribLui64vARB = (PFNGLGETVERTEXATTRIBLUI64VARBPROC)load("glGetVertexAttribLui64vARB");
}