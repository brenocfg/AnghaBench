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
struct gpu_delay_filter_data {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; int /*<<< orphan*/  frames; } ;
struct frame {int /*<<< orphan*/  render; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;
typedef  int /*<<< orphan*/  gs_eparam_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;
typedef  int /*<<< orphan*/  frame ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_EFFECT_DEFAULT ; 
 int /*<<< orphan*/  circlebuf_peek_front (int /*<<< orphan*/ *,struct frame*,int) ; 
 int /*<<< orphan*/  gs_draw_sprite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gs_effect_get_param_by_name (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ gs_effect_loop (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gs_effect_set_texture (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gs_texrender_get_texture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_get_base_effect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw_frame(struct gpu_delay_filter_data *f)
{
	struct frame frame;
	circlebuf_peek_front(&f->frames, &frame, sizeof(frame));

	gs_effect_t *effect = obs_get_base_effect(OBS_EFFECT_DEFAULT);
	gs_texture_t *tex = gs_texrender_get_texture(frame.render);
	if (tex) {
		gs_eparam_t *image =
			gs_effect_get_param_by_name(effect, "image");
		gs_effect_set_texture(image, tex);

		while (gs_effect_loop(effect, "Draw"))
			gs_draw_sprite(tex, 0, f->cx, f->cy);
	}
}