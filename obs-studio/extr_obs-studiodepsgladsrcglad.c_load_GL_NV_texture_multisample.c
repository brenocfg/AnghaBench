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
typedef  scalar_t__ PFNGLTEXTUREIMAGE3DMULTISAMPLENVPROC ;
typedef  scalar_t__ PFNGLTEXTUREIMAGE3DMULTISAMPLECOVERAGENVPROC ;
typedef  scalar_t__ PFNGLTEXTUREIMAGE2DMULTISAMPLENVPROC ;
typedef  scalar_t__ PFNGLTEXTUREIMAGE2DMULTISAMPLECOVERAGENVPROC ;
typedef  scalar_t__ PFNGLTEXIMAGE3DMULTISAMPLECOVERAGENVPROC ;
typedef  scalar_t__ PFNGLTEXIMAGE2DMULTISAMPLECOVERAGENVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_texture_multisample ; 
 scalar_t__ glad_glTexImage2DMultisampleCoverageNV ; 
 scalar_t__ glad_glTexImage3DMultisampleCoverageNV ; 
 scalar_t__ glad_glTextureImage2DMultisampleCoverageNV ; 
 scalar_t__ glad_glTextureImage2DMultisampleNV ; 
 scalar_t__ glad_glTextureImage3DMultisampleCoverageNV ; 
 scalar_t__ glad_glTextureImage3DMultisampleNV ; 

__attribute__((used)) static void load_GL_NV_texture_multisample(GLADloadproc load) {
	if(!GLAD_GL_NV_texture_multisample) return;
	glad_glTexImage2DMultisampleCoverageNV = (PFNGLTEXIMAGE2DMULTISAMPLECOVERAGENVPROC)load("glTexImage2DMultisampleCoverageNV");
	glad_glTexImage3DMultisampleCoverageNV = (PFNGLTEXIMAGE3DMULTISAMPLECOVERAGENVPROC)load("glTexImage3DMultisampleCoverageNV");
	glad_glTextureImage2DMultisampleNV = (PFNGLTEXTUREIMAGE2DMULTISAMPLENVPROC)load("glTextureImage2DMultisampleNV");
	glad_glTextureImage3DMultisampleNV = (PFNGLTEXTUREIMAGE3DMULTISAMPLENVPROC)load("glTextureImage3DMultisampleNV");
	glad_glTextureImage2DMultisampleCoverageNV = (PFNGLTEXTUREIMAGE2DMULTISAMPLECOVERAGENVPROC)load("glTextureImage2DMultisampleCoverageNV");
	glad_glTextureImage3DMultisampleCoverageNV = (PFNGLTEXTUREIMAGE3DMULTISAMPLECOVERAGENVPROC)load("glTextureImage3DMultisampleCoverageNV");
}