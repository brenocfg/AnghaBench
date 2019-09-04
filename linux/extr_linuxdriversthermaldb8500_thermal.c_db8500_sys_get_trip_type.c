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
typedef  enum thermal_trip_type { ____Placeholder_thermal_trip_type } thermal_trip_type ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int db8500_sys_get_trip_type(struct thermal_zone_device *thermal,
		int trip, enum thermal_trip_type *type)
{
	struct db8500_thermal_zone *pzone = thermal->devdata;
	struct db8500_thsens_platform_data *ptrips = pzone->trip_tab;

	if (trip >= ptrips->num_trips)
		return -EINVAL;

	*type = ptrips->trip_points[trip].type;

	return 0;
}