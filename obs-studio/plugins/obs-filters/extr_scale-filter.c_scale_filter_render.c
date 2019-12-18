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
struct scale_filter_data {scalar_t__ sampling; int /*<<< orphan*/  cy_out; int /*<<< orphan*/  cx_out; int /*<<< orphan*/  effect; int /*<<< orphan*/  context; int /*<<< orphan*/  point_sampler; int /*<<< orphan*/  image_param; scalar_t__ undistort_factor; scalar_t__ undistort_factor_param; int /*<<< orphan*/  dimension_i; scalar_t__ dimension_i_param; int /*<<< orphan*/  dimension; scalar_t__ dimension_param; int /*<<< orphan*/  target_valid; int /*<<< orphan*/  valid; scalar_t__ upscale; scalar_t__ undistort; } ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  GS_RGBA ; 
 int /*<<< orphan*/  OBS_NO_DIRECT_RENDERING ; 
 scalar_t__ OBS_SCALE_POINT ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_effect_set_float (scalar_t__,float) ; 
 int /*<<< orphan*/  gs_effect_set_next_sampler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_effect_set_vec2 (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_process_filter_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_process_filter_tech_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  obs_source_skip_video_filter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scale_filter_render(void *data, gs_effect_t *effect)
{
	struct scale_filter_data *filter = data;
	const char *technique =
		filter->undistort ? "DrawUndistort"
				  : (filter->upscale ? "DrawUpscale" : "Draw");

	if (!filter->valid || !filter->target_valid) {
		obs_source_skip_video_filter(filter->context);
		return;
	}

	if (!obs_source_process_filter_begin(filter->context, GS_RGBA,
					     OBS_NO_DIRECT_RENDERING))
		return;

	if (filter->dimension_param)
		gs_effect_set_vec2(filter->dimension_param, &filter->dimension);

	if (filter->dimension_i_param)
		gs_effect_set_vec2(filter->dimension_i_param,
				   &filter->dimension_i);

	if (filter->undistort_factor_param)
		gs_effect_set_float(filter->undistort_factor_param,
				    (float)filter->undistort_factor);

	if (filter->sampling == OBS_SCALE_POINT)
		gs_effect_set_next_sampler(filter->image_param,
					   filter->point_sampler);

	obs_source_process_filter_tech_end(filter->context, filter->effect,
					   filter->cx_out, filter->cy_out,
					   technique);

	UNUSED_PARAMETER(effect);
}