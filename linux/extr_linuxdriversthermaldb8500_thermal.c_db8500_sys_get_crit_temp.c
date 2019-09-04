#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thermal_zone_device {struct db8500_thermal_zone* devdata; } ;
struct db8500_thsens_platform_data {int num_trips; TYPE_1__* trip_points; } ;
struct db8500_thermal_zone {struct db8500_thsens_platform_data* trip_tab; } ;
struct TYPE_2__ {scalar_t__ type; int temp; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ THERMAL_TRIP_CRITICAL ; 

__attribute__((used)) static int db8500_sys_get_crit_temp(struct thermal_zone_device *thermal,
		int *temp)
{
	struct db8500_thermal_zone *pzone = thermal->devdata;
	struct db8500_thsens_platform_data *ptrips = pzone->trip_tab;
	int i;

	for (i = ptrips->num_trips - 1; i > 0; i--) {
		if (ptrips->trip_points[i].type == THERMAL_TRIP_CRITICAL) {
			*temp = ptrips->trip_points[i].temp;
			return 0;
		}
	}

	return -EINVAL;
}