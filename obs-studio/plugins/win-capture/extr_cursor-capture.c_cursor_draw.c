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
struct TYPE_2__ {long x; long y; } ;
struct cursor_data {long x_hotspot; long y_hotspot; int /*<<< orphan*/  texture; scalar_t__ visible; TYPE_1__ cursor_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_BLEND_INVSRCALPHA ; 
 int /*<<< orphan*/  GS_BLEND_SRCALPHA ; 
 int /*<<< orphan*/  gs_blend_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_blend_state_pop () ; 
 int /*<<< orphan*/  gs_blend_state_push () ; 
 int /*<<< orphan*/  gs_enable_color (int,int,int,int) ; 
 int /*<<< orphan*/  gs_matrix_pop () ; 
 int /*<<< orphan*/  gs_matrix_push () ; 
 int /*<<< orphan*/  gs_matrix_scale3f (float,float,float) ; 
 int /*<<< orphan*/  obs_source_draw (int /*<<< orphan*/ ,long,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void cursor_draw(struct cursor_data *data, long x_offset, long y_offset,
		 float x_scale, float y_scale, long width, long height)
{
	long x = data->cursor_pos.x + x_offset;
	long y = data->cursor_pos.y + y_offset;
	long x_draw = x - data->x_hotspot;
	long y_draw = y - data->y_hotspot;

	if (x < 0 || x > width || y < 0 || y > height)
		return;

	if (data->visible && !!data->texture) {
		gs_blend_state_push();
		gs_blend_function(GS_BLEND_SRCALPHA, GS_BLEND_INVSRCALPHA);
		gs_enable_color(true, true, true, false);

		gs_matrix_push();
		gs_matrix_scale3f(x_scale, y_scale, 1.0f);
		obs_source_draw(data->texture, x_draw, y_draw, 0, 0, false);
		gs_matrix_pop();

		gs_enable_color(true, true, true, true);
		gs_blend_state_pop();
	}
}