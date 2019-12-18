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
typedef  enum gs_stencil_op_type { ____Placeholder_gs_stencil_op_type } gs_stencil_op_type ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  convert_gs_stencil_op (int) ; 
 int /*<<< orphan*/  convert_gs_stencil_side (int) ; 
 int /*<<< orphan*/  glStencilOpSeparate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

void device_stencil_op(gs_device_t *device, enum gs_stencil_side side,
		       enum gs_stencil_op_type fail,
		       enum gs_stencil_op_type zfail,
		       enum gs_stencil_op_type zpass)
{
	GLenum gl_side = convert_gs_stencil_side(side);
	GLenum gl_fail = convert_gs_stencil_op(fail);
	GLenum gl_zfail = convert_gs_stencil_op(zfail);
	GLenum gl_zpass = convert_gs_stencil_op(zpass);

	glStencilOpSeparate(gl_side, gl_fail, gl_zfail, gl_zpass);
	if (!gl_success("glStencilOpSeparate"))
		blog(LOG_ERROR, "device_stencil_op (GL) failed");

	UNUSED_PARAMETER(device);
}