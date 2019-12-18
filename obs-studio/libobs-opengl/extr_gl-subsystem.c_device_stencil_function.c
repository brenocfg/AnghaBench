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
typedef  int /*<<< orphan*/  gs_device_t ;
typedef  enum gs_stencil_side { ____Placeholder_gs_stencil_side } gs_stencil_side ;
typedef  enum gs_depth_test { ____Placeholder_gs_depth_test } gs_depth_test ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  convert_gs_depth_test (int) ; 
 int /*<<< orphan*/  convert_gs_stencil_side (int) ; 
 int /*<<< orphan*/  glStencilFuncSeparate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

void device_stencil_function(gs_device_t *device, enum gs_stencil_side side,
			     enum gs_depth_test test)
{
	GLenum gl_side = convert_gs_stencil_side(side);
	GLenum gl_test = convert_gs_depth_test(test);

	glStencilFuncSeparate(gl_side, gl_test, 0, 0xFFFFFFFF);
	if (!gl_success("glStencilFuncSeparate"))
		blog(LOG_ERROR, "device_stencil_function (GL) failed");

	UNUSED_PARAMETER(device);
}