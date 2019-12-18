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
struct crop_filter_data {int absolute; int left; int top; int right; int bottom; int abs_cx; int abs_cy; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_data_get_bool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void crop_filter_update(void *data, obs_data_t *settings)
{
	struct crop_filter_data *filter = data;

	filter->absolute = !obs_data_get_bool(settings, "relative");
	filter->left = (int)obs_data_get_int(settings, "left");
	filter->top = (int)obs_data_get_int(settings, "top");
	filter->right = (int)obs_data_get_int(settings, "right");
	filter->bottom = (int)obs_data_get_int(settings, "bottom");
	filter->abs_cx = (int)obs_data_get_int(settings, "cx");
	filter->abs_cy = (int)obs_data_get_int(settings, "cy");
}