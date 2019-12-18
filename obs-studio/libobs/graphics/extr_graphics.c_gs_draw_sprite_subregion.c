#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct gs_vb_data {int dummy; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;
struct TYPE_3__ {int /*<<< orphan*/  sprite_buffer; } ;
typedef  TYPE_1__ graphics_t ;

/* Variables and functions */
 scalar_t__ GS_TEXTURE_2D ; 
 int /*<<< orphan*/  GS_TRISTRIP ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  build_subsprite_norm (struct gs_vb_data*,float,float,float,float,float,float,scalar_t__) ; 
 int /*<<< orphan*/  gs_draw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gs_get_texture_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_load_indexbuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_load_vertexbuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ gs_texture_get_height (int /*<<< orphan*/ *) ; 
 scalar_t__ gs_texture_get_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_vertexbuffer_flush (int /*<<< orphan*/ ) ; 
 struct gs_vb_data* gs_vertexbuffer_get_data (int /*<<< orphan*/ ) ; 
 TYPE_1__* thread_graphics ; 

void gs_draw_sprite_subregion(gs_texture_t *tex, uint32_t flip, uint32_t sub_x,
			      uint32_t sub_y, uint32_t sub_cx, uint32_t sub_cy)
{
	graphics_t *graphics = thread_graphics;
	float fcx, fcy;
	struct gs_vb_data *data;

	if (tex) {
		if (gs_get_texture_type(tex) != GS_TEXTURE_2D) {
			blog(LOG_ERROR, "A sprite must be a 2D texture");
			return;
		}
	}

	fcx = (float)gs_texture_get_width(tex);
	fcy = (float)gs_texture_get_height(tex);

	data = gs_vertexbuffer_get_data(graphics->sprite_buffer);
	build_subsprite_norm(data, (float)sub_x, (float)sub_y, (float)sub_cx,
			     (float)sub_cy, fcx, fcy, flip);

	gs_vertexbuffer_flush(graphics->sprite_buffer);
	gs_load_vertexbuffer(graphics->sprite_buffer);
	gs_load_indexbuffer(NULL);

	gs_draw(GS_TRISTRIP, 0, 0);
}