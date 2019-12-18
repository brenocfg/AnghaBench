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
struct slide_info {int /*<<< orphan*/  effect; int /*<<< orphan*/  tex_b_dir_param; int /*<<< orphan*/  tex_a_dir_param; int /*<<< orphan*/  b_param; int /*<<< orphan*/  a_param; struct vec2 dir; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;

/* Variables and functions */
 float cubic_ease_in_out (float) ; 
 int /*<<< orphan*/  gs_draw_sprite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gs_effect_loop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gs_effect_set_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_effect_set_vec2 (int /*<<< orphan*/ ,struct vec2*) ; 
 int /*<<< orphan*/  vec2_mulf (struct vec2*,struct vec2*,float) ; 

__attribute__((used)) static void slide_callback(void *data, gs_texture_t *a, gs_texture_t *b,
			   float t, uint32_t cx, uint32_t cy)
{
	struct slide_info *slide = data;

	struct vec2 tex_a_dir = slide->dir;
	struct vec2 tex_b_dir = slide->dir;

	t = cubic_ease_in_out(t);

	vec2_mulf(&tex_a_dir, &tex_a_dir, t);
	vec2_mulf(&tex_b_dir, &tex_b_dir, 1.0f - t);

	gs_effect_set_texture(slide->a_param, a);
	gs_effect_set_texture(slide->b_param, b);

	gs_effect_set_vec2(slide->tex_a_dir_param, &tex_a_dir);
	gs_effect_set_vec2(slide->tex_b_dir_param, &tex_b_dir);

	while (gs_effect_loop(slide->effect, "Slide"))
		gs_draw_sprite(NULL, 0, cx, cy);
}