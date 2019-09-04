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
struct thermal_zone_device {int trips; int temperature; TYPE_1__* ops; } ;
typedef  enum thermal_trip_type { ____Placeholder_thermal_trip_type } thermal_trip_type ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_trip_type ) (struct thermal_zone_device*,int,int*) ;int /*<<< orphan*/  (* get_trip_temp ) (struct thermal_zone_device*,int,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct thermal_zone_device*,int,int*) ; 
 int /*<<< orphan*/  stub2 (struct thermal_zone_device*,int,int*) ; 
 int /*<<< orphan*/  trace_thermal_zone_trip (struct thermal_zone_device*,int,int) ; 

__attribute__((used)) static int get_trip_level(struct thermal_zone_device *tz)
{
	int count = 0;
	int trip_temp;
	enum thermal_trip_type trip_type;

	if (tz->trips == 0 || !tz->ops->get_trip_temp)
		return 0;

	for (count = 0; count < tz->trips; count++) {
		tz->ops->get_trip_temp(tz, count, &trip_temp);
		if (tz->temperature < trip_temp)
			break;
	}

	/*
	 * count > 0 only if temperature is greater than first trip
	 * point, in which case, trip_point = count - 1
	 */
	if (count > 0) {
		tz->ops->get_trip_type(tz, count - 1, &trip_type);
		trace_thermal_zone_trip(tz, count - 1, trip_type);
	}

	return count;
}