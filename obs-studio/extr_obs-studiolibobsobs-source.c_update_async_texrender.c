#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  float uint32_t ;
struct obs_source_frame {int /*<<< orphan*/  color_range_max; int /*<<< orphan*/  color_range_min; int /*<<< orphan*/  full_range; int /*<<< orphan*/  color_matrix; int /*<<< orphan*/  format; } ;
struct obs_source {float async_width; float async_height; scalar_t__* async_plane_offset; scalar_t__ async_convert_width; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;
typedef  int /*<<< orphan*/  gs_texrender_t ;
typedef  int /*<<< orphan*/  gs_technique_t ;
typedef  int /*<<< orphan*/  gs_eparam_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;
struct TYPE_3__ {int /*<<< orphan*/ * conversion_effect; } ;
struct TYPE_4__ {TYPE_1__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_DEBUG_COLOR_CONVERT_FORMAT ; 
 int /*<<< orphan*/  GS_DEBUG_MARKER_BEGIN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GS_DEBUG_MARKER_END () ; 
 int /*<<< orphan*/  gs_draw_sprite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float,float) ; 
 int /*<<< orphan*/ * gs_effect_get_param_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * gs_effect_get_technique (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  gs_effect_set_texture (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_effect_set_val (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gs_ortho (float,float,float,float,float,float) ; 
 int /*<<< orphan*/  gs_technique_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_technique_begin_pass (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_technique_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_technique_end_pass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_texrender_begin (int /*<<< orphan*/ *,float,float) ; 
 int /*<<< orphan*/  gs_texrender_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_texrender_reset (int /*<<< orphan*/ *) ; 
 TYPE_2__* obs ; 
 char* select_conversion_technique (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_eparam (int /*<<< orphan*/ *,char*,float) ; 
 int /*<<< orphan*/  set_eparami (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  upload_raw_frame (int /*<<< orphan*/ *,struct obs_source_frame const*) ; 

__attribute__((used)) static bool update_async_texrender(struct obs_source *source,
		const struct obs_source_frame *frame,
		gs_texture_t *tex, gs_texrender_t *texrender)
{
	GS_DEBUG_MARKER_BEGIN(GS_DEBUG_COLOR_CONVERT_FORMAT, "Convert Format");

	gs_texrender_reset(texrender);

	upload_raw_frame(tex, frame);

	uint32_t cx = source->async_width;
	uint32_t cy = source->async_height;

	float convert_width  = (float)source->async_convert_width;

	gs_effect_t *conv = obs->video.conversion_effect;
	const char *tech_name = select_conversion_technique(frame->format,
			frame->full_range);
	gs_technique_t *tech = gs_effect_get_technique(conv, tech_name);

	if (!gs_texrender_begin(texrender, cx, cy)) {
		GS_DEBUG_MARKER_END();
		return false;
	}

	gs_technique_begin(tech);
	gs_technique_begin_pass(tech, 0);

	gs_effect_set_texture(gs_effect_get_param_by_name(conv, "image"), tex);
	set_eparam(conv, "width",  (float)cx);
	set_eparam(conv, "height", (float)cy);
	set_eparam(conv, "width_d2",  cx * 0.5f);
	set_eparam(conv, "width_d2_i",  1.0f / (cx * 0.5f));
	set_eparam(conv, "input_width_i_d2",  (1.0f / convert_width)  * 0.5f);

	set_eparami(conv, "int_width", (int)cx);
	set_eparami(conv, "int_input_width", (int)source->async_convert_width);
	set_eparami(conv, "int_u_plane_offset",
			(int)source->async_plane_offset[0]);
	set_eparami(conv, "int_v_plane_offset",
			(int)source->async_plane_offset[1]);

	gs_effect_set_val(gs_effect_get_param_by_name(conv, "color_matrix"),
			frame->color_matrix, sizeof(float) * 16);
	if (!frame->full_range) {
		gs_eparam_t *min_param = gs_effect_get_param_by_name(
				conv, "color_range_min");
		gs_effect_set_val(min_param, frame->color_range_min,
				sizeof(float) * 3);
		gs_eparam_t *max_param = gs_effect_get_param_by_name(
				conv, "color_range_max");
		gs_effect_set_val(max_param, frame->color_range_max,
				sizeof(float) * 3);
	}

	gs_ortho(0.f, (float)cx, 0.f, (float)cy, -100.f, 100.f);

	gs_draw_sprite(tex, 0, cx, cy);

	gs_technique_end_pass(tech);
	gs_technique_end(tech);

	gs_texrender_end(texrender);

	GS_DEBUG_MARKER_END();
	return true;
}