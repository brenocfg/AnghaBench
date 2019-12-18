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
typedef  enum gs_blend_type { ____Placeholder_gs_blend_type } gs_blend_type ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  convert_gs_blend_type (int) ; 
 int /*<<< orphan*/  glBlendFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

void device_blend_function(gs_device_t *device, enum gs_blend_type src,
			   enum gs_blend_type dest)
{
	GLenum gl_src = convert_gs_blend_type(src);
	GLenum gl_dst = convert_gs_blend_type(dest);

	glBlendFunc(gl_src, gl_dst);
	if (!gl_success("glBlendFunc"))
		blog(LOG_ERROR, "device_blend_function (GL) failed");

	UNUSED_PARAMETER(device);
}