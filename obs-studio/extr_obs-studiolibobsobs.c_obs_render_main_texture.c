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
struct obs_core_video {int cur_texture; int /*<<< orphan*/ ** render_textures; int /*<<< orphan*/ * textures_rendered; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;
typedef  int /*<<< orphan*/  gs_eparam_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;
struct TYPE_2__ {struct obs_core_video video; } ;

/* Variables and functions */
 int NUM_TEXTURES ; 
 int /*<<< orphan*/  OBS_EFFECT_DEFAULT ; 
 int /*<<< orphan*/  gs_draw_sprite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gs_effect_get_param_by_name (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ gs_effect_loop (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gs_effect_set_texture (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* obs ; 
 int /*<<< orphan*/ * obs_get_base_effect (int /*<<< orphan*/ ) ; 

void obs_render_main_texture(void)
{
	struct obs_core_video *video = &obs->video;
	gs_texture_t *tex;
	gs_effect_t *effect;
	gs_eparam_t *param;
	int last_tex;

	if (!obs) return;

	last_tex = video->cur_texture == 0
		? NUM_TEXTURES - 1
		: video->cur_texture - 1;

	if (!video->textures_rendered[last_tex])
		return;

	tex = video->render_textures[last_tex];
	effect = obs_get_base_effect(OBS_EFFECT_DEFAULT);
	param = gs_effect_get_param_by_name(effect, "image");
	gs_effect_set_texture(param, tex);

	while (gs_effect_loop(effect, "Draw"))
		gs_draw_sprite(tex, 0, 0, 0);
}