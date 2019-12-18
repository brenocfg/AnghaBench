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
struct obs_video_info {int /*<<< orphan*/  output_height; int /*<<< orphan*/  output_width; int /*<<< orphan*/  base_height; int /*<<< orphan*/  base_width; } ;
struct obs_core_video {void* output_texture; void* render_texture; scalar_t__** copy_surfaces; scalar_t__ gpu_conversion; scalar_t__ using_nv12_tex; } ;
struct TYPE_2__ {struct obs_core_video video; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_RENDER_TARGET ; 
 int /*<<< orphan*/  GS_RGBA ; 
 size_t NUM_TEXTURES ; 
 scalar_t__ gs_stagesurface_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gs_stagesurface_create_nv12 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* gs_texture_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* obs ; 
 int /*<<< orphan*/  obs_init_gpu_copy_surfaces (struct obs_video_info*,size_t) ; 

__attribute__((used)) static bool obs_init_textures(struct obs_video_info *ovi)
{
	struct obs_core_video *video = &obs->video;

	for (size_t i = 0; i < NUM_TEXTURES; i++) {
#ifdef _WIN32
		if (video->using_nv12_tex) {
			video->copy_surfaces[i][0] =
				gs_stagesurface_create_nv12(ovi->output_width,
							    ovi->output_height);
			if (!video->copy_surfaces[i][0])
				return false;

		} else {
#endif
			if (video->gpu_conversion) {
				if (!obs_init_gpu_copy_surfaces(ovi, i))
					return false;
			} else {
				video->copy_surfaces[i][0] =
					gs_stagesurface_create(
						ovi->output_width,
						ovi->output_height, GS_RGBA);
				if (!video->copy_surfaces[i][0])
					return false;
			}
#ifdef _WIN32
		}
#endif
	}

	video->render_texture = gs_texture_create(ovi->base_width,
						  ovi->base_height, GS_RGBA, 1,
						  NULL, GS_RENDER_TARGET);

	if (!video->render_texture)
		return false;

	video->output_texture = gs_texture_create(ovi->output_width,
						  ovi->output_height, GS_RGBA,
						  1, NULL, GS_RENDER_TARGET);

	if (!video->output_texture)
		return false;

	return true;
}