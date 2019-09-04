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
 void* GLAD_WGL_3DFX_multisample ; 
 void* GLAD_WGL_3DL_stereo_control ; 
 void* GLAD_WGL_AMD_gpu_association ; 
 void* GLAD_WGL_ARB_buffer_region ; 
 void* GLAD_WGL_ARB_create_context ; 
 void* GLAD_WGL_ARB_create_context_profile ; 
 void* GLAD_WGL_ARB_create_context_robustness ; 
 void* GLAD_WGL_ARB_extensions_string ; 
 void* GLAD_WGL_ARB_framebuffer_sRGB ; 
 void* GLAD_WGL_ARB_make_current_read ; 
 void* GLAD_WGL_ARB_multisample ; 
 void* GLAD_WGL_ARB_pbuffer ; 
 void* GLAD_WGL_ARB_pixel_format ; 
 void* GLAD_WGL_ARB_pixel_format_float ; 
 void* GLAD_WGL_ARB_render_texture ; 
 void* GLAD_WGL_ARB_robustness_application_isolation ; 
 void* GLAD_WGL_ARB_robustness_share_group_isolation ; 
 void* GLAD_WGL_ATI_pixel_format_float ; 
 void* GLAD_WGL_EXT_create_context_es2_profile ; 
 void* GLAD_WGL_EXT_create_context_es_profile ; 
 void* GLAD_WGL_EXT_depth_float ; 
 void* GLAD_WGL_EXT_display_color_table ; 
 void* GLAD_WGL_EXT_extensions_string ; 
 void* GLAD_WGL_EXT_framebuffer_sRGB ; 
 void* GLAD_WGL_EXT_make_current_read ; 
 void* GLAD_WGL_EXT_multisample ; 
 void* GLAD_WGL_EXT_pbuffer ; 
 void* GLAD_WGL_EXT_pixel_format ; 
 void* GLAD_WGL_EXT_pixel_format_packed_float ; 
 void* GLAD_WGL_EXT_swap_control ; 
 void* GLAD_WGL_EXT_swap_control_tear ; 
 void* GLAD_WGL_I3D_digital_video_control ; 
 void* GLAD_WGL_I3D_gamma ; 
 void* GLAD_WGL_I3D_genlock ; 
 void* GLAD_WGL_I3D_image_buffer ; 
 void* GLAD_WGL_I3D_swap_frame_lock ; 
 void* GLAD_WGL_I3D_swap_frame_usage ; 
 void* GLAD_WGL_NV_DX_interop ; 
 void* GLAD_WGL_NV_DX_interop2 ; 
 void* GLAD_WGL_NV_copy_image ; 
 void* GLAD_WGL_NV_delay_before_swap ; 
 void* GLAD_WGL_NV_float_buffer ; 
 void* GLAD_WGL_NV_gpu_affinity ; 
 void* GLAD_WGL_NV_multisample_coverage ; 
 void* GLAD_WGL_NV_present_video ; 
 void* GLAD_WGL_NV_render_depth_texture ; 
 void* GLAD_WGL_NV_render_texture_rectangle ; 
 void* GLAD_WGL_NV_swap_group ; 
 void* GLAD_WGL_NV_vertex_array_range ; 
 void* GLAD_WGL_NV_video_capture ; 
 void* GLAD_WGL_NV_video_output ; 
 void* GLAD_WGL_OML_sync_control ; 
 void* has_ext (char*) ; 

