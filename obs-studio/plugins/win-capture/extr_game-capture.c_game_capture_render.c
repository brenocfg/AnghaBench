#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cursor; scalar_t__ allow_transparency; } ;
struct game_capture {int /*<<< orphan*/  cursor_hidden; TYPE_2__ config; TYPE_1__* global_hook_info; int /*<<< orphan*/  texture; int /*<<< orphan*/  active; } ;
typedef  int /*<<< orphan*/  gs_effect_t ;
struct TYPE_3__ {int /*<<< orphan*/  flip; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_EFFECT_DEFAULT ; 
 int /*<<< orphan*/  OBS_EFFECT_OPAQUE ; 
 int /*<<< orphan*/  game_capture_render_cursor (struct game_capture*) ; 
 scalar_t__ gs_effect_loop (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * obs_get_base_effect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_draw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void game_capture_render(void *data, gs_effect_t *effect)
{
	struct game_capture *gc = data;
	if (!gc->texture || !gc->active)
		return;

	effect = obs_get_base_effect(gc->config.allow_transparency
					     ? OBS_EFFECT_DEFAULT
					     : OBS_EFFECT_OPAQUE);

	while (gs_effect_loop(effect, "Draw")) {
		obs_source_draw(gc->texture, 0, 0, 0, 0,
				gc->global_hook_info->flip);

		if (gc->config.allow_transparency && gc->config.cursor &&
		    !gc->cursor_hidden) {
			game_capture_render_cursor(gc);
		}
	}

	if (!gc->config.allow_transparency && gc->config.cursor &&
	    !gc->cursor_hidden) {
		effect = obs_get_base_effect(OBS_EFFECT_DEFAULT);

		while (gs_effect_loop(effect, "Draw")) {
			game_capture_render_cursor(gc);
		}
	}
}