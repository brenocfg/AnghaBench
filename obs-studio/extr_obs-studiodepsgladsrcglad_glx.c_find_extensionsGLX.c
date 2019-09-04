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

/* Variables and functions */
 void* GLAD_GLX_3DFX_multisample ; 
 void* GLAD_GLX_AMD_gpu_association ; 
 void* GLAD_GLX_ARB_create_context ; 
 void* GLAD_GLX_ARB_create_context_profile ; 
 void* GLAD_GLX_ARB_create_context_robustness ; 
 void* GLAD_GLX_ARB_fbconfig_float ; 
 void* GLAD_GLX_ARB_framebuffer_sRGB ; 
 void* GLAD_GLX_ARB_get_proc_address ; 
 void* GLAD_GLX_ARB_multisample ; 
 void* GLAD_GLX_ARB_robustness_application_isolation ; 
 void* GLAD_GLX_ARB_robustness_share_group_isolation ; 
 void* GLAD_GLX_ARB_vertex_buffer_object ; 
 void* GLAD_GLX_EXT_buffer_age ; 
 void* GLAD_GLX_EXT_create_context_es2_profile ; 
 void* GLAD_GLX_EXT_create_context_es_profile ; 
 void* GLAD_GLX_EXT_fbconfig_packed_float ; 
 void* GLAD_GLX_EXT_framebuffer_sRGB ; 
 void* GLAD_GLX_EXT_import_context ; 
 void* GLAD_GLX_EXT_swap_control ; 
 void* GLAD_GLX_EXT_swap_control_tear ; 
 void* GLAD_GLX_EXT_texture_from_pixmap ; 
 void* GLAD_GLX_EXT_visual_info ; 
 void* GLAD_GLX_EXT_visual_rating ; 
 void* GLAD_GLX_INTEL_swap_event ; 
 void* GLAD_GLX_MESA_agp_offset ; 
 void* GLAD_GLX_MESA_copy_sub_buffer ; 
 void* GLAD_GLX_MESA_pixmap_colormap ; 
 void* GLAD_GLX_MESA_query_renderer ; 
 void* GLAD_GLX_MESA_release_buffers ; 
 void* GLAD_GLX_MESA_set_3dfx_mode ; 
 void* GLAD_GLX_MESA_swap_control ; 
 void* GLAD_GLX_NV_copy_image ; 
 void* GLAD_GLX_NV_delay_before_swap ; 
 void* GLAD_GLX_NV_float_buffer ; 
 void* GLAD_GLX_NV_multisample_coverage ; 
 void* GLAD_GLX_NV_present_video ; 
 void* GLAD_GLX_NV_swap_group ; 
 void* GLAD_GLX_NV_video_capture ; 
 void* GLAD_GLX_NV_video_output ; 
 void* GLAD_GLX_OML_swap_method ; 
 void* GLAD_GLX_OML_sync_control ; 
 void* GLAD_GLX_SGIS_blended_overlay ; 
 void* GLAD_GLX_SGIS_multisample ; 
 void* GLAD_GLX_SGIS_shared_multisample ; 
 void* GLAD_GLX_SGIX_dmbuffer ; 
 void* GLAD_GLX_SGIX_fbconfig ; 
 void* GLAD_GLX_SGIX_hyperpipe ; 
 void* GLAD_GLX_SGIX_pbuffer ; 
 void* GLAD_GLX_SGIX_swap_barrier ; 
 void* GLAD_GLX_SGIX_swap_group ; 
 void* GLAD_GLX_SGIX_video_resize ; 
 void* GLAD_GLX_SGIX_video_source ; 
 void* GLAD_GLX_SGIX_visual_select_group ; 
 void* GLAD_GLX_SGI_cushion ; 
 void* GLAD_GLX_SGI_make_current_read ; 
 void* GLAD_GLX_SGI_swap_control ; 
 void* GLAD_GLX_SGI_video_sync ; 
 void* GLAD_GLX_SUN_get_transparent_index ; 
 void* has_ext (char*) ; 

