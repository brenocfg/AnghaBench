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
typedef  scalar_t__ PFNGLSAMPLECOVERAGEPROC ;
typedef  scalar_t__ PFNGLGETCOMPRESSEDTEXIMAGEPROC ;
typedef  scalar_t__ PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC ;
typedef  scalar_t__ PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC ;
typedef  scalar_t__ PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC ;
typedef  scalar_t__ PFNGLCOMPRESSEDTEXIMAGE3DPROC ;
typedef  scalar_t__ PFNGLCOMPRESSEDTEXIMAGE2DPROC ;
typedef  scalar_t__ PFNGLCOMPRESSEDTEXIMAGE1DPROC ;
typedef  scalar_t__ PFNGLACTIVETEXTUREPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_VERSION_1_3 ; 
 scalar_t__ glad_glActiveTexture ; 
 scalar_t__ glad_glCompressedTexImage1D ; 
 scalar_t__ glad_glCompressedTexImage2D ; 
 scalar_t__ glad_glCompressedTexImage3D ; 
 scalar_t__ glad_glCompressedTexSubImage1D ; 
 scalar_t__ glad_glCompressedTexSubImage2D ; 
 scalar_t__ glad_glCompressedTexSubImage3D ; 
 scalar_t__ glad_glGetCompressedTexImage ; 
 scalar_t__ glad_glSampleCoverage ; 

__attribute__((used)) static void load_GL_VERSION_1_3(GLADloadproc load) {
	if(!GLAD_GL_VERSION_1_3) return;
	glad_glActiveTexture = (PFNGLACTIVETEXTUREPROC)load("glActiveTexture");
	glad_glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)load("glSampleCoverage");
	glad_glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)load("glCompressedTexImage3D");
	glad_glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)load("glCompressedTexImage2D");
	glad_glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)load("glCompressedTexImage1D");
	glad_glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)load("glCompressedTexSubImage3D");
	glad_glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)load("glCompressedTexSubImage2D");
	glad_glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)load("glCompressedTexSubImage1D");
	glad_glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC)load("glGetCompressedTexImage");
}