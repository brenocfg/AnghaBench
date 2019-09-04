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
typedef  scalar_t__ PFNGLSHADERBINARYPROC ;
typedef  scalar_t__ PFNGLRELEASESHADERCOMPILERPROC ;
typedef  scalar_t__ PFNGLGETSHADERPRECISIONFORMATPROC ;
typedef  scalar_t__ PFNGLDEPTHRANGEFPROC ;
typedef  scalar_t__ PFNGLCLEARDEPTHFPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_ES2_compatibility ; 
 scalar_t__ glad_glClearDepthf ; 
 scalar_t__ glad_glDepthRangef ; 
 scalar_t__ glad_glGetShaderPrecisionFormat ; 
 scalar_t__ glad_glReleaseShaderCompiler ; 
 scalar_t__ glad_glShaderBinary ; 

__attribute__((used)) static void load_GL_ARB_ES2_compatibility(GLADloadproc load) {
	if(!GLAD_GL_ARB_ES2_compatibility) return;
	glad_glReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC)load("glReleaseShaderCompiler");
	glad_glShaderBinary = (PFNGLSHADERBINARYPROC)load("glShaderBinary");
	glad_glGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC)load("glGetShaderPrecisionFormat");
	glad_glDepthRangef = (PFNGLDEPTHRANGEFPROC)load("glDepthRangef");
	glad_glClearDepthf = (PFNGLCLEARDEPTHFPROC)load("glClearDepthf");
}