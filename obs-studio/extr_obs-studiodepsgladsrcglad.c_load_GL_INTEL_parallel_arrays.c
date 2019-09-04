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
typedef  scalar_t__ PFNGLVERTEXPOINTERVINTELPROC ;
typedef  scalar_t__ PFNGLTEXCOORDPOINTERVINTELPROC ;
typedef  scalar_t__ PFNGLNORMALPOINTERVINTELPROC ;
typedef  scalar_t__ PFNGLCOLORPOINTERVINTELPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_INTEL_parallel_arrays ; 
 scalar_t__ glad_glColorPointervINTEL ; 
 scalar_t__ glad_glNormalPointervINTEL ; 
 scalar_t__ glad_glTexCoordPointervINTEL ; 
 scalar_t__ glad_glVertexPointervINTEL ; 

__attribute__((used)) static void load_GL_INTEL_parallel_arrays(GLADloadproc load) {
	if(!GLAD_GL_INTEL_parallel_arrays) return;
	glad_glVertexPointervINTEL = (PFNGLVERTEXPOINTERVINTELPROC)load("glVertexPointervINTEL");
	glad_glNormalPointervINTEL = (PFNGLNORMALPOINTERVINTELPROC)load("glNormalPointervINTEL");
	glad_glColorPointervINTEL = (PFNGLCOLORPOINTERVINTELPROC)load("glColorPointervINTEL");
	glad_glTexCoordPointervINTEL = (PFNGLTEXCOORDPOINTERVINTELPROC)load("glTexCoordPointervINTEL");
}