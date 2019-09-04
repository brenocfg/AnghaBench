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
struct duplicator_capture {int rot; scalar_t__ capture_cursor; scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  duplicator; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_EFFECT_DEFAULT ; 
 int /*<<< orphan*/  OBS_EFFECT_OPAQUE ; 
 int /*<<< orphan*/  RAD (float) ; 
 int /*<<< orphan*/  draw_cursor (struct duplicator_capture*) ; 
 int /*<<< orphan*/ * gs_duplicator_get_texture (int /*<<< orphan*/ ) ; 
 scalar_t__ gs_effect_loop (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gs_matrix_pop () ; 
 int /*<<< orphan*/  gs_matrix_push () ; 
 int /*<<< orphan*/  gs_matrix_rotaa4f (float,float,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_matrix_translate3f (float,float,float) ; 
 int /*<<< orphan*/ * obs_get_base_effect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_draw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void duplicator_capture_render(void *data, gs_effect_t *effect)
{
	struct duplicator_capture *capture = data;
	gs_texture_t *texture;
	int rot;

	if (!capture->duplicator)
		return;

	texture = gs_duplicator_get_texture(capture->duplicator);
	if (!texture)
		return;

	effect = obs_get_base_effect(OBS_EFFECT_OPAQUE);

	rot = capture->rot;

	while (gs_effect_loop(effect, "Draw")) {
		if (rot != 0) {
			float x = 0.0f;
			float y = 0.0f;

			switch (rot) {
			case 90:
				x = (float)capture->height;
				break;
			case 180:
				x = (float)capture->width;
				y = (float)capture->height;
				break;
			case 270:
				y = (float)capture->width;
				break;
			}

			gs_matrix_push();
			gs_matrix_translate3f(x, y, 0.0f);
			gs_matrix_rotaa4f(0.0f, 0.0f, 1.0f, RAD((float)rot));
		}

		obs_source_draw(texture, 0, 0, 0, 0, false);

		if (rot != 0)
			gs_matrix_pop();
	}

	if (capture->capture_cursor) {
		effect = obs_get_base_effect(OBS_EFFECT_DEFAULT);

		while (gs_effect_loop(effect, "Draw")) {
			draw_cursor(capture);
		}
	}
}