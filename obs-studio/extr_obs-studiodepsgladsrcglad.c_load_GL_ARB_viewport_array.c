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
typedef  scalar_t__ PFNGLVIEWPORTINDEXEDFVPROC ;
typedef  scalar_t__ PFNGLVIEWPORTINDEXEDFPROC ;
typedef  scalar_t__ PFNGLVIEWPORTARRAYVPROC ;
typedef  scalar_t__ PFNGLSCISSORINDEXEDVPROC ;
typedef  scalar_t__ PFNGLSCISSORINDEXEDPROC ;
typedef  scalar_t__ PFNGLSCISSORARRAYVPROC ;
typedef  scalar_t__ PFNGLGETFLOATI_VPROC ;
typedef  scalar_t__ PFNGLGETDOUBLEI_VPROC ;
typedef  scalar_t__ PFNGLDEPTHRANGEINDEXEDPROC ;
typedef  scalar_t__ PFNGLDEPTHRANGEARRAYVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_viewport_array ; 
 scalar_t__ glad_glDepthRangeArrayv ; 
 scalar_t__ glad_glDepthRangeIndexed ; 
 scalar_t__ glad_glGetDoublei_v ; 
 scalar_t__ glad_glGetFloati_v ; 
 scalar_t__ glad_glScissorArrayv ; 
 scalar_t__ glad_glScissorIndexed ; 
 scalar_t__ glad_glScissorIndexedv ; 
 scalar_t__ glad_glViewportArrayv ; 
 scalar_t__ glad_glViewportIndexedf ; 
 scalar_t__ glad_glViewportIndexedfv ; 

__attribute__((used)) static void load_GL_ARB_viewport_array(GLADloadproc load) {
	if(!GLAD_GL_ARB_viewport_array) return;
	glad_glViewportArrayv = (PFNGLVIEWPORTARRAYVPROC)load("glViewportArrayv");
	glad_glViewportIndexedf = (PFNGLVIEWPORTINDEXEDFPROC)load("glViewportIndexedf");
	glad_glViewportIndexedfv = (PFNGLVIEWPORTINDEXEDFVPROC)load("glViewportIndexedfv");
	glad_glScissorArrayv = (PFNGLSCISSORARRAYVPROC)load("glScissorArrayv");
	glad_glScissorIndexed = (PFNGLSCISSORINDEXEDPROC)load("glScissorIndexed");
	glad_glScissorIndexedv = (PFNGLSCISSORINDEXEDVPROC)load("glScissorIndexedv");
	glad_glDepthRangeArrayv = (PFNGLDEPTHRANGEARRAYVPROC)load("glDepthRangeArrayv");
	glad_glDepthRangeIndexed = (PFNGLDEPTHRANGEINDEXEDPROC)load("glDepthRangeIndexed");
	glad_glGetFloati_v = (PFNGLGETFLOATI_VPROC)load("glGetFloati_v");
	glad_glGetDoublei_v = (PFNGLGETDOUBLEI_VPROC)load("glGetDoublei_v");
}