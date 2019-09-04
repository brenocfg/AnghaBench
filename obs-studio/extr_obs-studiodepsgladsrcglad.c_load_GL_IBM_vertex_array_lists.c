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
typedef  scalar_t__ PFNGLVERTEXPOINTERLISTIBMPROC ;
typedef  scalar_t__ PFNGLTEXCOORDPOINTERLISTIBMPROC ;
typedef  scalar_t__ PFNGLSECONDARYCOLORPOINTERLISTIBMPROC ;
typedef  scalar_t__ PFNGLNORMALPOINTERLISTIBMPROC ;
typedef  scalar_t__ PFNGLINDEXPOINTERLISTIBMPROC ;
typedef  scalar_t__ PFNGLFOGCOORDPOINTERLISTIBMPROC ;
typedef  scalar_t__ PFNGLEDGEFLAGPOINTERLISTIBMPROC ;
typedef  scalar_t__ PFNGLCOLORPOINTERLISTIBMPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_IBM_vertex_array_lists ; 
 scalar_t__ glad_glColorPointerListIBM ; 
 scalar_t__ glad_glEdgeFlagPointerListIBM ; 
 scalar_t__ glad_glFogCoordPointerListIBM ; 
 scalar_t__ glad_glIndexPointerListIBM ; 
 scalar_t__ glad_glNormalPointerListIBM ; 
 scalar_t__ glad_glSecondaryColorPointerListIBM ; 
 scalar_t__ glad_glTexCoordPointerListIBM ; 
 scalar_t__ glad_glVertexPointerListIBM ; 

__attribute__((used)) static void load_GL_IBM_vertex_array_lists(GLADloadproc load) {
	if(!GLAD_GL_IBM_vertex_array_lists) return;
	glad_glColorPointerListIBM = (PFNGLCOLORPOINTERLISTIBMPROC)load("glColorPointerListIBM");
	glad_glSecondaryColorPointerListIBM = (PFNGLSECONDARYCOLORPOINTERLISTIBMPROC)load("glSecondaryColorPointerListIBM");
	glad_glEdgeFlagPointerListIBM = (PFNGLEDGEFLAGPOINTERLISTIBMPROC)load("glEdgeFlagPointerListIBM");
	glad_glFogCoordPointerListIBM = (PFNGLFOGCOORDPOINTERLISTIBMPROC)load("glFogCoordPointerListIBM");
	glad_glIndexPointerListIBM = (PFNGLINDEXPOINTERLISTIBMPROC)load("glIndexPointerListIBM");
	glad_glNormalPointerListIBM = (PFNGLNORMALPOINTERLISTIBMPROC)load("glNormalPointerListIBM");
	glad_glTexCoordPointerListIBM = (PFNGLTEXCOORDPOINTERLISTIBMPROC)load("glTexCoordPointerListIBM");
	glad_glVertexPointerListIBM = (PFNGLVERTEXPOINTERLISTIBMPROC)load("glVertexPointerListIBM");
}