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
typedef  scalar_t__ PFNGLMAPVERTEXATTRIB2FAPPLEPROC ;
typedef  scalar_t__ PFNGLMAPVERTEXATTRIB2DAPPLEPROC ;
typedef  scalar_t__ PFNGLMAPVERTEXATTRIB1FAPPLEPROC ;
typedef  scalar_t__ PFNGLMAPVERTEXATTRIB1DAPPLEPROC ;
typedef  scalar_t__ PFNGLISVERTEXATTRIBENABLEDAPPLEPROC ;
typedef  scalar_t__ PFNGLENABLEVERTEXATTRIBAPPLEPROC ;
typedef  scalar_t__ PFNGLDISABLEVERTEXATTRIBAPPLEPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_APPLE_vertex_program_evaluators ; 
 scalar_t__ glad_glDisableVertexAttribAPPLE ; 
 scalar_t__ glad_glEnableVertexAttribAPPLE ; 
 scalar_t__ glad_glIsVertexAttribEnabledAPPLE ; 
 scalar_t__ glad_glMapVertexAttrib1dAPPLE ; 
 scalar_t__ glad_glMapVertexAttrib1fAPPLE ; 
 scalar_t__ glad_glMapVertexAttrib2dAPPLE ; 
 scalar_t__ glad_glMapVertexAttrib2fAPPLE ; 

__attribute__((used)) static void load_GL_APPLE_vertex_program_evaluators(GLADloadproc load) {
	if(!GLAD_GL_APPLE_vertex_program_evaluators) return;
	glad_glEnableVertexAttribAPPLE = (PFNGLENABLEVERTEXATTRIBAPPLEPROC)load("glEnableVertexAttribAPPLE");
	glad_glDisableVertexAttribAPPLE = (PFNGLDISABLEVERTEXATTRIBAPPLEPROC)load("glDisableVertexAttribAPPLE");
	glad_glIsVertexAttribEnabledAPPLE = (PFNGLISVERTEXATTRIBENABLEDAPPLEPROC)load("glIsVertexAttribEnabledAPPLE");
	glad_glMapVertexAttrib1dAPPLE = (PFNGLMAPVERTEXATTRIB1DAPPLEPROC)load("glMapVertexAttrib1dAPPLE");
	glad_glMapVertexAttrib1fAPPLE = (PFNGLMAPVERTEXATTRIB1FAPPLEPROC)load("glMapVertexAttrib1fAPPLE");
	glad_glMapVertexAttrib2dAPPLE = (PFNGLMAPVERTEXATTRIB2DAPPLEPROC)load("glMapVertexAttrib2dAPPLE");
	glad_glMapVertexAttrib2fAPPLE = (PFNGLMAPVERTEXATTRIB2FAPPLEPROC)load("glMapVertexAttrib2fAPPLE");
}