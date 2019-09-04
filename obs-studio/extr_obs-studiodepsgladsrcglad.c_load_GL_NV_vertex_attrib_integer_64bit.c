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
typedef  scalar_t__ PFNGLVERTEXATTRIBLFORMATNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL4UI64VNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL4UI64NVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL4I64VNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL4I64NVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL3UI64VNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL3UI64NVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL3I64VNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL3I64NVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL2UI64VNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL2UI64NVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL2I64VNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL2I64NVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL1UI64VNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL1UI64NVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL1I64VNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBL1I64NVPROC ;
typedef  scalar_t__ PFNGLGETVERTEXATTRIBLUI64VNVPROC ;
typedef  scalar_t__ PFNGLGETVERTEXATTRIBLI64VNVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_vertex_attrib_integer_64bit ; 
 scalar_t__ glad_glGetVertexAttribLi64vNV ; 
 scalar_t__ glad_glGetVertexAttribLui64vNV ; 
 scalar_t__ glad_glVertexAttribL1i64NV ; 
 scalar_t__ glad_glVertexAttribL1i64vNV ; 
 scalar_t__ glad_glVertexAttribL1ui64NV ; 
 scalar_t__ glad_glVertexAttribL1ui64vNV ; 
 scalar_t__ glad_glVertexAttribL2i64NV ; 
 scalar_t__ glad_glVertexAttribL2i64vNV ; 
 scalar_t__ glad_glVertexAttribL2ui64NV ; 
 scalar_t__ glad_glVertexAttribL2ui64vNV ; 
 scalar_t__ glad_glVertexAttribL3i64NV ; 
 scalar_t__ glad_glVertexAttribL3i64vNV ; 
 scalar_t__ glad_glVertexAttribL3ui64NV ; 
 scalar_t__ glad_glVertexAttribL3ui64vNV ; 
 scalar_t__ glad_glVertexAttribL4i64NV ; 
 scalar_t__ glad_glVertexAttribL4i64vNV ; 
 scalar_t__ glad_glVertexAttribL4ui64NV ; 
 scalar_t__ glad_glVertexAttribL4ui64vNV ; 
 scalar_t__ glad_glVertexAttribLFormatNV ; 

__attribute__((used)) static void load_GL_NV_vertex_attrib_integer_64bit(GLADloadproc load) {
	if(!GLAD_GL_NV_vertex_attrib_integer_64bit) return;
	glad_glVertexAttribL1i64NV = (PFNGLVERTEXATTRIBL1I64NVPROC)load("glVertexAttribL1i64NV");
	glad_glVertexAttribL2i64NV = (PFNGLVERTEXATTRIBL2I64NVPROC)load("glVertexAttribL2i64NV");
	glad_glVertexAttribL3i64NV = (PFNGLVERTEXATTRIBL3I64NVPROC)load("glVertexAttribL3i64NV");
	glad_glVertexAttribL4i64NV = (PFNGLVERTEXATTRIBL4I64NVPROC)load("glVertexAttribL4i64NV");
	glad_glVertexAttribL1i64vNV = (PFNGLVERTEXATTRIBL1I64VNVPROC)load("glVertexAttribL1i64vNV");
	glad_glVertexAttribL2i64vNV = (PFNGLVERTEXATTRIBL2I64VNVPROC)load("glVertexAttribL2i64vNV");
	glad_glVertexAttribL3i64vNV = (PFNGLVERTEXATTRIBL3I64VNVPROC)load("glVertexAttribL3i64vNV");
	glad_glVertexAttribL4i64vNV = (PFNGLVERTEXATTRIBL4I64VNVPROC)load("glVertexAttribL4i64vNV");
	glad_glVertexAttribL1ui64NV = (PFNGLVERTEXATTRIBL1UI64NVPROC)load("glVertexAttribL1ui64NV");
	glad_glVertexAttribL2ui64NV = (PFNGLVERTEXATTRIBL2UI64NVPROC)load("glVertexAttribL2ui64NV");
	glad_glVertexAttribL3ui64NV = (PFNGLVERTEXATTRIBL3UI64NVPROC)load("glVertexAttribL3ui64NV");
	glad_glVertexAttribL4ui64NV = (PFNGLVERTEXATTRIBL4UI64NVPROC)load("glVertexAttribL4ui64NV");
	glad_glVertexAttribL1ui64vNV = (PFNGLVERTEXATTRIBL1UI64VNVPROC)load("glVertexAttribL1ui64vNV");
	glad_glVertexAttribL2ui64vNV = (PFNGLVERTEXATTRIBL2UI64VNVPROC)load("glVertexAttribL2ui64vNV");
	glad_glVertexAttribL3ui64vNV = (PFNGLVERTEXATTRIBL3UI64VNVPROC)load("glVertexAttribL3ui64vNV");
	glad_glVertexAttribL4ui64vNV = (PFNGLVERTEXATTRIBL4UI64VNVPROC)load("glVertexAttribL4ui64vNV");
	glad_glGetVertexAttribLi64vNV = (PFNGLGETVERTEXATTRIBLI64VNVPROC)load("glGetVertexAttribLi64vNV");
	glad_glGetVertexAttribLui64vNV = (PFNGLGETVERTEXATTRIBLUI64VNVPROC)load("glGetVertexAttribLui64vNV");
	glad_glVertexAttribLFormatNV = (PFNGLVERTEXATTRIBLFORMATNVPROC)load("glVertexAttribLFormatNV");
}