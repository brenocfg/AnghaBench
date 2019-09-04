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
typedef  scalar_t__ PFNGLVERTEXFORMATNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBIFORMATNVPROC ;
typedef  scalar_t__ PFNGLVERTEXATTRIBFORMATNVPROC ;
typedef  scalar_t__ PFNGLTEXCOORDFORMATNVPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLORFORMATNVPROC ;
typedef  scalar_t__ PFNGLNORMALFORMATNVPROC ;
typedef  scalar_t__ PFNGLINDEXFORMATNVPROC ;
typedef  scalar_t__ PFNGLGETINTEGERUI64I_VNVPROC ;
typedef  scalar_t__ PFNGLFOGCOORDFORMATNVPROC ;
typedef  scalar_t__ PFNGLEDGEFLAGFORMATNVPROC ;
typedef  scalar_t__ PFNGLCOLORFORMATNVPROC ;
typedef  scalar_t__ PFNGLBUFFERADDRESSRANGENVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_vertex_buffer_unified_memory ; 
 scalar_t__ glad_glBufferAddressRangeNV ; 
 scalar_t__ glad_glColorFormatNV ; 
 scalar_t__ glad_glEdgeFlagFormatNV ; 
 scalar_t__ glad_glFogCoordFormatNV ; 
 scalar_t__ glad_glGetIntegerui64i_vNV ; 
 scalar_t__ glad_glIndexFormatNV ; 
 scalar_t__ glad_glNormalFormatNV ; 
 scalar_t__ glad_glSecondaryColorFormatNV ; 
 scalar_t__ glad_glTexCoordFormatNV ; 
 scalar_t__ glad_glVertexAttribFormatNV ; 
 scalar_t__ glad_glVertexAttribIFormatNV ; 
 scalar_t__ glad_glVertexFormatNV ; 

__attribute__((used)) static void load_GL_NV_vertex_buffer_unified_memory(GLADloadproc load) {
	if(!GLAD_GL_NV_vertex_buffer_unified_memory) return;
	glad_glBufferAddressRangeNV = (PFNGLBUFFERADDRESSRANGENVPROC)load("glBufferAddressRangeNV");
	glad_glVertexFormatNV = (PFNGLVERTEXFORMATNVPROC)load("glVertexFormatNV");
	glad_glNormalFormatNV = (PFNGLNORMALFORMATNVPROC)load("glNormalFormatNV");
	glad_glColorFormatNV = (PFNGLCOLORFORMATNVPROC)load("glColorFormatNV");
	glad_glIndexFormatNV = (PFNGLINDEXFORMATNVPROC)load("glIndexFormatNV");
	glad_glTexCoordFormatNV = (PFNGLTEXCOORDFORMATNVPROC)load("glTexCoordFormatNV");
	glad_glEdgeFlagFormatNV = (PFNGLEDGEFLAGFORMATNVPROC)load("glEdgeFlagFormatNV");
	glad_glSecondaryColorFormatNV = (PFNGLSECONDARYCOLORFORMATNVPROC)load("glSecondaryColorFormatNV");
	glad_glFogCoordFormatNV = (PFNGLFOGCOORDFORMATNVPROC)load("glFogCoordFormatNV");
	glad_glVertexAttribFormatNV = (PFNGLVERTEXATTRIBFORMATNVPROC)load("glVertexAttribFormatNV");
	glad_glVertexAttribIFormatNV = (PFNGLVERTEXATTRIBIFORMATNVPROC)load("glVertexAttribIFormatNV");
	glad_glGetIntegerui64i_vNV = (PFNGLGETINTEGERUI64I_VNVPROC)load("glGetIntegerui64i_vNV");
}