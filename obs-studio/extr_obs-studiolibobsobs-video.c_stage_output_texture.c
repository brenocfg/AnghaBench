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
struct obs_core_video {int* textures_converted; int* textures_output; int* textures_copied; int /*<<< orphan*/ ** output_textures; int /*<<< orphan*/ ** convert_textures; scalar_t__ gpu_conversion; int /*<<< orphan*/ ** copy_surfaces; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;
typedef  int /*<<< orphan*/  gs_stagesurf_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_stage_texture (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  profile_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stage_output_texture_name ; 
 int /*<<< orphan*/  unmap_last_surface (struct obs_core_video*) ; 

__attribute__((used)) static inline void stage_output_texture(struct obs_core_video *video,
		int cur_texture, int prev_texture)
{
	profile_start(stage_output_texture_name);

	gs_texture_t   *texture;
	bool        texture_ready;
	gs_stagesurf_t *copy = video->copy_surfaces[cur_texture];

	if (video->gpu_conversion) {
		texture = video->convert_textures[prev_texture];
		texture_ready = video->textures_converted[prev_texture];
	} else {
		texture = video->output_textures[prev_texture];
		texture_ready = video->textures_output[prev_texture];
	}

	unmap_last_surface(video);

	if (!texture_ready)
		goto end;

	gs_stage_texture(copy, texture);

	video->textures_copied[cur_texture] = true;

end:
	profile_end(stage_output_texture_name);
}