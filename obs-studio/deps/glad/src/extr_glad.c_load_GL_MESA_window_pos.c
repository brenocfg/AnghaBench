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
typedef  scalar_t__ PFNGLWINDOWPOS4SVMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS4SMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS4IVMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS4IMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS4FVMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS4FMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS4DVMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS4DMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3SVMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3SMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3IVMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3IMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3FVMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3FMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3DVMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS3DMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2SVMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2SMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2IVMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2IMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2FVMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2FMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2DVMESAPROC ;
typedef  scalar_t__ PFNGLWINDOWPOS2DMESAPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_MESA_window_pos ; 
 scalar_t__ glad_glWindowPos2dMESA ; 
 scalar_t__ glad_glWindowPos2dvMESA ; 
 scalar_t__ glad_glWindowPos2fMESA ; 
 scalar_t__ glad_glWindowPos2fvMESA ; 
 scalar_t__ glad_glWindowPos2iMESA ; 
 scalar_t__ glad_glWindowPos2ivMESA ; 
 scalar_t__ glad_glWindowPos2sMESA ; 
 scalar_t__ glad_glWindowPos2svMESA ; 
 scalar_t__ glad_glWindowPos3dMESA ; 
 scalar_t__ glad_glWindowPos3dvMESA ; 
 scalar_t__ glad_glWindowPos3fMESA ; 
 scalar_t__ glad_glWindowPos3fvMESA ; 
 scalar_t__ glad_glWindowPos3iMESA ; 
 scalar_t__ glad_glWindowPos3ivMESA ; 
 scalar_t__ glad_glWindowPos3sMESA ; 
 scalar_t__ glad_glWindowPos3svMESA ; 
 scalar_t__ glad_glWindowPos4dMESA ; 
 scalar_t__ glad_glWindowPos4dvMESA ; 
 scalar_t__ glad_glWindowPos4fMESA ; 
 scalar_t__ glad_glWindowPos4fvMESA ; 
 scalar_t__ glad_glWindowPos4iMESA ; 
 scalar_t__ glad_glWindowPos4ivMESA ; 
 scalar_t__ glad_glWindowPos4sMESA ; 
 scalar_t__ glad_glWindowPos4svMESA ; 

__attribute__((used)) static void load_GL_MESA_window_pos(GLADloadproc load) {
	if(!GLAD_GL_MESA_window_pos) return;
	glad_glWindowPos2dMESA = (PFNGLWINDOWPOS2DMESAPROC)load("glWindowPos2dMESA");
	glad_glWindowPos2dvMESA = (PFNGLWINDOWPOS2DVMESAPROC)load("glWindowPos2dvMESA");
	glad_glWindowPos2fMESA = (PFNGLWINDOWPOS2FMESAPROC)load("glWindowPos2fMESA");
	glad_glWindowPos2fvMESA = (PFNGLWINDOWPOS2FVMESAPROC)load("glWindowPos2fvMESA");
	glad_glWindowPos2iMESA = (PFNGLWINDOWPOS2IMESAPROC)load("glWindowPos2iMESA");
	glad_glWindowPos2ivMESA = (PFNGLWINDOWPOS2IVMESAPROC)load("glWindowPos2ivMESA");
	glad_glWindowPos2sMESA = (PFNGLWINDOWPOS2SMESAPROC)load("glWindowPos2sMESA");
	glad_glWindowPos2svMESA = (PFNGLWINDOWPOS2SVMESAPROC)load("glWindowPos2svMESA");
	glad_glWindowPos3dMESA = (PFNGLWINDOWPOS3DMESAPROC)load("glWindowPos3dMESA");
	glad_glWindowPos3dvMESA = (PFNGLWINDOWPOS3DVMESAPROC)load("glWindowPos3dvMESA");
	glad_glWindowPos3fMESA = (PFNGLWINDOWPOS3FMESAPROC)load("glWindowPos3fMESA");
	glad_glWindowPos3fvMESA = (PFNGLWINDOWPOS3FVMESAPROC)load("glWindowPos3fvMESA");
	glad_glWindowPos3iMESA = (PFNGLWINDOWPOS3IMESAPROC)load("glWindowPos3iMESA");
	glad_glWindowPos3ivMESA = (PFNGLWINDOWPOS3IVMESAPROC)load("glWindowPos3ivMESA");
	glad_glWindowPos3sMESA = (PFNGLWINDOWPOS3SMESAPROC)load("glWindowPos3sMESA");
	glad_glWindowPos3svMESA = (PFNGLWINDOWPOS3SVMESAPROC)load("glWindowPos3svMESA");
	glad_glWindowPos4dMESA = (PFNGLWINDOWPOS4DMESAPROC)load("glWindowPos4dMESA");
	glad_glWindowPos4dvMESA = (PFNGLWINDOWPOS4DVMESAPROC)load("glWindowPos4dvMESA");
	glad_glWindowPos4fMESA = (PFNGLWINDOWPOS4FMESAPROC)load("glWindowPos4fMESA");
	glad_glWindowPos4fvMESA = (PFNGLWINDOWPOS4FVMESAPROC)load("glWindowPos4fvMESA");
	glad_glWindowPos4iMESA = (PFNGLWINDOWPOS4IMESAPROC)load("glWindowPos4iMESA");
	glad_glWindowPos4ivMESA = (PFNGLWINDOWPOS4IVMESAPROC)load("glWindowPos4ivMESA");
	glad_glWindowPos4sMESA = (PFNGLWINDOWPOS4SMESAPROC)load("glWindowPos4sMESA");
	glad_glWindowPos4svMESA = (PFNGLWINDOWPOS4SVMESAPROC)load("glWindowPos4svMESA");
}