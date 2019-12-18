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
typedef  scalar_t__ PFNGLTANGENTPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3SVEXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3SEXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3IVEXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3IEXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3FVEXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3FEXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3DVEXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3DEXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3BVEXTPROC ;
typedef  scalar_t__ PFNGLTANGENT3BEXTPROC ;
typedef  scalar_t__ PFNGLBINORMALPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3SVEXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3SEXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3IVEXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3IEXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3FVEXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3FEXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3DVEXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3DEXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3BVEXTPROC ;
typedef  scalar_t__ PFNGLBINORMAL3BEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_coordinate_frame ; 
 scalar_t__ glad_glBinormal3bEXT ; 
 scalar_t__ glad_glBinormal3bvEXT ; 
 scalar_t__ glad_glBinormal3dEXT ; 
 scalar_t__ glad_glBinormal3dvEXT ; 
 scalar_t__ glad_glBinormal3fEXT ; 
 scalar_t__ glad_glBinormal3fvEXT ; 
 scalar_t__ glad_glBinormal3iEXT ; 
 scalar_t__ glad_glBinormal3ivEXT ; 
 scalar_t__ glad_glBinormal3sEXT ; 
 scalar_t__ glad_glBinormal3svEXT ; 
 scalar_t__ glad_glBinormalPointerEXT ; 
 scalar_t__ glad_glTangent3bEXT ; 
 scalar_t__ glad_glTangent3bvEXT ; 
 scalar_t__ glad_glTangent3dEXT ; 
 scalar_t__ glad_glTangent3dvEXT ; 
 scalar_t__ glad_glTangent3fEXT ; 
 scalar_t__ glad_glTangent3fvEXT ; 
 scalar_t__ glad_glTangent3iEXT ; 
 scalar_t__ glad_glTangent3ivEXT ; 
 scalar_t__ glad_glTangent3sEXT ; 
 scalar_t__ glad_glTangent3svEXT ; 
 scalar_t__ glad_glTangentPointerEXT ; 

__attribute__((used)) static void load_GL_EXT_coordinate_frame(GLADloadproc load) {
	if(!GLAD_GL_EXT_coordinate_frame) return;
	glad_glTangent3bEXT = (PFNGLTANGENT3BEXTPROC)load("glTangent3bEXT");
	glad_glTangent3bvEXT = (PFNGLTANGENT3BVEXTPROC)load("glTangent3bvEXT");
	glad_glTangent3dEXT = (PFNGLTANGENT3DEXTPROC)load("glTangent3dEXT");
	glad_glTangent3dvEXT = (PFNGLTANGENT3DVEXTPROC)load("glTangent3dvEXT");
	glad_glTangent3fEXT = (PFNGLTANGENT3FEXTPROC)load("glTangent3fEXT");
	glad_glTangent3fvEXT = (PFNGLTANGENT3FVEXTPROC)load("glTangent3fvEXT");
	glad_glTangent3iEXT = (PFNGLTANGENT3IEXTPROC)load("glTangent3iEXT");
	glad_glTangent3ivEXT = (PFNGLTANGENT3IVEXTPROC)load("glTangent3ivEXT");
	glad_glTangent3sEXT = (PFNGLTANGENT3SEXTPROC)load("glTangent3sEXT");
	glad_glTangent3svEXT = (PFNGLTANGENT3SVEXTPROC)load("glTangent3svEXT");
	glad_glBinormal3bEXT = (PFNGLBINORMAL3BEXTPROC)load("glBinormal3bEXT");
	glad_glBinormal3bvEXT = (PFNGLBINORMAL3BVEXTPROC)load("glBinormal3bvEXT");
	glad_glBinormal3dEXT = (PFNGLBINORMAL3DEXTPROC)load("glBinormal3dEXT");
	glad_glBinormal3dvEXT = (PFNGLBINORMAL3DVEXTPROC)load("glBinormal3dvEXT");
	glad_glBinormal3fEXT = (PFNGLBINORMAL3FEXTPROC)load("glBinormal3fEXT");
	glad_glBinormal3fvEXT = (PFNGLBINORMAL3FVEXTPROC)load("glBinormal3fvEXT");
	glad_glBinormal3iEXT = (PFNGLBINORMAL3IEXTPROC)load("glBinormal3iEXT");
	glad_glBinormal3ivEXT = (PFNGLBINORMAL3IVEXTPROC)load("glBinormal3ivEXT");
	glad_glBinormal3sEXT = (PFNGLBINORMAL3SEXTPROC)load("glBinormal3sEXT");
	glad_glBinormal3svEXT = (PFNGLBINORMAL3SVEXTPROC)load("glBinormal3svEXT");
	glad_glTangentPointerEXT = (PFNGLTANGENTPOINTEREXTPROC)load("glTangentPointerEXT");
	glad_glBinormalPointerEXT = (PFNGLBINORMALPOINTEREXTPROC)load("glBinormalPointerEXT");
}