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
typedef  scalar_t__ PFNGLLOADIDENTITYDEFORMATIONMAPSGIXPROC ;
typedef  scalar_t__ PFNGLDEFORMSGIXPROC ;
typedef  scalar_t__ PFNGLDEFORMATIONMAP3FSGIXPROC ;
typedef  scalar_t__ PFNGLDEFORMATIONMAP3DSGIXPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_SGIX_polynomial_ffd ; 
 scalar_t__ glad_glDeformSGIX ; 
 scalar_t__ glad_glDeformationMap3dSGIX ; 
 scalar_t__ glad_glDeformationMap3fSGIX ; 
 scalar_t__ glad_glLoadIdentityDeformationMapSGIX ; 

__attribute__((used)) static void load_GL_SGIX_polynomial_ffd(GLADloadproc load) {
	if(!GLAD_GL_SGIX_polynomial_ffd) return;
	glad_glDeformationMap3dSGIX = (PFNGLDEFORMATIONMAP3DSGIXPROC)load("glDeformationMap3dSGIX");
	glad_glDeformationMap3fSGIX = (PFNGLDEFORMATIONMAP3FSGIXPROC)load("glDeformationMap3fSGIX");
	glad_glDeformSGIX = (PFNGLDEFORMSGIXPROC)load("glDeformSGIX");
	glad_glLoadIdentityDeformationMapSGIX = (PFNGLLOADIDENTITYDEFORMATIONMAPSGIXPROC)load("glLoadIdentityDeformationMapSGIX");
}