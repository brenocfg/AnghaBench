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
typedef  int /*<<< orphan*/  obs_properties_t ;

/* Variables and functions */
 int /*<<< orphan*/  SETTING_LUMA_MAX ; 
 int /*<<< orphan*/  SETTING_LUMA_MAX_SMOOTH ; 
 int /*<<< orphan*/  SETTING_LUMA_MIN ; 
 int /*<<< orphan*/  SETTING_LUMA_MIN_SMOOTH ; 
 int /*<<< orphan*/  TEXT_LUMA_MAX ; 
 int /*<<< orphan*/  TEXT_LUMA_MAX_SMOOTH ; 
 int /*<<< orphan*/  TEXT_LUMA_MIN ; 
 int /*<<< orphan*/  TEXT_LUMA_MIN_SMOOTH ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 
 int /*<<< orphan*/  obs_properties_add_float_slider (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,double) ; 
 int /*<<< orphan*/ * obs_properties_create () ; 

__attribute__((used)) static obs_properties_t *luma_key_properties(void *data)
{
	obs_properties_t *props = obs_properties_create();

	obs_properties_add_float_slider(props, SETTING_LUMA_MAX, TEXT_LUMA_MAX,
					0, 1, 0.01);
	obs_properties_add_float_slider(props, SETTING_LUMA_MAX_SMOOTH,
					TEXT_LUMA_MAX_SMOOTH, 0, 1, 0.01);
	obs_properties_add_float_slider(props, SETTING_LUMA_MIN, TEXT_LUMA_MIN,
					0, 1, 0.01);
	obs_properties_add_float_slider(props, SETTING_LUMA_MIN_SMOOTH,
					TEXT_LUMA_MIN_SMOOTH, 0, 1, 0.01);

	UNUSED_PARAMETER(data);
	return props;
}