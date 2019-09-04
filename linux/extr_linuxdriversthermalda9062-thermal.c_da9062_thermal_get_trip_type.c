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
struct thermal_zone_device {struct da9062_thermal* devdata; } ;
struct da9062_thermal {int /*<<< orphan*/  dev; } ;
typedef  enum thermal_trip_type { ____Placeholder_thermal_trip_type } thermal_trip_type ;

/* Variables and functions */
 int EINVAL ; 
 int THERMAL_TRIP_HOT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int da9062_thermal_get_trip_type(struct thermal_zone_device *z,
					int trip,
					enum thermal_trip_type *type)
{
	struct da9062_thermal *thermal = z->devdata;

	switch (trip) {
	case 0:
		*type = THERMAL_TRIP_HOT;
		break;
	default:
		dev_err(thermal->dev,
			"Driver does not support more than 1 trip-wire\n");
		return -EINVAL;
	}

	return 0;
}