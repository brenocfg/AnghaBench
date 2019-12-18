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
struct TYPE_3__ {int /*<<< orphan*/  tex; int /*<<< orphan*/  y_render; int /*<<< orphan*/  x_render; } ;
typedef  TYPE_1__ xcb_xcursor_t ;
typedef  int /*<<< orphan*/  gs_eparam_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  GS_BLEND_INVSRCALPHA ; 
 int /*<<< orphan*/  GS_BLEND_SRCALPHA ; 
 int /*<<< orphan*/  gs_blend_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_blend_state_pop () ; 
 int /*<<< orphan*/  gs_blend_state_push () ; 
 int /*<<< orphan*/  gs_draw_sprite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gs_effect_get_param_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gs_effect_set_texture (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_enable_color (int,int,int,int) ; 
 int /*<<< orphan*/ * gs_get_effect () ; 
 int /*<<< orphan*/  gs_matrix_pop () ; 
 int /*<<< orphan*/  gs_matrix_push () ; 
 int /*<<< orphan*/  gs_matrix_translate3f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 

void xcb_xcursor_render(xcb_xcursor_t *data)
{
	if (!data->tex)
		return;

	gs_effect_t *effect = gs_get_effect();
	gs_eparam_t *image = gs_effect_get_param_by_name(effect, "image");
	gs_effect_set_texture(image, data->tex);

	gs_blend_state_push();
	gs_blend_function(GS_BLEND_SRCALPHA, GS_BLEND_INVSRCALPHA);
	gs_enable_color(true, true, true, false);

	gs_matrix_push();
	gs_matrix_translate3f(data->x_render, data->y_render, 0.0f);
	gs_draw_sprite(data->tex, 0, 0, 0);
	gs_matrix_pop();

	gs_enable_color(true, true, true, true);
	gs_blend_state_pop();
}