__attribute__((used)) static void find_extensionsWGL(void) {
	GLAD_WGL_NV_multisample_coverage = has_ext("WGL_NV_multisample_coverage");
	GLAD_WGL_I3D_image_buffer = has_ext("WGL_I3D_image_buffer");
	GLAD_WGL_I3D_swap_frame_usage = has_ext("WGL_I3D_swap_frame_usage");
	GLAD_WGL_NV_DX_interop2 = has_ext("WGL_NV_DX_interop2");
	GLAD_WGL_NV_float_buffer = has_ext("WGL_NV_float_buffer");
	GLAD_WGL_NV_delay_before_swap = has_ext("WGL_NV_delay_before_swap");
	GLAD_WGL_OML_sync_control = has_ext("WGL_OML_sync_control");
	GLAD_WGL_ARB_pixel_format_float = has_ext("WGL_ARB_pixel_format_float");
	GLAD_WGL_ARB_create_context = has_ext("WGL_ARB_create_context");
	GLAD_WGL_NV_swap_group = has_ext("WGL_NV_swap_group");
	GLAD_WGL_NV_gpu_affinity = has_ext("WGL_NV_gpu_affinity");
	GLAD_WGL_EXT_pixel_format = has_ext("WGL_EXT_pixel_format");
	GLAD_WGL_ARB_extensions_string = has_ext("WGL_ARB_extensions_string");
	GLAD_WGL_NV_video_capture = has_ext("WGL_NV_video_capture");
	GLAD_WGL_NV_render_texture_rectangle = has_ext("WGL_NV_render_texture_rectangle");
	GLAD_WGL_EXT_create_context_es_profile = has_ext("WGL_EXT_create_context_es_profile");
	GLAD_WGL_ARB_robustness_share_group_isolation = has_ext("WGL_ARB_robustness_share_group_isolation");
	GLAD_WGL_ARB_render_texture = has_ext("WGL_ARB_render_texture");
	GLAD_WGL_EXT_depth_float = has_ext("WGL_EXT_depth_float");
	GLAD_WGL_EXT_swap_control_tear = has_ext("WGL_EXT_swap_control_tear");
	GLAD_WGL_ARB_pixel_format = has_ext("WGL_ARB_pixel_format");
	GLAD_WGL_ARB_multisample = has_ext("WGL_ARB_multisample");
	GLAD_WGL_I3D_genlock = has_ext("WGL_I3D_genlock");
	GLAD_WGL_NV_DX_interop = has_ext("WGL_NV_DX_interop");
	GLAD_WGL_3DL_stereo_control = has_ext("WGL_3DL_stereo_control");
	GLAD_WGL_EXT_pbuffer = has_ext("WGL_EXT_pbuffer");
	GLAD_WGL_EXT_display_color_table = has_ext("WGL_EXT_display_color_table");
	GLAD_WGL_NV_video_output = has_ext("WGL_NV_video_output");
	GLAD_WGL_ARB_robustness_application_isolation = has_ext("WGL_ARB_robustness_application_isolation");
	GLAD_WGL_3DFX_multisample = has_ext("WGL_3DFX_multisample");
	GLAD_WGL_I3D_gamma = has_ext("WGL_I3D_gamma");
	GLAD_WGL_ARB_framebuffer_sRGB = has_ext("WGL_ARB_framebuffer_sRGB");
	GLAD_WGL_NV_copy_image = has_ext("WGL_NV_copy_image");
	GLAD_WGL_EXT_framebuffer_sRGB = has_ext("WGL_EXT_framebuffer_sRGB");
	GLAD_WGL_NV_present_video = has_ext("WGL_NV_present_video");
	GLAD_WGL_EXT_create_context_es2_profile = has_ext("WGL_EXT_create_context_es2_profile");
	GLAD_WGL_ARB_create_context_robustness = has_ext("WGL_ARB_create_context_robustness");
	GLAD_WGL_ARB_make_current_read = has_ext("WGL_ARB_make_current_read");
	GLAD_WGL_EXT_multisample = has_ext("WGL_EXT_multisample");
	GLAD_WGL_EXT_extensions_string = has_ext("WGL_EXT_extensions_string");
	GLAD_WGL_NV_render_depth_texture = has_ext("WGL_NV_render_depth_texture");
	GLAD_WGL_ATI_pixel_format_float = has_ext("WGL_ATI_pixel_format_float");
	GLAD_WGL_ARB_create_context_profile = has_ext("WGL_ARB_create_context_profile");
	GLAD_WGL_EXT_swap_control = has_ext("WGL_EXT_swap_control");
	GLAD_WGL_I3D_digital_video_control = has_ext("WGL_I3D_digital_video_control");
	GLAD_WGL_ARB_pbuffer = has_ext("WGL_ARB_pbuffer");
	GLAD_WGL_NV_vertex_array_range = has_ext("WGL_NV_vertex_array_range");
	GLAD_WGL_AMD_gpu_association = has_ext("WGL_AMD_gpu_association");
	GLAD_WGL_EXT_pixel_format_packed_float = has_ext("WGL_EXT_pixel_format_packed_float");
	GLAD_WGL_EXT_make_current_read = has_ext("WGL_EXT_make_current_read");
	GLAD_WGL_I3D_swap_frame_lock = has_ext("WGL_I3D_swap_frame_lock");
	GLAD_WGL_ARB_buffer_region = has_ext("WGL_ARB_buffer_region");
}