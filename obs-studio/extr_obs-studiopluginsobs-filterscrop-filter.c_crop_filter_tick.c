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
struct crop_filter_data {int /*<<< orphan*/  add_val; int /*<<< orphan*/  mul_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (float) ; 
 int /*<<< orphan*/  calc_crop_dimensions (struct crop_filter_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vec2_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void crop_filter_tick(void *data, float seconds)
{
	struct crop_filter_data *filter = data;

	vec2_zero(&filter->mul_val);
	vec2_zero(&filter->add_val);
	calc_crop_dimensions(filter, &filter->mul_val, &filter->add_val);

	UNUSED_PARAMETER(seconds);
}