__attribute__((used)) static void find_extensionsGLX(void) {
	GLAD_GLX_ARB_framebuffer_sRGB = has_ext("GLX_ARB_framebuffer_sRGB");
	GLAD_GLX_EXT_import_context = has_ext("GLX_EXT_import_context");
	GLAD_GLX_NV_multisample_coverage = has_ext("GLX_NV_multisample_coverage");
	GLAD_GLX_SGIS_shared_multisample = has_ext("GLX_SGIS_shared_multisample");
	GLAD_GLX_SGIX_pbuffer = has_ext("GLX_SGIX_pbuffer");
	GLAD_GLX_NV_swap_group = has_ext("GLX_NV_swap_group");
	GLAD_GLX_ARB_fbconfig_float = has_ext("GLX_ARB_fbconfig_float");
	GLAD_GLX_SGIX_hyperpipe = has_ext("GLX_SGIX_hyperpipe");
	GLAD_GLX_ARB_robustness_share_group_isolation = has_ext("GLX_ARB_robustness_share_group_isolation");
	GLAD_GLX_INTEL_swap_event = has_ext("GLX_INTEL_swap_event");
	GLAD_GLX_SGIX_video_resize = has_ext("GLX_SGIX_video_resize");
	GLAD_GLX_EXT_create_context_es2_profile = has_ext("GLX_EXT_create_context_es2_profile");
	GLAD_GLX_ARB_robustness_application_isolation = has_ext("GLX_ARB_robustness_application_isolation");
	GLAD_GLX_NV_copy_image = has_ext("GLX_NV_copy_image");
	GLAD_GLX_OML_sync_control = has_ext("GLX_OML_sync_control");
	GLAD_GLX_EXT_framebuffer_sRGB = has_ext("GLX_EXT_framebuffer_sRGB");
	GLAD_GLX_SGI_make_current_read = has_ext("GLX_SGI_make_current_read");
	GLAD_GLX_MESA_swap_control = has_ext("GLX_MESA_swap_control");
	GLAD_GLX_SGI_swap_control = has_ext("GLX_SGI_swap_control");
	GLAD_GLX_EXT_fbconfig_packed_float = has_ext("GLX_EXT_fbconfig_packed_float");
	GLAD_GLX_EXT_buffer_age = has_ext("GLX_EXT_buffer_age");
	GLAD_GLX_3DFX_multisample = has_ext("GLX_3DFX_multisample");
	GLAD_GLX_EXT_visual_info = has_ext("GLX_EXT_visual_info");
	GLAD_GLX_SGI_video_sync = has_ext("GLX_SGI_video_sync");
	GLAD_GLX_MESA_agp_offset = has_ext("GLX_MESA_agp_offset");
	GLAD_GLX_SGIS_multisample = has_ext("GLX_SGIS_multisample");
	GLAD_GLX_MESA_set_3dfx_mode = has_ext("GLX_MESA_set_3dfx_mode");
	GLAD_GLX_EXT_texture_from_pixmap = has_ext("GLX_EXT_texture_from_pixmap");
	GLAD_GLX_NV_video_capture = has_ext("GLX_NV_video_capture");
	GLAD_GLX_ARB_multisample = has_ext("GLX_ARB_multisample");
	GLAD_GLX_NV_delay_before_swap = has_ext("GLX_NV_delay_before_swap");
	GLAD_GLX_SGIX_swap_group = has_ext("GLX_SGIX_swap_group");
	GLAD_GLX_EXT_swap_control = has_ext("GLX_EXT_swap_control");
	GLAD_GLX_SGIX_video_source = has_ext("GLX_SGIX_video_source");
	GLAD_GLX_MESA_query_renderer = has_ext("GLX_MESA_query_renderer");
	GLAD_GLX_ARB_create_context = has_ext("GLX_ARB_create_context");
	GLAD_GLX_EXT_create_context_es_profile = has_ext("GLX_EXT_create_context_es_profile");
	GLAD_GLX_SGIX_fbconfig = has_ext("GLX_SGIX_fbconfig");
	GLAD_GLX_MESA_pixmap_colormap = has_ext("GLX_MESA_pixmap_colormap");
	GLAD_GLX_SGIX_visual_select_group = has_ext("GLX_SGIX_visual_select_group");
	GLAD_GLX_NV_video_output = has_ext("GLX_NV_video_output");
	GLAD_GLX_SGIS_blended_overlay = has_ext("GLX_SGIS_blended_overlay");
	GLAD_GLX_SGIX_dmbuffer = has_ext("GLX_SGIX_dmbuffer");
	GLAD_GLX_ARB_create_context_robustness = has_ext("GLX_ARB_create_context_robustness");
	GLAD_GLX_SGIX_swap_barrier = has_ext("GLX_SGIX_swap_barrier");
	GLAD_GLX_EXT_swap_control_tear = has_ext("GLX_EXT_swap_control_tear");
	GLAD_GLX_MESA_release_buffers = has_ext("GLX_MESA_release_buffers");
	GLAD_GLX_EXT_visual_rating = has_ext("GLX_EXT_visual_rating");
	GLAD_GLX_MESA_copy_sub_buffer = has_ext("GLX_MESA_copy_sub_buffer");
	GLAD_GLX_SGI_cushion = has_ext("GLX_SGI_cushion");
	GLAD_GLX_NV_float_buffer = has_ext("GLX_NV_float_buffer");
	GLAD_GLX_OML_swap_method = has_ext("GLX_OML_swap_method");
	GLAD_GLX_NV_present_video = has_ext("GLX_NV_present_video");
	GLAD_GLX_SUN_get_transparent_index = has_ext("GLX_SUN_get_transparent_index");
	GLAD_GLX_AMD_gpu_association = has_ext("GLX_AMD_gpu_association");
	GLAD_GLX_ARB_create_context_profile = has_ext("GLX_ARB_create_context_profile");
	GLAD_GLX_ARB_get_proc_address = has_ext("GLX_ARB_get_proc_address");
	GLAD_GLX_ARB_vertex_buffer_object = has_ext("GLX_ARB_vertex_buffer_object");
}