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
typedef  scalar_t__ PFNGLPROGRAMVERTEXLIMITNVPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC ;
typedef  scalar_t__ PFNGLFRAMEBUFFERTEXTUREEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_geometry_program4 ; 
 scalar_t__ glad_glFramebufferTextureEXT ; 
 scalar_t__ glad_glFramebufferTextureFaceEXT ; 
 scalar_t__ glad_glFramebufferTextureLayerEXT ; 
 scalar_t__ glad_glProgramVertexLimitNV ; 

__attribute__((used)) static void load_GL_NV_geometry_program4(GLADloadproc load) {
	if(!GLAD_GL_NV_geometry_program4) return;
	glad_glProgramVertexLimitNV = (PFNGLPROGRAMVERTEXLIMITNVPROC)load("glProgramVertexLimitNV");
	glad_glFramebufferTextureEXT = (PFNGLFRAMEBUFFERTEXTUREEXTPROC)load("glFramebufferTextureEXT");
	glad_glFramebufferTextureLayerEXT = (PFNGLFRAMEBUFFERTEXTURELAYEREXTPROC)load("glFramebufferTextureLayerEXT");
	glad_glFramebufferTextureFaceEXT = (PFNGLFRAMEBUFFERTEXTUREFACEEXTPROC)load("glFramebufferTextureFaceEXT");
}