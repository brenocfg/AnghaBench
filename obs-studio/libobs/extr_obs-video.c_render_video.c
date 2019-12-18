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
struct obs_core_video {scalar_t__ gpu_conversion; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;

/* Variables and functions */
 int /*<<< orphan*/  GS_NEITHER ; 
 int /*<<< orphan*/  gs_begin_scene () ; 
 int /*<<< orphan*/  gs_enable_blending (int) ; 
 int /*<<< orphan*/  gs_enable_depth_test (int) ; 
 int /*<<< orphan*/  gs_end_scene () ; 
 int /*<<< orphan*/  gs_flush () ; 
 int /*<<< orphan*/  gs_set_cull_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_set_render_target (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_gpu_encoders (struct obs_core_video*,int) ; 
 int /*<<< orphan*/  render_convert_texture (struct obs_core_video*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  render_main_texture (struct obs_core_video*) ; 
 int /*<<< orphan*/ * render_output_texture (struct obs_core_video*) ; 
 int /*<<< orphan*/  stage_output_texture (struct obs_core_video*,int) ; 

__attribute__((used)) static inline void render_video(struct obs_core_video *video, bool raw_active,
				const bool gpu_active, int cur_texture)
{
	gs_begin_scene();

	gs_enable_depth_test(false);
	gs_set_cull_mode(GS_NEITHER);

	render_main_texture(video);

	if (raw_active || gpu_active) {
		gs_texture_t *texture = render_output_texture(video);

#ifdef _WIN32
		if (gpu_active)
			gs_flush();
#endif

		if (video->gpu_conversion)
			render_convert_texture(video, texture);

#ifdef _WIN32
		if (gpu_active) {
			gs_flush();
			output_gpu_encoders(video, raw_active);
		}
#endif

		if (raw_active)
			stage_output_texture(video, cur_texture);
	}

	gs_set_render_target(NULL, NULL);
	gs_enable_blending(true);

	gs_end_scene();
}