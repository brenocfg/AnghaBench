#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct vec2 {float member_0; float member_1; } ;
struct TYPE_5__ {float x; float y; } ;
struct obs_scene_item {int scale_filter; TYPE_2__ output_scale; int /*<<< orphan*/  item_render; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;
typedef  int /*<<< orphan*/  gs_eparam_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;
typedef  enum obs_scale_type { ____Placeholder_obs_scale_type } obs_scale_type ;
struct TYPE_4__ {int /*<<< orphan*/ * area_effect; int /*<<< orphan*/ * lanczos_effect; int /*<<< orphan*/ * bicubic_effect; int /*<<< orphan*/ * bilinear_lowres_effect; int /*<<< orphan*/  point_sampler; int /*<<< orphan*/ * default_effect; } ;
struct TYPE_6__ {TYPE_1__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPSILON ; 
 int /*<<< orphan*/  GS_BLEND_INVSRCALPHA ; 
 int /*<<< orphan*/  GS_BLEND_ONE ; 
 int /*<<< orphan*/  GS_DEBUG_COLOR_ITEM_TEXTURE ; 
 int /*<<< orphan*/  GS_DEBUG_MARKER_BEGIN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GS_DEBUG_MARKER_END () ; 
 int OBS_SCALE_AREA ; 
 int OBS_SCALE_BICUBIC ; 
 int OBS_SCALE_DISABLE ; 
 int OBS_SCALE_LANCZOS ; 
 int OBS_SCALE_POINT ; 
 int /*<<< orphan*/  close_float (float,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_blend_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_blend_state_pop () ; 
 int /*<<< orphan*/  gs_blend_state_push () ; 
 int /*<<< orphan*/ * gs_effect_get_param_by_name (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ gs_effect_loop (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  gs_effect_set_next_sampler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_effect_set_vec2 (int /*<<< orphan*/ *,struct vec2*) ; 
 int /*<<< orphan*/ * gs_texrender_get_texture (int /*<<< orphan*/ ) ; 
 scalar_t__ gs_texture_get_height (int /*<<< orphan*/ *) ; 
 scalar_t__ gs_texture_get_width (int /*<<< orphan*/ *) ; 
 TYPE_3__* obs ; 
 int /*<<< orphan*/  obs_source_draw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void render_item_texture(struct obs_scene_item *item)
{
	gs_texture_t *tex = gs_texrender_get_texture(item->item_render);
	if (!tex) {
		return;
	}

	GS_DEBUG_MARKER_BEGIN(GS_DEBUG_COLOR_ITEM_TEXTURE,
			      "render_item_texture");

	gs_effect_t *effect = obs->video.default_effect;
	enum obs_scale_type type = item->scale_filter;
	uint32_t cx = gs_texture_get_width(tex);
	uint32_t cy = gs_texture_get_height(tex);
	const char *tech = "Draw";

	if (type != OBS_SCALE_DISABLE) {
		if (type == OBS_SCALE_POINT) {
			gs_eparam_t *image =
				gs_effect_get_param_by_name(effect, "image");
			gs_effect_set_next_sampler(image,
						   obs->video.point_sampler);

		} else if (!close_float(item->output_scale.x, 1.0f, EPSILON) ||
			   !close_float(item->output_scale.y, 1.0f, EPSILON)) {
			gs_eparam_t *scale_param;
			gs_eparam_t *scale_i_param;

			if (item->output_scale.x < 0.5f ||
			    item->output_scale.y < 0.5f) {
				effect = obs->video.bilinear_lowres_effect;
			} else if (type == OBS_SCALE_BICUBIC) {
				effect = obs->video.bicubic_effect;
			} else if (type == OBS_SCALE_LANCZOS) {
				effect = obs->video.lanczos_effect;
			} else if (type == OBS_SCALE_AREA) {
				effect = obs->video.area_effect;
				if ((item->output_scale.x >= 1.0f) &&
				    (item->output_scale.y >= 1.0f))
					tech = "DrawUpscale";
			}

			scale_param = gs_effect_get_param_by_name(
				effect, "base_dimension");
			if (scale_param) {
				struct vec2 base_res = {(float)cx, (float)cy};

				gs_effect_set_vec2(scale_param, &base_res);
			}

			scale_i_param = gs_effect_get_param_by_name(
				effect, "base_dimension_i");
			if (scale_i_param) {
				struct vec2 base_res_i = {1.0f / (float)cx,
							  1.0f / (float)cy};

				gs_effect_set_vec2(scale_i_param, &base_res_i);
			}
		}
	}

	gs_blend_state_push();
	gs_blend_function(GS_BLEND_ONE, GS_BLEND_INVSRCALPHA);

	while (gs_effect_loop(effect, tech))
		obs_source_draw(tex, 0, 0, 0, 0, 0);

	gs_blend_state_pop();

	GS_DEBUG_MARKER_END();
}