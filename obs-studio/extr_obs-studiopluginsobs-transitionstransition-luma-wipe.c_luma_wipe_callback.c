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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * texture; } ;
struct luma_wipe_info {float softness; int /*<<< orphan*/  effect; int /*<<< orphan*/  ep_softness; int /*<<< orphan*/  invert_luma; int /*<<< orphan*/  ep_invert; int /*<<< orphan*/  ep_progress; TYPE_1__ luma_image; int /*<<< orphan*/  ep_l_tex; int /*<<< orphan*/  ep_b_tex; int /*<<< orphan*/  ep_a_tex; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_draw_sprite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gs_effect_loop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gs_effect_set_bool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_effect_set_float (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  gs_effect_set_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void luma_wipe_callback(void *data, gs_texture_t *a, gs_texture_t *b,
			       float t, uint32_t cx, uint32_t cy)
{
	struct luma_wipe_info *lwipe = data;

	gs_effect_set_texture(lwipe->ep_a_tex, a);
	gs_effect_set_texture(lwipe->ep_b_tex, b);
	gs_effect_set_texture(lwipe->ep_l_tex, lwipe->luma_image.texture);
	gs_effect_set_float(lwipe->ep_progress, t);

	gs_effect_set_bool(lwipe->ep_invert, lwipe->invert_luma);
	gs_effect_set_float(lwipe->ep_softness, lwipe->softness);

	while (gs_effect_loop(lwipe->effect, "LumaWipe"))
		gs_draw_sprite(NULL, 0, cx, cy);
}