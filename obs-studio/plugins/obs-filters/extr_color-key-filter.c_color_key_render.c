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
struct color_key_filter_data {int /*<<< orphan*/  effect; int /*<<< orphan*/  context; int /*<<< orphan*/  smoothness; int /*<<< orphan*/  smoothness_param; int /*<<< orphan*/  similarity; int /*<<< orphan*/  similarity_param; int /*<<< orphan*/  key_color; int /*<<< orphan*/  key_color_param; int /*<<< orphan*/  gamma; int /*<<< orphan*/  gamma_param; int /*<<< orphan*/  brightness; int /*<<< orphan*/  brightness_param; int /*<<< orphan*/  contrast; int /*<<< orphan*/  contrast_param; int /*<<< orphan*/  color; int /*<<< orphan*/  color_param; } ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  GS_RGBA ; 
 int /*<<< orphan*/  OBS_ALLOW_DIRECT_RENDERING ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_effect_set_float (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_effect_set_vec4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_process_filter_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_process_filter_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void color_key_render(void *data, gs_effect_t *effect)
{
	struct color_key_filter_data *filter = data;

	if (!obs_source_process_filter_begin(filter->context, GS_RGBA,
					     OBS_ALLOW_DIRECT_RENDERING))
		return;

	gs_effect_set_vec4(filter->color_param, &filter->color);
	gs_effect_set_float(filter->contrast_param, filter->contrast);
	gs_effect_set_float(filter->brightness_param, filter->brightness);
	gs_effect_set_float(filter->gamma_param, filter->gamma);
	gs_effect_set_vec4(filter->key_color_param, &filter->key_color);
	gs_effect_set_float(filter->similarity_param, filter->similarity);
	gs_effect_set_float(filter->smoothness_param, filter->smoothness);

	obs_source_process_filter_end(filter->context, filter->effect, 0, 0);

	UNUSED_PARAMETER(effect);
}