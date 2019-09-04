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
typedef  scalar_t__ PFNGLSETFRAGMENTSHADERCONSTANTATIPROC ;
typedef  scalar_t__ PFNGLSAMPLEMAPATIPROC ;
typedef  scalar_t__ PFNGLPASSTEXCOORDATIPROC ;
typedef  scalar_t__ PFNGLGENFRAGMENTSHADERSATIPROC ;
typedef  scalar_t__ PFNGLENDFRAGMENTSHADERATIPROC ;
typedef  scalar_t__ PFNGLDELETEFRAGMENTSHADERATIPROC ;
typedef  scalar_t__ PFNGLCOLORFRAGMENTOP3ATIPROC ;
typedef  scalar_t__ PFNGLCOLORFRAGMENTOP2ATIPROC ;
typedef  scalar_t__ PFNGLCOLORFRAGMENTOP1ATIPROC ;
typedef  scalar_t__ PFNGLBINDFRAGMENTSHADERATIPROC ;
typedef  scalar_t__ PFNGLBEGINFRAGMENTSHADERATIPROC ;
typedef  scalar_t__ PFNGLALPHAFRAGMENTOP3ATIPROC ;
typedef  scalar_t__ PFNGLALPHAFRAGMENTOP2ATIPROC ;
typedef  scalar_t__ PFNGLALPHAFRAGMENTOP1ATIPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ATI_fragment_shader ; 
 scalar_t__ glad_glAlphaFragmentOp1ATI ; 
 scalar_t__ glad_glAlphaFragmentOp2ATI ; 
 scalar_t__ glad_glAlphaFragmentOp3ATI ; 
 scalar_t__ glad_glBeginFragmentShaderATI ; 
 scalar_t__ glad_glBindFragmentShaderATI ; 
 scalar_t__ glad_glColorFragmentOp1ATI ; 
 scalar_t__ glad_glColorFragmentOp2ATI ; 
 scalar_t__ glad_glColorFragmentOp3ATI ; 
 scalar_t__ glad_glDeleteFragmentShaderATI ; 
 scalar_t__ glad_glEndFragmentShaderATI ; 
 scalar_t__ glad_glGenFragmentShadersATI ; 
 scalar_t__ glad_glPassTexCoordATI ; 
 scalar_t__ glad_glSampleMapATI ; 
 scalar_t__ glad_glSetFragmentShaderConstantATI ; 

__attribute__((used)) static void load_GL_ATI_fragment_shader(GLADloadproc load) {
	if(!GLAD_GL_ATI_fragment_shader) return;
	glad_glGenFragmentShadersATI = (PFNGLGENFRAGMENTSHADERSATIPROC)load("glGenFragmentShadersATI");
	glad_glBindFragmentShaderATI = (PFNGLBINDFRAGMENTSHADERATIPROC)load("glBindFragmentShaderATI");
	glad_glDeleteFragmentShaderATI = (PFNGLDELETEFRAGMENTSHADERATIPROC)load("glDeleteFragmentShaderATI");
	glad_glBeginFragmentShaderATI = (PFNGLBEGINFRAGMENTSHADERATIPROC)load("glBeginFragmentShaderATI");
	glad_glEndFragmentShaderATI = (PFNGLENDFRAGMENTSHADERATIPROC)load("glEndFragmentShaderATI");
	glad_glPassTexCoordATI = (PFNGLPASSTEXCOORDATIPROC)load("glPassTexCoordATI");
	glad_glSampleMapATI = (PFNGLSAMPLEMAPATIPROC)load("glSampleMapATI");
	glad_glColorFragmentOp1ATI = (PFNGLCOLORFRAGMENTOP1ATIPROC)load("glColorFragmentOp1ATI");
	glad_glColorFragmentOp2ATI = (PFNGLCOLORFRAGMENTOP2ATIPROC)load("glColorFragmentOp2ATI");
	glad_glColorFragmentOp3ATI = (PFNGLCOLORFRAGMENTOP3ATIPROC)load("glColorFragmentOp3ATI");
	glad_glAlphaFragmentOp1ATI = (PFNGLALPHAFRAGMENTOP1ATIPROC)load("glAlphaFragmentOp1ATI");
	glad_glAlphaFragmentOp2ATI = (PFNGLALPHAFRAGMENTOP2ATIPROC)load("glAlphaFragmentOp2ATI");
	glad_glAlphaFragmentOp3ATI = (PFNGLALPHAFRAGMENTOP3ATIPROC)load("glAlphaFragmentOp3ATI");
	glad_glSetFragmentShaderConstantATI = (PFNGLSETFRAGMENTSHADERCONSTANTATIPROC)load("glSetFragmentShaderConstantATI");
}