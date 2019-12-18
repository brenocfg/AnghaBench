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

/* Variables and functions */
 int /*<<< orphan*/ * obs_properties_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_property_next (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  obs_property_set_enabled (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void v4l2_props_set_enabled(obs_properties_t *props,
				   obs_property_t *ignore, bool enable)
{
	if (!props)
		return;

	for (obs_property_t *prop = obs_properties_first(props); prop != NULL;
	     obs_property_next(&prop)) {
		if (prop == ignore)
			continue;

		obs_property_set_enabled(prop, enable);
	}
}