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
struct luma_key_filter_data {int /*<<< orphan*/  effect; int /*<<< orphan*/  context; int /*<<< orphan*/  luma_min_smooth; int /*<<< orphan*/  luma_min_smooth_param; int /*<<< orphan*/  luma_max_smooth; int /*<<< orphan*/  luma_max_smooth_param; int /*<<< orphan*/  luma_min; int /*<<< orphan*/  luma_min_param; int /*<<< orphan*/  luma_max; int /*<<< orphan*/  luma_max_param; } ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  GS_RGBA ; 
 int /*<<< orphan*/  OBS_ALLOW_DIRECT_RENDERING ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_effect_set_float (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_process_filter_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_process_filter_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void luma_key_render(void *data, gs_effect_t *effect)
{
	struct luma_key_filter_data *filter = data;

	if (!obs_source_process_filter_begin(filter->context, GS_RGBA,
					     OBS_ALLOW_DIRECT_RENDERING))
		return;

	gs_effect_set_float(filter->luma_max_param, filter->luma_max);
	gs_effect_set_float(filter->luma_min_param, filter->luma_min);
	gs_effect_set_float(filter->luma_max_smooth_param,
			    filter->luma_max_smooth);
	gs_effect_set_float(filter->luma_min_smooth_param,
			    filter->luma_min_smooth);

	obs_source_process_filter_end(filter->context, filter->effect, 0, 0);

	UNUSED_PARAMETER(effect);
}