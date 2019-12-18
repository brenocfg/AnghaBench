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
 int /*<<< orphan*/  glBlendFuncSeparate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_success (char*) ; 

void device_blend_function_separate(gs_device_t *device,
				    enum gs_blend_type src_c,
				    enum gs_blend_type dest_c,
				    enum gs_blend_type src_a,
				    enum gs_blend_type dest_a)
{
	GLenum gl_src_c = convert_gs_blend_type(src_c);
	GLenum gl_dst_c = convert_gs_blend_type(dest_c);
	GLenum gl_src_a = convert_gs_blend_type(src_a);
	GLenum gl_dst_a = convert_gs_blend_type(dest_a);

	glBlendFuncSeparate(gl_src_c, gl_dst_c, gl_src_a, gl_dst_a);
	if (!gl_success("glBlendFuncSeparate"))
		blog(LOG_ERROR, "device_blend_function_separate (GL) failed");

	UNUSED_PARAMETER(device);
}