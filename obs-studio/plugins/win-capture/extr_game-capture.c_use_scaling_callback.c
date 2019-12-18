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
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  int /*<<< orphan*/  obs_properties_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  SETTING_FORCE_SCALING ; 
 int /*<<< orphan*/  SETTING_SCALE_RES ; 
 int obs_data_get_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * obs_properties_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_property_set_enabled (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool use_scaling_callback(obs_properties_t *ppts, obs_property_t *p,
				 obs_data_t *settings)
{
	bool use_scale = obs_data_get_bool(settings, SETTING_FORCE_SCALING);

	p = obs_properties_get(ppts, SETTING_SCALE_RES);
	obs_property_set_enabled(p, use_scale);
	return true;
}