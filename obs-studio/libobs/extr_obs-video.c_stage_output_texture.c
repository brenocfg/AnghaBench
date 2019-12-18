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
struct obs_core_video {int* textures_copied; int /*<<< orphan*/ * convert_textures; int /*<<< orphan*/ *** copy_surfaces; scalar_t__ texture_converted; int /*<<< orphan*/  output_texture; int /*<<< orphan*/  gpu_conversion; } ;
typedef  int /*<<< orphan*/  gs_stagesurf_t ;

/* Variables and functions */
 int NUM_CHANNELS ; 
 int /*<<< orphan*/  gs_stage_texture (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stage_output_texture_name ; 
 int /*<<< orphan*/  unmap_last_surface (struct obs_core_video*) ; 

__attribute__((used)) static inline void stage_output_texture(struct obs_core_video *video,
					int cur_texture)
{
	profile_start(stage_output_texture_name);

	unmap_last_surface(video);

	if (!video->gpu_conversion) {
		gs_stagesurf_t *copy = video->copy_surfaces[cur_texture][0];
		if (copy)
			gs_stage_texture(copy, video->output_texture);

		video->textures_copied[cur_texture] = true;
	} else if (video->texture_converted) {
		for (int i = 0; i < NUM_CHANNELS; i++) {
			gs_stagesurf_t *copy =
				video->copy_surfaces[cur_texture][i];
			if (copy)
				gs_stage_texture(copy,
						 video->convert_textures[i]);
		}

		video->textures_copied[cur_texture] = true;
	}

	profile_end(stage_output_texture_name);
}