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
typedef  scalar_t__ PFNGLSECONDARYCOLORPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3USVEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3USEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3UIVEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3UIEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3UBVEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3UBEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3SVEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3SEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3IVEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3IEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3FVEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3FEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3DVEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3DEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3BVEXTPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLOR3BEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_secondary_color ; 
 scalar_t__ glad_glSecondaryColor3bEXT ; 
 scalar_t__ glad_glSecondaryColor3bvEXT ; 
 scalar_t__ glad_glSecondaryColor3dEXT ; 
 scalar_t__ glad_glSecondaryColor3dvEXT ; 
 scalar_t__ glad_glSecondaryColor3fEXT ; 
 scalar_t__ glad_glSecondaryColor3fvEXT ; 
 scalar_t__ glad_glSecondaryColor3iEXT ; 
 scalar_t__ glad_glSecondaryColor3ivEXT ; 
 scalar_t__ glad_glSecondaryColor3sEXT ; 
 scalar_t__ glad_glSecondaryColor3svEXT ; 
 scalar_t__ glad_glSecondaryColor3ubEXT ; 
 scalar_t__ glad_glSecondaryColor3ubvEXT ; 
 scalar_t__ glad_glSecondaryColor3uiEXT ; 
 scalar_t__ glad_glSecondaryColor3uivEXT ; 
 scalar_t__ glad_glSecondaryColor3usEXT ; 
 scalar_t__ glad_glSecondaryColor3usvEXT ; 
 scalar_t__ glad_glSecondaryColorPointerEXT ; 

__attribute__((used)) static void load_GL_EXT_secondary_color(GLADloadproc load) {
	if(!GLAD_GL_EXT_secondary_color) return;
	glad_glSecondaryColor3bEXT = (PFNGLSECONDARYCOLOR3BEXTPROC)load("glSecondaryColor3bEXT");
	glad_glSecondaryColor3bvEXT = (PFNGLSECONDARYCOLOR3BVEXTPROC)load("glSecondaryColor3bvEXT");
	glad_glSecondaryColor3dEXT = (PFNGLSECONDARYCOLOR3DEXTPROC)load("glSecondaryColor3dEXT");
	glad_glSecondaryColor3dvEXT = (PFNGLSECONDARYCOLOR3DVEXTPROC)load("glSecondaryColor3dvEXT");
	glad_glSecondaryColor3fEXT = (PFNGLSECONDARYCOLOR3FEXTPROC)load("glSecondaryColor3fEXT");
	glad_glSecondaryColor3fvEXT = (PFNGLSECONDARYCOLOR3FVEXTPROC)load("glSecondaryColor3fvEXT");
	glad_glSecondaryColor3iEXT = (PFNGLSECONDARYCOLOR3IEXTPROC)load("glSecondaryColor3iEXT");
	glad_glSecondaryColor3ivEXT = (PFNGLSECONDARYCOLOR3IVEXTPROC)load("glSecondaryColor3ivEXT");
	glad_glSecondaryColor3sEXT = (PFNGLSECONDARYCOLOR3SEXTPROC)load("glSecondaryColor3sEXT");
	glad_glSecondaryColor3svEXT = (PFNGLSECONDARYCOLOR3SVEXTPROC)load("glSecondaryColor3svEXT");
	glad_glSecondaryColor3ubEXT = (PFNGLSECONDARYCOLOR3UBEXTPROC)load("glSecondaryColor3ubEXT");
	glad_glSecondaryColor3ubvEXT = (PFNGLSECONDARYCOLOR3UBVEXTPROC)load("glSecondaryColor3ubvEXT");
	glad_glSecondaryColor3uiEXT = (PFNGLSECONDARYCOLOR3UIEXTPROC)load("glSecondaryColor3uiEXT");
	glad_glSecondaryColor3uivEXT = (PFNGLSECONDARYCOLOR3UIVEXTPROC)load("glSecondaryColor3uivEXT");
	glad_glSecondaryColor3usEXT = (PFNGLSECONDARYCOLOR3USEXTPROC)load("glSecondaryColor3usEXT");
	glad_glSecondaryColor3usvEXT = (PFNGLSECONDARYCOLOR3USVEXTPROC)load("glSecondaryColor3usvEXT");
	glad_glSecondaryColorPointerEXT = (PFNGLSECONDARYCOLORPOINTEREXTPROC)load("glSecondaryColorPointerEXT");
}