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
typedef  scalar_t__ uint32_t ;
struct vec2 {int dummy; } ;
struct chroma_key_filter_data {int /*<<< orphan*/  effect; int /*<<< orphan*/  context; int /*<<< orphan*/  spill; int /*<<< orphan*/  spill_param; int /*<<< orphan*/  smoothness; int /*<<< orphan*/  smoothness_param; int /*<<< orphan*/  similarity; int /*<<< orphan*/  similarity_param; int /*<<< orphan*/  pixel_size_param; struct vec2 chroma; int /*<<< orphan*/  chroma_param; int /*<<< orphan*/  gamma; int /*<<< orphan*/  gamma_param; int /*<<< orphan*/  brightness; int /*<<< orphan*/  brightness_param; int /*<<< orphan*/  contrast; int /*<<< orphan*/  contrast_param; int /*<<< orphan*/  color; int /*<<< orphan*/  color_param; } ;
typedef  int /*<<< orphan*/  obs_source_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  GS_RGBA ; 
 int /*<<< orphan*/  OBS_ALLOW_DIRECT_RENDERING ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_effect_set_float (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_effect_set_vec2 (int /*<<< orphan*/ ,struct vec2*) ; 
 int /*<<< orphan*/  gs_effect_set_vec4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_filter_get_target (int /*<<< orphan*/ ) ; 
 scalar_t__ obs_source_get_base_height (int /*<<< orphan*/ *) ; 
 scalar_t__ obs_source_get_base_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_process_filter_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_process_filter_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec2_set (struct vec2*,float,float) ; 

__attribute__((used)) static void chroma_key_render(void *data, gs_effect_t *effect)
{
	struct chroma_key_filter_data *filter = data;
	obs_source_t *target = obs_filter_get_target(filter->context);
	uint32_t width = obs_source_get_base_width(target);
	uint32_t height = obs_source_get_base_height(target);
	struct vec2 pixel_size;

	if (!obs_source_process_filter_begin(filter->context, GS_RGBA,
					     OBS_ALLOW_DIRECT_RENDERING))
		return;

	vec2_set(&pixel_size, 1.0f / (float)width, 1.0f / (float)height);

	gs_effect_set_vec4(filter->color_param, &filter->color);
	gs_effect_set_float(filter->contrast_param, filter->contrast);
	gs_effect_set_float(filter->brightness_param, filter->brightness);
	gs_effect_set_float(filter->gamma_param, filter->gamma);
	gs_effect_set_vec2(filter->chroma_param, &filter->chroma);
	gs_effect_set_vec2(filter->pixel_size_param, &pixel_size);
	gs_effect_set_float(filter->similarity_param, filter->similarity);
	gs_effect_set_float(filter->smoothness_param, filter->smoothness);
	gs_effect_set_float(filter->spill_param, filter->spill);

	obs_source_process_filter_end(filter->context, filter->effect, 0, 0);

	UNUSED_PARAMETER(effect);
}