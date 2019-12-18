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
typedef  scalar_t__ PFNGLVERTEXATTRIBLPOINTEREXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL4DVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL4DEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL3DVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL3DEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL2DVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL2DEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL1DVEXTPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL1DEXTPROC ;
typedef  scalar_t__ PFNGLGETVERTEXATTRIBLDVEXTPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_EXT_vertex_attrib_64bit ; 
 scalar_t__ glad_glGetVertexAttribLdvEXT ; 
 scalar_t__ glad_glVertexAttribL1dEXT ; 
 scalar_t__ glad_glVertexAttribL1dvEXT ; 
 scalar_t__ glad_glVertexAttribL2dEXT ; 
 scalar_t__ glad_glVertexAttribL2dvEXT ; 
 scalar_t__ glad_glVertexAttribL3dEXT ; 
 scalar_t__ glad_glVertexAttribL3dvEXT ; 
 scalar_t__ glad_glVertexAttribL4dEXT ; 
 scalar_t__ glad_glVertexAttribL4dvEXT ; 
 scalar_t__ glad_glVertexAttribLPointerEXT ; 

__attribute__((used)) static void load_GL_EXT_vertex_attrib_64bit(GLADloadproc load) {
	if(!GLAD_GL_EXT_vertex_attrib_64bit) return;
	glad_glVertexAttribL1dEXT = (PFNGLVERTEXATTRIBL1DEXTPROC)load("glVertexAttribL1dEXT");
	glad_glVertexAttribL2dEXT = (PFNGLVERTEXATTRIBL2DEXTPROC)load("glVertexAttribL2dEXT");
	glad_glVertexAttribL3dEXT = (PFNGLVERTEXATTRIBL3DEXTPROC)load("glVertexAttribL3dEXT");
	glad_glVertexAttribL4dEXT = (PFNGLVERTEXATTRIBL4DEXTPROC)load("glVertexAttribL4dEXT");
	glad_glVertexAttribL1dvEXT = (PFNGLVERTEXATTRIBL1DVEXTPROC)load("glVertexAttribL1dvEXT");
	glad_glVertexAttribL2dvEXT = (PFNGLVERTEXATTRIBL2DVEXTPROC)load("glVertexAttribL2dvEXT");
	glad_glVertexAttribL3dvEXT = (PFNGLVERTEXATTRIBL3DVEXTPROC)load("glVertexAttribL3dvEXT");
	glad_glVertexAttribL4dvEXT = (PFNGLVERTEXATTRIBL4DVEXTPROC)load("glVertexAttribL4dvEXT");
	glad_glVertexAttribLPointerEXT = (PFNGLVERTEXATTRIBLPOINTEREXTPROC)load("glVertexAttribLPointerEXT");
	glad_glGetVertexAttribLdvEXT = (PFNGLGETVERTEXATTRIBLDVEXTPROC)load("glGetVertexAttribLdvEXT");
}