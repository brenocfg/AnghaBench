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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  gs_texture_t ;
typedef  int /*<<< orphan*/  gs_eparam_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  GS_FLIP_V ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gs_draw_sprite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gs_effect_get_param_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gs_effect_set_texture (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gs_get_effect () ; 
 int /*<<< orphan*/  gs_matrix_pop () ; 
 int /*<<< orphan*/  gs_matrix_push () ; 
 int /*<<< orphan*/  gs_matrix_translate3f (float,float,float) ; 
 int /*<<< orphan*/  obs_ptr_valid (int /*<<< orphan*/ *,char*) ; 

void obs_source_draw(gs_texture_t *texture, int x, int y, uint32_t cx,
		     uint32_t cy, bool flip)
{
	gs_effect_t *effect = gs_get_effect();
	bool change_pos = (x != 0 || y != 0);
	gs_eparam_t *image;

	if (!effect) {
		blog(LOG_WARNING, "obs_source_draw: no active effect!");
		return;
	}

	if (!obs_ptr_valid(texture, "obs_source_draw"))
		return;

	image = gs_effect_get_param_by_name(effect, "image");
	gs_effect_set_texture(image, texture);

	if (change_pos) {
		gs_matrix_push();
		gs_matrix_translate3f((float)x, (float)y, 0.0f);
	}

	gs_draw_sprite(texture, flip ? GS_FLIP_V : 0, cx, cy);

	if (change_pos)
		gs_matrix_pop();
}