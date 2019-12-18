#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct vec4 {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;
struct gpu_delay_filter_data {int processed_frame; TYPE_1__ frames; scalar_t__ cy; scalar_t__ cx; int /*<<< orphan*/  context; int /*<<< orphan*/  target_valid; } ;
struct frame {int /*<<< orphan*/  render; } ;
typedef  int /*<<< orphan*/  obs_source_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;
typedef  int /*<<< orphan*/  frame ;

/* Variables and functions */
 int /*<<< orphan*/  GS_BLEND_ONE ; 
 int /*<<< orphan*/  GS_BLEND_ZERO ; 
 int /*<<< orphan*/  GS_CLEAR_COLOR ; 
 int OBS_SOURCE_ASYNC ; 
 int OBS_SOURCE_CUSTOM_DRAW ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  circlebuf_pop_front (TYPE_1__*,struct frame*,int) ; 
 int /*<<< orphan*/  circlebuf_push_back (TYPE_1__*,struct frame*,int) ; 
 int /*<<< orphan*/  draw_frame (struct gpu_delay_filter_data*) ; 
 int /*<<< orphan*/  gs_blend_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_blend_state_pop () ; 
 int /*<<< orphan*/  gs_blend_state_push () ; 
 int /*<<< orphan*/  gs_clear (int /*<<< orphan*/ ,struct vec4*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_ortho (float,float,float,float,float,float) ; 
 scalar_t__ gs_texrender_begin (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gs_texrender_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_texrender_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_filter_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_filter_get_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_default_render (int /*<<< orphan*/ *) ; 
 int obs_source_get_output_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_skip_video_filter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_video_render (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vec4_zero (struct vec4*) ; 

__attribute__((used)) static void gpu_delay_filter_render(void *data, gs_effect_t *effect)
{
	struct gpu_delay_filter_data *f = data;
	obs_source_t *target = obs_filter_get_target(f->context);
	obs_source_t *parent = obs_filter_get_parent(f->context);

	if (!f->target_valid || !target || !parent || !f->frames.size) {
		obs_source_skip_video_filter(f->context);
		return;
	}

	if (f->processed_frame) {
		draw_frame(f);
		return;
	}

	struct frame frame;
	circlebuf_pop_front(&f->frames, &frame, sizeof(frame));

	gs_texrender_reset(frame.render);

	gs_blend_state_push();
	gs_blend_function(GS_BLEND_ONE, GS_BLEND_ZERO);

	if (gs_texrender_begin(frame.render, f->cx, f->cy)) {
		uint32_t parent_flags = obs_source_get_output_flags(target);
		bool custom_draw = (parent_flags & OBS_SOURCE_CUSTOM_DRAW) != 0;
		bool async = (parent_flags & OBS_SOURCE_ASYNC) != 0;
		struct vec4 clear_color;

		vec4_zero(&clear_color);
		gs_clear(GS_CLEAR_COLOR, &clear_color, 0.0f, 0);
		gs_ortho(0.0f, (float)f->cx, 0.0f, (float)f->cy, -100.0f,
			 100.0f);

		if (target == parent && !custom_draw && !async)
			obs_source_default_render(target);
		else
			obs_source_video_render(target);

		gs_texrender_end(frame.render);
	}

	gs_blend_state_pop();

	circlebuf_push_back(&f->frames, &frame, sizeof(frame));
	draw_frame(f);
	f->processed_frame = true;

	UNUSED_PARAMETER(effect);
}