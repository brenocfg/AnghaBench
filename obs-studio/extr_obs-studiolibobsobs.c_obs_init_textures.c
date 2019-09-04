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
typedef  int /*<<< orphan*/  uint32_t ;
struct obs_video_info {int /*<<< orphan*/  output_height; int /*<<< orphan*/  output_width; int /*<<< orphan*/  base_height; int /*<<< orphan*/  base_width; } ;
struct obs_core_video {void** output_textures; void** render_textures; int /*<<< orphan*/ * copy_surfaces; int /*<<< orphan*/  conversion_height; scalar_t__ gpu_conversion; } ;
struct TYPE_2__ {struct obs_core_video video; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_RENDER_TARGET ; 
 int /*<<< orphan*/  GS_RGBA ; 
 size_t NUM_TEXTURES ; 
 int /*<<< orphan*/  gs_stagesurface_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* gs_texture_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* obs ; 

__attribute__((used)) static bool obs_init_textures(struct obs_video_info *ovi)
{
	struct obs_core_video *video = &obs->video;
	uint32_t output_height = video->gpu_conversion ?
		video->conversion_height : ovi->output_height;
	size_t i;

	for (i = 0; i < NUM_TEXTURES; i++) {
#ifdef _WIN32
		if (video->using_nv12_tex) {
			video->copy_surfaces[i] = gs_stagesurface_create_nv12(
					ovi->output_width, ovi->output_height);
			if (!video->copy_surfaces[i])
				return false;

		} else {
#endif
			video->copy_surfaces[i] = gs_stagesurface_create(
					ovi->output_width, output_height,
					GS_RGBA);
			if (!video->copy_surfaces[i])
				return false;
#ifdef _WIN32
		}
#endif

		video->render_textures[i] = gs_texture_create(
				ovi->base_width, ovi->base_height,
				GS_RGBA, 1, NULL, GS_RENDER_TARGET);

		if (!video->render_textures[i])
			return false;

		video->output_textures[i] = gs_texture_create(
				ovi->output_width, ovi->output_height,
				GS_RGBA, 1, NULL, GS_RENDER_TARGET);

		if (!video->output_textures[i])
			return false;
	}

	return true;
}