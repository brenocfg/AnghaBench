#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct obs_video_info {scalar_t__ output_format; int /*<<< orphan*/  output_width; } ;
struct obs_core_video {int using_nv12_tex; int gpu_conversion; int /*<<< orphan*/ * convert_textures; int /*<<< orphan*/  conversion_height; } ;
struct TYPE_2__ {struct obs_core_video video; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_RENDER_TARGET ; 
 int /*<<< orphan*/  GS_RGBA ; 
 int /*<<< orphan*/  LOG_INFO ; 
 size_t NUM_TEXTURES ; 
 scalar_t__ VIDEO_FORMAT_NV12 ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  calc_gpu_conversion_sizes (struct obs_video_info*) ; 
 int gs_nv12_available () ; 
 int /*<<< orphan*/  gs_texture_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* obs ; 

__attribute__((used)) static bool obs_init_gpu_conversion(struct obs_video_info *ovi)
{
	struct obs_core_video *video = &obs->video;

	calc_gpu_conversion_sizes(ovi);

	video->using_nv12_tex = ovi->output_format == VIDEO_FORMAT_NV12
		? gs_nv12_available() : false;

	if (!video->conversion_height) {
		blog(LOG_INFO, "GPU conversion not available for format: %u",
				(unsigned int)ovi->output_format);
		video->gpu_conversion = false;
		video->using_nv12_tex = false;
		blog(LOG_INFO, "NV12 texture support not available");
		return true;
	}

	if (video->using_nv12_tex)
		blog(LOG_INFO, "NV12 texture support enabled");
	else
		blog(LOG_INFO, "NV12 texture support not available");

	for (size_t i = 0; i < NUM_TEXTURES; i++) {
#ifdef _WIN32
		if (video->using_nv12_tex) {
			gs_texture_create_nv12(
					&video->convert_textures[i],
					&video->convert_uv_textures[i],
					ovi->output_width, ovi->output_height,
					GS_RENDER_TARGET | GS_SHARED_KM_TEX);
			if (!video->convert_uv_textures[i])
				return false;
		} else {
#endif
			video->convert_textures[i] = gs_texture_create(
					ovi->output_width,
					video->conversion_height,
					GS_RGBA, 1, NULL, GS_RENDER_TARGET);
#ifdef _WIN32
		}
#endif

		if (!video->convert_textures[i])
			return false;
	}

	return true;
}