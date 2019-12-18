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
struct obs_core_video {int /*<<< orphan*/ * render_texture; int /*<<< orphan*/  texture_rendered; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;
typedef  int /*<<< orphan*/  gs_eparam_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;
typedef  enum gs_blend_type { ____Placeholder_gs_blend_type } gs_blend_type ;
struct TYPE_2__ {struct obs_core_video video; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_EFFECT_DEFAULT ; 
 int /*<<< orphan*/  gs_blend_function_separate (int,int,int,int) ; 
 int /*<<< orphan*/  gs_blend_state_pop () ; 
 int /*<<< orphan*/  gs_blend_state_push () ; 
 int /*<<< orphan*/  gs_draw_sprite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gs_effect_get_param_by_name (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ gs_effect_loop (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gs_effect_set_texture (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* obs ; 
 int /*<<< orphan*/ * obs_get_base_effect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void obs_render_main_texture_internal(enum gs_blend_type src_c,
					     enum gs_blend_type dest_c,
					     enum gs_blend_type src_a,
					     enum gs_blend_type dest_a)
{
	struct obs_core_video *video;
	gs_texture_t *tex;
	gs_effect_t *effect;
	gs_eparam_t *param;

	if (!obs)
		return;

	video = &obs->video;
	if (!video->texture_rendered)
		return;

	tex = video->render_texture;
	effect = obs_get_base_effect(OBS_EFFECT_DEFAULT);
	param = gs_effect_get_param_by_name(effect, "image");
	gs_effect_set_texture(param, tex);

	gs_blend_state_push();
	gs_blend_function_separate(src_c, dest_c, src_a, dest_a);

	while (gs_effect_loop(effect, "Draw"))
		gs_draw_sprite(tex, 0, 0, 0);

	gs_blend_state_pop();
}