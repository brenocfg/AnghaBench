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
struct vec2 {int dummy; } ;
struct swipe_info {int /*<<< orphan*/  effect; int /*<<< orphan*/  swipe_param; scalar_t__ swipe_in; int /*<<< orphan*/  b_param; int /*<<< orphan*/  a_param; struct vec2 dir; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;

/* Variables and functions */
 float cubic_ease_in_out (float) ; 
 int /*<<< orphan*/  gs_draw_sprite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gs_effect_loop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gs_effect_set_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_effect_set_vec2 (int /*<<< orphan*/ ,struct vec2*) ; 
 int /*<<< orphan*/  vec2_mulf (struct vec2*,struct vec2*,float) ; 
 int /*<<< orphan*/  vec2_neg (struct vec2*,struct vec2*) ; 

__attribute__((used)) static void swipe_callback(void *data, gs_texture_t *a, gs_texture_t *b,
			   float t, uint32_t cx, uint32_t cy)
{
	struct swipe_info *swipe = data;
	struct vec2 swipe_val = swipe->dir;

	if (swipe->swipe_in)
		vec2_neg(&swipe_val, &swipe_val);

	t = cubic_ease_in_out(t);

	vec2_mulf(&swipe_val, &swipe_val, swipe->swipe_in ? 1.0f - t : t);

	gs_effect_set_texture(swipe->a_param, swipe->swipe_in ? b : a);
	gs_effect_set_texture(swipe->b_param, swipe->swipe_in ? a : b);
	gs_effect_set_vec2(swipe->swipe_param, &swipe_val);

	while (gs_effect_loop(swipe->effect, "Swipe"))
		gs_draw_sprite(NULL, 0, cx, cy);
}