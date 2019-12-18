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
struct vec2 {float x; float y; } ;
struct crop_filter_data {int width; int abs_cx; int height; int abs_cy; int left; int right; int top; int bottom; scalar_t__ absolute; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/ * obs_filter_get_target (int /*<<< orphan*/ ) ; 
 scalar_t__ obs_source_get_base_height (int /*<<< orphan*/ *) ; 
 scalar_t__ obs_source_get_base_width (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void calc_crop_dimensions(struct crop_filter_data *filter,
				 struct vec2 *mul_val, struct vec2 *add_val)
{
	obs_source_t *target = obs_filter_get_target(filter->context);
	uint32_t width;
	uint32_t height;

	if (!target) {
		width = 0;
		height = 0;
		return;
	} else {
		width = obs_source_get_base_width(target);
		height = obs_source_get_base_height(target);
	}

	if (filter->absolute) {
		filter->width = filter->abs_cx;
		filter->height = filter->abs_cy;
	} else {
		filter->width = (int)width - filter->left - filter->right;
		filter->height = (int)height - filter->top - filter->bottom;
	}

	if (filter->width < 1)
		filter->width = 1;
	if (filter->height < 1)
		filter->height = 1;

	if (width && filter->width) {
		mul_val->x = (float)filter->width / (float)width;
		add_val->x = (float)filter->left / (float)width;
	}

	if (height && filter->height) {
		mul_val->y = (float)filter->height / (float)height;
		add_val->y = (float)filter->top / (float)height;
	}
}