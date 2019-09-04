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
typedef  int /*<<< orphan*/ * PFNGLXQUERYVERSIONPROC ;
typedef  scalar_t__ (* GLADloadproc ) (char*) ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  find_coreGLX (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  find_extensionsGLX () ; 
 int /*<<< orphan*/ * glXQueryVersion ; 
 int /*<<< orphan*/  load_GLX_ARB_create_context (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_ARB_get_proc_address (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_EXT_import_context (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_EXT_swap_control (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_EXT_texture_from_pixmap (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_MESA_agp_offset (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_MESA_copy_sub_buffer (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_MESA_pixmap_colormap (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_MESA_query_renderer (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_MESA_release_buffers (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_MESA_set_3dfx_mode (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_MESA_swap_control (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_NV_copy_image (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_NV_delay_before_swap (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_NV_present_video (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_NV_swap_group (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_NV_video_capture (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_NV_video_output (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_OML_sync_control (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_SGIX_dmbuffer (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_SGIX_fbconfig (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_SGIX_hyperpipe (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_SGIX_pbuffer (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_SGIX_swap_barrier (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_SGIX_swap_group (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_SGIX_video_resize (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_SGIX_video_source (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_SGI_cushion (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_SGI_make_current_read (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_SGI_swap_control (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_SGI_video_sync (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_SUN_get_transparent_index (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_VERSION_1_0 (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_VERSION_1_1 (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_VERSION_1_2 (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_VERSION_1_3 (scalar_t__ (*) (char*)) ; 
 int /*<<< orphan*/  load_GLX_VERSION_1_4 (scalar_t__ (*) (char*)) ; 

void gladLoadGLXLoader(GLADloadproc load, Display *dpy, int screen) {
	glXQueryVersion = (PFNGLXQUERYVERSIONPROC)load("glXQueryVersion");
	if(glXQueryVersion == NULL) return;
	find_coreGLX(dpy, screen);
	load_GLX_VERSION_1_0(load);
	load_GLX_VERSION_1_1(load);
	load_GLX_VERSION_1_2(load);
	load_GLX_VERSION_1_3(load);
	load_GLX_VERSION_1_4(load);

	find_extensionsGLX();
	load_GLX_EXT_import_context(load);
	load_GLX_SGIX_pbuffer(load);
	load_GLX_NV_swap_group(load);
	load_GLX_SGIX_hyperpipe(load);
	load_GLX_SGIX_video_resize(load);
	load_GLX_NV_copy_image(load);
	load_GLX_OML_sync_control(load);
	load_GLX_SGI_make_current_read(load);
	load_GLX_MESA_swap_control(load);
	load_GLX_SGI_swap_control(load);
	load_GLX_SGI_video_sync(load);
	load_GLX_MESA_agp_offset(load);
	load_GLX_MESA_set_3dfx_mode(load);
	load_GLX_EXT_texture_from_pixmap(load);
	load_GLX_NV_video_capture(load);
	load_GLX_NV_delay_before_swap(load);
	load_GLX_SGIX_swap_group(load);
	load_GLX_EXT_swap_control(load);
	load_GLX_SGIX_video_source(load);
	load_GLX_MESA_query_renderer(load);
	load_GLX_ARB_create_context(load);
	load_GLX_SGIX_fbconfig(load);
	load_GLX_MESA_pixmap_colormap(load);
	load_GLX_NV_video_output(load);
	load_GLX_SGIX_dmbuffer(load);
	load_GLX_SGIX_swap_barrier(load);
	load_GLX_MESA_release_buffers(load);
	load_GLX_MESA_copy_sub_buffer(load);
	load_GLX_SGI_cushion(load);
	load_GLX_NV_present_video(load);
	load_GLX_SUN_get_transparent_index(load);
	load_GLX_ARB_get_proc_address(load);

	return;
}