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
typedef  int /*<<< orphan*/  gs_eparam_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;
struct TYPE_2__ {int /*<<< orphan*/  cursor; scalar_t__ show_cursor; int /*<<< orphan*/  texture; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_EFFECT_DEFAULT ; 
 int /*<<< orphan*/  OBS_EFFECT_OPAQUE ; 
 int /*<<< orphan*/  XSHM_DATA (void*) ; 
 TYPE_1__* data ; 
 int /*<<< orphan*/  gs_draw_sprite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gs_effect_get_param_by_name (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ gs_effect_loop (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gs_effect_set_texture (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_get_base_effect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_xcursor_render (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xshm_video_render(void *vptr, gs_effect_t *effect)
{
	XSHM_DATA(vptr);

	effect = obs_get_base_effect(OBS_EFFECT_OPAQUE);

	if (!data->texture)
		return;

	gs_eparam_t *image = gs_effect_get_param_by_name(effect, "image");
	gs_effect_set_texture(image, data->texture);

	while (gs_effect_loop(effect, "Draw")) {
		gs_draw_sprite(data->texture, 0, 0, 0);
	}

	if (data->show_cursor) {
		effect = obs_get_base_effect(OBS_EFFECT_DEFAULT);

		while (gs_effect_loop(effect, "Draw")) {
			xcb_xcursor_render(data->cursor);
		}
	}
}