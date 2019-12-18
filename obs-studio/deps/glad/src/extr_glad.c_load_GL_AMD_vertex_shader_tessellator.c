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
typedef  scalar_t__ PFNGLTESSELLATIONMODEAMDPROC ;
typedef  scalar_t__ PFNGLTESSELLATIONFACTORAMDPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_AMD_vertex_shader_tessellator ; 
 scalar_t__ glad_glTessellationFactorAMD ; 
 scalar_t__ glad_glTessellationModeAMD ; 

__attribute__((used)) static void load_GL_AMD_vertex_shader_tessellator(GLADloadproc load) {
	if(!GLAD_GL_AMD_vertex_shader_tessellator) return;
	glad_glTessellationFactorAMD = (PFNGLTESSELLATIONFACTORAMDPROC)load("glTessellationFactorAMD");
	glad_glTessellationModeAMD = (PFNGLTESSELLATIONMODEAMDPROC)load("glTessellationModeAMD");
}