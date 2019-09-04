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
typedef  scalar_t__ PFNGLGETFRAGDATAINDEXPROC ;
typedef  scalar_t__ PFNGLBINDFRAGDATALOCATIONINDEXEDPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_ARB_blend_func_extended ; 
 scalar_t__ glad_glBindFragDataLocationIndexed ; 
 scalar_t__ glad_glGetFragDataIndex ; 

__attribute__((used)) static void load_GL_ARB_blend_func_extended(GLADloadproc load) {
	if(!GLAD_GL_ARB_blend_func_extended) return;
	glad_glBindFragDataLocationIndexed = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)load("glBindFragDataLocationIndexed");
	glad_glGetFragDataIndex = (PFNGLGETFRAGDATAINDEXPROC)load("glGetFragDataIndex");
}