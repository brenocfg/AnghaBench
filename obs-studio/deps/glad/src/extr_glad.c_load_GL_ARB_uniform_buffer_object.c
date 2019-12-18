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
typedef  scalar_t__ PFNGLUNIFORMBLOCKBINDINGPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMINDICESPROC ;
typedef  scalar_t__ PFNGLGETUNIFORMBLOCKINDEXPROC ;
typedef  scalar_t__ PFNGLGETACTIVEUNIFORMSIVPROC ;
typedef  scalar_t__ PFNGLGETACTIVEUNIFORMNAMEPROC ;
typedef  scalar_t__ PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC ;
typedef  scalar_t__ PFNGLGETACTIVEUNIFORMBLOCKIVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_uniform_buffer_object ; 
 scalar_t__ glad_glGetActiveUniformBlockName ; 
 scalar_t__ glad_glGetActiveUniformBlockiv ; 
 scalar_t__ glad_glGetActiveUniformName ; 
 scalar_t__ glad_glGetActiveUniformsiv ; 
 scalar_t__ glad_glGetUniformBlockIndex ; 
 scalar_t__ glad_glGetUniformIndices ; 
 scalar_t__ glad_glUniformBlockBinding ; 

__attribute__((used)) static void load_GL_ARB_uniform_buffer_object(GLADloadproc load) {
	if(!GLAD_GL_ARB_uniform_buffer_object) return;
	glad_glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC)load("glGetUniformIndices");
	glad_glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)load("glGetActiveUniformsiv");
	glad_glGetActiveUniformName = (PFNGLGETACTIVEUNIFORMNAMEPROC)load("glGetActiveUniformName");
	glad_glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC)load("glGetUniformBlockIndex");
	glad_glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)load("glGetActiveUniformBlockiv");
	glad_glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)load("glGetActiveUniformBlockName");
	glad_glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC)load("glUniformBlockBinding");
}