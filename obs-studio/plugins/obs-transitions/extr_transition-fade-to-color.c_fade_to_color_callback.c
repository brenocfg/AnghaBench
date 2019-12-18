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
struct fade_to_color_info {float switch_point; int /*<<< orphan*/  effect; int /*<<< orphan*/  color; int /*<<< orphan*/  ep_color; int /*<<< orphan*/  ep_swp; int /*<<< orphan*/  ep_tex; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_draw_sprite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gs_effect_loop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gs_effect_set_float (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  gs_effect_set_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_effect_set_vec4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 float smoothstep (float,float,float) ; 

__attribute__((used)) static void fade_to_color_callback(void *data, gs_texture_t *a, gs_texture_t *b,
				   float t, uint32_t cx, uint32_t cy)
{
	struct fade_to_color_info *fade_to_color = data;

	float sa = smoothstep(0.0f, fade_to_color->switch_point, t);
	float sb = smoothstep(fade_to_color->switch_point, 1.0f, t);

	float swp = t < fade_to_color->switch_point ? sa : 1.0f - sb;

	gs_effect_set_texture(fade_to_color->ep_tex,
			      t < fade_to_color->switch_point ? a : b);
	gs_effect_set_float(fade_to_color->ep_swp, swp);
	gs_effect_set_vec4(fade_to_color->ep_color, &fade_to_color->color);

	while (gs_effect_loop(fade_to_color->effect, "FadeToColor"))
		gs_draw_sprite(NULL, 0, cx, cy);
}