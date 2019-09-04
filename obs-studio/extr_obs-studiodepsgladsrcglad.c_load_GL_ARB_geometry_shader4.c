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
typedef  scalar_t__ PFNGLPROGRAMPARAMETERIARBPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERTEXTURELAYERARBPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERTEXTUREFACEARBPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERTEXTUREARBPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_geometry_shader4 ; 
 scalar_t__ glad_glFramebufferTextureARB ; 
 scalar_t__ glad_glFramebufferTextureFaceARB ; 
 scalar_t__ glad_glFramebufferTextureLayerARB ; 
 scalar_t__ glad_glProgramParameteriARB ; 

__attribute__((used)) static void load_GL_ARB_geometry_shader4(GLADloadproc load) {
	if(!GLAD_GL_ARB_geometry_shader4) return;
	glad_glProgramParameteriARB = (PFNGLPROGRAMPARAMETERIARBPROC)load("glProgramParameteriARB");
	glad_glFramebufferTextureARB = (PFNGLFRAMEBUFFERTEXTUREARBPROC)load("glFramebufferTextureARB");
	glad_glFramebufferTextureLayerARB = (PFNGLFRAMEBUFFERTEXTURELAYERARBPROC)load("glFramebufferTextureLayerARB");
	glad_glFramebufferTextureFaceARB = (PFNGLFRAMEBUFFERTEXTUREFACEARBPROC)load("glFramebufferTextureFaceARB");
}