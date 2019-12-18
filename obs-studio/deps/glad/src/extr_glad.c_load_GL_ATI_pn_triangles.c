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
typedef  scalar_t__ PFNGLPNTRIANGLESIATIPROC ;
typedef  scalar_t__ PFNGLPNTRIANGLESFATIPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ATI_pn_triangles ; 
 scalar_t__ glad_glPNTrianglesfATI ; 
 scalar_t__ glad_glPNTrianglesiATI ; 

__attribute__((used)) static void load_GL_ATI_pn_triangles(GLADloadproc load) {
	if(!GLAD_GL_ATI_pn_triangles) return;
	glad_glPNTrianglesiATI = (PFNGLPNTRIANGLESIATIPROC)load("glPNTrianglesiATI");
	glad_glPNTrianglesfATI = (PFNGLPNTRIANGLESFATIPROC)load("glPNTrianglesfATI");
}