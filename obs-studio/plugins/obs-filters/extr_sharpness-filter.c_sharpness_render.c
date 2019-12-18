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
struct sharpness_data {float texwidth; float texheight; float sharpness; int /*<<< orphan*/  effect; int /*<<< orphan*/  context; int /*<<< orphan*/  texture_height; int /*<<< orphan*/  texture_width; int /*<<< orphan*/  sharpness_param; } ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  GS_RGBA ; 
 int /*<<< orphan*/  OBS_ALLOW_DIRECT_RENDERING ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_effect_set_float (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  obs_filter_get_target (int /*<<< orphan*/ ) ; 
 scalar_t__ obs_source_get_height (int /*<<< orphan*/ ) ; 
 scalar_t__ obs_source_get_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_process_filter_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_process_filter_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sharpness_render(void *data, gs_effect_t *effect)
{
	struct sharpness_data *filter = data;

	if (!obs_source_process_filter_begin(filter->context, GS_RGBA,
					     OBS_ALLOW_DIRECT_RENDERING))
		return;

	filter->texwidth = (float)obs_source_get_width(
		obs_filter_get_target(filter->context));
	filter->texheight = (float)obs_source_get_height(
		obs_filter_get_target(filter->context));

	gs_effect_set_float(filter->sharpness_param, filter->sharpness);
	gs_effect_set_float(filter->texture_width, filter->texwidth);
	gs_effect_set_float(filter->texture_height, filter->texheight);

	obs_source_process_filter_end(filter->context, filter->effect, 0, 0);

	UNUSED_PARAMETER(effect);
}