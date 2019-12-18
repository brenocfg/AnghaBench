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
typedef  int /*<<< orphan*/ * PFNWGLGETEXTENSIONSSTRINGEXTPROC ;
typedef  int /*<<< orphan*/ * PFNWGLGETEXTENSIONSSTRINGARBPROC ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;

/* Variables and functions */
 int /*<<< orphan*/  find_coreWGL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_extensionsWGL () ; 
 int /*<<< orphan*/  load_WGL_3DL_stereo_control (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_AMD_gpu_association (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_ARB_buffer_region (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_ARB_create_context (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_ARB_extensions_string (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_ARB_make_current_read (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_ARB_pbuffer (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_ARB_pixel_format (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_ARB_render_texture (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_EXT_display_color_table (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_EXT_extensions_string (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_EXT_make_current_read (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_EXT_pbuffer (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_EXT_pixel_format (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_EXT_swap_control (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_I3D_digital_video_control (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_I3D_gamma (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_I3D_genlock (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_I3D_image_buffer (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_I3D_swap_frame_lock (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_I3D_swap_frame_usage (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_NV_DX_interop (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_NV_copy_image (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_NV_delay_before_swap (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_NV_gpu_affinity (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_NV_present_video (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_NV_swap_group (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_NV_vertex_array_range (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_NV_video_capture (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_NV_video_output (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_WGL_OML_sync_control (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/ * wglGetExtensionsStringARB ; 
 int /*<<< orphan*/ * wglGetExtensionsStringEXT ; 

void gladLoadWGLLoader(GLADloadproc load, HDC hdc) {
	wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)load("wglGetExtensionsStringARB");
	wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)load("wglGetExtensionsStringEXT");
	if(wglGetExtensionsStringARB == NULL && wglGetExtensionsStringEXT == NULL) return;
	find_coreWGL(hdc);

	find_extensionsWGL();
	load_WGL_I3D_image_buffer(load);
	load_WGL_I3D_swap_frame_usage(load);
	load_WGL_NV_delay_before_swap(load);
	load_WGL_OML_sync_control(load);
	load_WGL_ARB_create_context(load);
	load_WGL_NV_swap_group(load);
	load_WGL_NV_gpu_affinity(load);
	load_WGL_EXT_pixel_format(load);
	load_WGL_ARB_extensions_string(load);
	load_WGL_NV_video_capture(load);
	load_WGL_ARB_render_texture(load);
	load_WGL_ARB_pixel_format(load);
	load_WGL_I3D_genlock(load);
	load_WGL_NV_DX_interop(load);
	load_WGL_3DL_stereo_control(load);
	load_WGL_EXT_pbuffer(load);
	load_WGL_EXT_display_color_table(load);
	load_WGL_NV_video_output(load);
	load_WGL_I3D_gamma(load);
	load_WGL_NV_copy_image(load);
	load_WGL_NV_present_video(load);
	load_WGL_ARB_make_current_read(load);
	load_WGL_EXT_extensions_string(load);
	load_WGL_EXT_swap_control(load);
	load_WGL_I3D_digital_video_control(load);
	load_WGL_ARB_pbuffer(load);
	load_WGL_NV_vertex_array_range(load);
	load_WGL_AMD_gpu_association(load);
	load_WGL_EXT_make_current_read(load);
	load_WGL_I3D_swap_frame_lock(load);
	load_WGL_ARB_buffer_region(load);

	return;
}