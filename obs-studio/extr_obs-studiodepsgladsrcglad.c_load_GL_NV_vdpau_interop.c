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
typedef  scalar_t__ PFNGLVDPAUUNREGISTERSURFACENVPROC ;
typedef  scalar_t__ PFNGLVDPAUUNMAPSURFACESNVPROC ;
typedef  scalar_t__ PFNGLVDPAUSURFACEACCESSNVPROC ;
typedef  scalar_t__ PFNGLVDPAUREGISTERVIDEOSURFACENVPROC ;
typedef  scalar_t__ PFNGLVDPAUREGISTEROUTPUTSURFACENVPROC ;
typedef  scalar_t__ PFNGLVDPAUMAPSURFACESNVPROC ;
typedef  scalar_t__ PFNGLVDPAUISSURFACENVPROC ;
typedef  scalar_t__ PFNGLVDPAUINITNVPROC ;
typedef  scalar_t__ PFNGLVDPAUGETSURFACEIVNVPROC ;
typedef  scalar_t__ PFNGLVDPAUFININVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_vdpau_interop ; 
 scalar_t__ glad_glVDPAUFiniNV ; 
 scalar_t__ glad_glVDPAUGetSurfaceivNV ; 
 scalar_t__ glad_glVDPAUInitNV ; 
 scalar_t__ glad_glVDPAUIsSurfaceNV ; 
 scalar_t__ glad_glVDPAUMapSurfacesNV ; 
 scalar_t__ glad_glVDPAURegisterOutputSurfaceNV ; 
 scalar_t__ glad_glVDPAURegisterVideoSurfaceNV ; 
 scalar_t__ glad_glVDPAUSurfaceAccessNV ; 
 scalar_t__ glad_glVDPAUUnmapSurfacesNV ; 
 scalar_t__ glad_glVDPAUUnregisterSurfaceNV ; 

__attribute__((used)) static void load_GL_NV_vdpau_interop(GLADloadproc load) {
	if(!GLAD_GL_NV_vdpau_interop) return;
	glad_glVDPAUInitNV = (PFNGLVDPAUINITNVPROC)load("glVDPAUInitNV");
	glad_glVDPAUFiniNV = (PFNGLVDPAUFININVPROC)load("glVDPAUFiniNV");
	glad_glVDPAURegisterVideoSurfaceNV = (PFNGLVDPAUREGISTERVIDEOSURFACENVPROC)load("glVDPAURegisterVideoSurfaceNV");
	glad_glVDPAURegisterOutputSurfaceNV = (PFNGLVDPAUREGISTEROUTPUTSURFACENVPROC)load("glVDPAURegisterOutputSurfaceNV");
	glad_glVDPAUIsSurfaceNV = (PFNGLVDPAUISSURFACENVPROC)load("glVDPAUIsSurfaceNV");
	glad_glVDPAUUnregisterSurfaceNV = (PFNGLVDPAUUNREGISTERSURFACENVPROC)load("glVDPAUUnregisterSurfaceNV");
	glad_glVDPAUGetSurfaceivNV = (PFNGLVDPAUGETSURFACEIVNVPROC)load("glVDPAUGetSurfaceivNV");
	glad_glVDPAUSurfaceAccessNV = (PFNGLVDPAUSURFACEACCESSNVPROC)load("glVDPAUSurfaceAccessNV");
	glad_glVDPAUMapSurfacesNV = (PFNGLVDPAUMAPSURFACESNVPROC)load("glVDPAUMapSurfacesNV");
	glad_glVDPAUUnmapSurfacesNV = (PFNGLVDPAUUNMAPSURFACESNVPROC)load("glVDPAUUnmapSurfacesNV");
}