#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_12__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct transition_state {scalar_t__* s; scalar_t__ transitioning_audio; scalar_t__ transitioning_video; } ;
struct matrix4 {int dummy; } ;
typedef  int /*<<< orphan*/  (* obs_transition_video_render_callback_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float,scalar_t__,scalar_t__) ;
struct TYPE_22__ {int /*<<< orphan*/  data; } ;
struct TYPE_23__ {int transitioning_video; TYPE_2__ context; struct matrix4* transition_matrices; int /*<<< orphan*/  transitioning_audio; } ;
typedef  TYPE_3__ obs_source_t ;
typedef  int /*<<< orphan*/  gs_texture_t ;
struct TYPE_21__ {int /*<<< orphan*/ * transparent_texture; } ;
struct TYPE_20__ {TYPE_1__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_BLEND_INVSRCALPHA ; 
 int /*<<< orphan*/  GS_BLEND_ONE ; 
 int /*<<< orphan*/  copy_transition_state (TYPE_3__*,struct transition_state*) ; 
 scalar_t__ get_cx (TYPE_3__*) ; 
 scalar_t__ get_cy (TYPE_3__*) ; 
 int /*<<< orphan*/ * get_texture (TYPE_3__*,size_t) ; 
 float get_video_time (TYPE_3__*) ; 
 int /*<<< orphan*/  gs_blend_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_blend_state_pop () ; 
 int /*<<< orphan*/  gs_blend_state_push () ; 
 int /*<<< orphan*/  gs_matrix_mul (struct matrix4*) ; 
 int /*<<< orphan*/  gs_matrix_pop () ; 
 int /*<<< orphan*/  gs_matrix_push () ; 
 int /*<<< orphan*/  handle_stop (TYPE_3__*) ; 
 int /*<<< orphan*/  lock_transition (TYPE_3__*) ; 
 TYPE_12__* obs ; 
 int /*<<< orphan*/  obs_source_dosignal (TYPE_3__*,char*,char*) ; 
 int /*<<< orphan*/  obs_source_release (scalar_t__) ; 
 int /*<<< orphan*/  obs_source_video_render (scalar_t__) ; 
 int /*<<< orphan*/  obs_transition_stop (TYPE_3__*) ; 
 int /*<<< orphan*/  render_child (TYPE_3__*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  transition_valid (TYPE_3__*,char*) ; 
 scalar_t__ trylock_textures (TYPE_3__*) ; 
 int /*<<< orphan*/  unlock_textures (TYPE_3__*) ; 
 int /*<<< orphan*/  unlock_transition (TYPE_3__*) ; 

void obs_transition_video_render(obs_source_t *transition,
				 obs_transition_video_render_callback_t callback)
{
	struct transition_state state;
	struct matrix4 matrices[2];
	bool locked = false;
	bool stopped = false;
	bool video_stopped = false;
	float t;

	if (!transition_valid(transition, "obs_transition_video_render"))
		return;

	t = get_video_time(transition);

	lock_transition(transition);

	if (t >= 1.0f && transition->transitioning_video) {
		transition->transitioning_video = false;
		video_stopped = true;

		if (!transition->transitioning_audio) {
			obs_transition_stop(transition);
			stopped = true;
		}
	}
	copy_transition_state(transition, &state);
	matrices[0] = transition->transition_matrices[0];
	matrices[1] = transition->transition_matrices[1];

	unlock_transition(transition);

	if (state.transitioning_video)
		locked = trylock_textures(transition) == 0;

	if (state.transitioning_video && locked && callback) {
		gs_texture_t *tex[2];
		uint32_t cx;
		uint32_t cy;

		for (size_t i = 0; i < 2; i++) {
			if (state.s[i]) {
				render_child(transition, state.s[i], i);
				tex[i] = get_texture(transition, i);
				if (!tex[i])
					tex[i] = obs->video.transparent_texture;
			} else {
				tex[i] = obs->video.transparent_texture;
			}
		}

		cx = get_cx(transition);
		cy = get_cy(transition);
		if (cx && cy) {
			gs_blend_state_push();
			gs_blend_function(GS_BLEND_ONE, GS_BLEND_INVSRCALPHA);

			callback(transition->context.data, tex[0], tex[1], t,
				 cx, cy);

			gs_blend_state_pop();
		}

	} else if (state.transitioning_audio) {
		if (state.s[1]) {
			gs_matrix_push();
			gs_matrix_mul(&matrices[1]);
			obs_source_video_render(state.s[1]);
			gs_matrix_pop();
		}
	} else {
		if (state.s[0]) {
			gs_matrix_push();
			gs_matrix_mul(&matrices[0]);
			obs_source_video_render(state.s[0]);
			gs_matrix_pop();
		}
	}

	if (locked)
		unlock_textures(transition);

	obs_source_release(state.s[0]);
	obs_source_release(state.s[1]);

	if (video_stopped)
		obs_source_dosignal(transition, "source_transition_video_stop",
				    "transition_video_stop");
	if (stopped)
		handle_stop(transition);
}