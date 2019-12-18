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
typedef  scalar_t__ uint32_t ;
struct vec4 {int dummy; } ;
struct TYPE_2__ {scalar_t__ top; scalar_t__ left; } ;
struct obs_scene_item {int /*<<< orphan*/  source; scalar_t__ item_render; int /*<<< orphan*/  draw_transform; TYPE_1__ crop; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_CLEAR_COLOR ; 
 int /*<<< orphan*/  GS_DEBUG_COLOR_ITEM ; 
 int /*<<< orphan*/  GS_DEBUG_MARKER_BEGIN_FORMAT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GS_DEBUG_MARKER_END () ; 
 scalar_t__ calc_cx (struct obs_scene_item*,scalar_t__) ; 
 scalar_t__ calc_cy (struct obs_scene_item*,scalar_t__) ; 
 int /*<<< orphan*/  gs_clear (int /*<<< orphan*/ ,struct vec4*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_matrix_mul (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_matrix_pop () ; 
 int /*<<< orphan*/  gs_matrix_push () ; 
 int /*<<< orphan*/  gs_matrix_scale3f (float,float,float) ; 
 int /*<<< orphan*/  gs_matrix_translate3f (float,float,float) ; 
 int /*<<< orphan*/  gs_ortho (float,float,float,float,float,float) ; 
 scalar_t__ gs_texrender_begin (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gs_texrender_end (scalar_t__) ; 
 scalar_t__ obs_source_get_height (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_get_name (int /*<<< orphan*/ ) ; 
 scalar_t__ obs_source_get_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_video_render (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  render_item_texture (struct obs_scene_item*) ; 
 int /*<<< orphan*/  vec4_zero (struct vec4*) ; 

__attribute__((used)) static inline void render_item(struct obs_scene_item *item)
{
	GS_DEBUG_MARKER_BEGIN_FORMAT(GS_DEBUG_COLOR_ITEM, "Item: %s",
				     obs_source_get_name(item->source));

	if (item->item_render) {
		uint32_t width = obs_source_get_width(item->source);
		uint32_t height = obs_source_get_height(item->source);

		if (!width || !height) {
			goto cleanup;
		}

		uint32_t cx = calc_cx(item, width);
		uint32_t cy = calc_cy(item, height);

		if (cx && cy && gs_texrender_begin(item->item_render, cx, cy)) {
			float cx_scale = (float)width / (float)cx;
			float cy_scale = (float)height / (float)cy;
			struct vec4 clear_color;

			vec4_zero(&clear_color);
			gs_clear(GS_CLEAR_COLOR, &clear_color, 0.0f, 0);
			gs_ortho(0.0f, (float)width, 0.0f, (float)height,
				 -100.0f, 100.0f);

			gs_matrix_scale3f(cx_scale, cy_scale, 1.0f);
			gs_matrix_translate3f(-(float)item->crop.left,
					      -(float)item->crop.top, 0.0f);

			obs_source_video_render(item->source);

			gs_texrender_end(item->item_render);
		}
	}

	gs_matrix_push();
	gs_matrix_mul(&item->draw_transform);
	if (item->item_render) {
		render_item_texture(item);
	} else {
		obs_source_video_render(item->source);
	}
	gs_matrix_pop();

cleanup:
	GS_DEBUG_MARKER_END();
}