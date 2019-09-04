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
typedef  scalar_t__ PFNGLPRIMITIVERESTARTNVPROC ;
typedef  scalar_t__ PFNGLPRIMITIVERESTARTINDEXNVPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  GLAD_GL_NV_primitive_restart ; 
 scalar_t__ glad_glPrimitiveRestartIndexNV ; 
 scalar_t__ glad_glPrimitiveRestartNV ; 

__attribute__((used)) static void load_GL_NV_primitive_restart(GLADloadproc load) {
	if(!GLAD_GL_NV_primitive_restart) return;
	glad_glPrimitiveRestartNV = (PFNGLPRIMITIVERESTARTNVPROC)load("glPrimitiveRestartNV");
	glad_glPrimitiveRestartIndexNV = (PFNGLPRIMITIVERESTARTINDEXNVPROC)load("glPrimitiveRestartIndexNV");
}