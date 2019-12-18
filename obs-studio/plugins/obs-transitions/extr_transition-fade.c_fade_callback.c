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
struct fade_info {int /*<<< orphan*/  effect; int /*<<< orphan*/  fade_param; int /*<<< orphan*/  b_param; int /*<<< orphan*/  a_param; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_draw_sprite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gs_effect_loop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gs_effect_set_float (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  gs_effect_set_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fade_callback(void *data, gs_texture_t *a, gs_texture_t *b, float t,
			  uint32_t cx, uint32_t cy)
{
	struct fade_info *fade = data;

	gs_effect_set_texture(fade->a_param, a);
	gs_effect_set_texture(fade->b_param, b);
	gs_effect_set_float(fade->fade_param, t);

	while (gs_effect_loop(fade->effect, "Fade"))
		gs_draw_sprite(NULL, 0, cx, cy);
}