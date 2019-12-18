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
typedef  scalar_t__ PFNGLVERTEXATTRIBLPOINTERPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL4DVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL4DPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL3DVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL3DPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL2DVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL2DPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL1DVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL1DPROC ;
typedef  scalar_t__ PFNGLGETVERTEXATTRIBLDVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_vertex_attrib_64bit ; 
 scalar_t__ glad_glGetVertexAttribLdv ; 
 scalar_t__ glad_glVertexAttribL1d ; 
 scalar_t__ glad_glVertexAttribL1dv ; 
 scalar_t__ glad_glVertexAttribL2d ; 
 scalar_t__ glad_glVertexAttribL2dv ; 
 scalar_t__ glad_glVertexAttribL3d ; 
 scalar_t__ glad_glVertexAttribL3dv ; 
 scalar_t__ glad_glVertexAttribL4d ; 
 scalar_t__ glad_glVertexAttribL4dv ; 
 scalar_t__ glad_glVertexAttribLPointer ; 

__attribute__((used)) static void load_GL_ARB_vertex_attrib_64bit(GLADloadproc load) {
	if(!GLAD_GL_ARB_vertex_attrib_64bit) return;
	glad_glVertexAttribL1d = (PFNGLVERTEXATTRIBL1DPROC)load("glVertexAttribL1d");
	glad_glVertexAttribL2d = (PFNGLVERTEXATTRIBL2DPROC)load("glVertexAttribL2d");
	glad_glVertexAttribL3d = (PFNGLVERTEXATTRIBL3DPROC)load("glVertexAttribL3d");
	glad_glVertexAttribL4d = (PFNGLVERTEXATTRIBL4DPROC)load("glVertexAttribL4d");
	glad_glVertexAttribL1dv = (PFNGLVERTEXATTRIBL1DVPROC)load("glVertexAttribL1dv");
	glad_glVertexAttribL2dv = (PFNGLVERTEXATTRIBL2DVPROC)load("glVertexAttribL2dv");
	glad_glVertexAttribL3dv = (PFNGLVERTEXATTRIBL3DVPROC)load("glVertexAttribL3dv");
	glad_glVertexAttribL4dv = (PFNGLVERTEXATTRIBL4DVPROC)load("glVertexAttribL4dv");
	glad_glVertexAttribLPointer = (PFNGLVERTEXATTRIBLPOINTERPROC)load("glVertexAttribLPointer");
	glad_glGetVertexAttribLdv = (PFNGLGETVERTEXATTRIBLDVPROC)load("glGetVertexAttribLdv");
}