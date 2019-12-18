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
struct luma_key_filter_data {float luma_max; float luma_min; float luma_max_smooth; float luma_min_smooth; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  SETTING_LUMA_MAX ; 
 int /*<<< orphan*/  SETTING_LUMA_MAX_SMOOTH ; 
 int /*<<< orphan*/  SETTING_LUMA_MIN ; 
 int /*<<< orphan*/  SETTING_LUMA_MIN_SMOOTH ; 
 double obs_data_get_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void luma_key_update(void *data, obs_data_t *settings)
{
	struct luma_key_filter_data *filter = data;

	double lumaMax = obs_data_get_double(settings, SETTING_LUMA_MAX);
	double lumaMin = obs_data_get_double(settings, SETTING_LUMA_MIN);
	double lumaMaxSmooth =
		obs_data_get_double(settings, SETTING_LUMA_MAX_SMOOTH);
	double lumaMinSmooth =
		obs_data_get_double(settings, SETTING_LUMA_MIN_SMOOTH);

	filter->luma_max = (float)lumaMax;
	filter->luma_min = (float)lumaMin;
	filter->luma_max_smooth = (float)lumaMaxSmooth;
	filter->luma_min_smooth = (float)lumaMinSmooth;
}