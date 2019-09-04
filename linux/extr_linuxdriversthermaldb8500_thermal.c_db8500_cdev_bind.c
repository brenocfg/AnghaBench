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
struct thermal_cooling_device {int /*<<< orphan*/  type; int /*<<< orphan*/  device; TYPE_1__* ops; } ;
struct db8500_thsens_platform_data {int num_trips; int /*<<< orphan*/ * trip_points; } ;
struct db8500_thermal_zone {struct db8500_thsens_platform_data* trip_tab; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_max_state ) (struct thermal_cooling_device*,unsigned long*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  THERMAL_WEIGHT_DEFAULT ; 
 scalar_t__ db8500_thermal_match_cdev (struct thermal_cooling_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  stub1 (struct thermal_cooling_device*,unsigned long*) ; 
 int thermal_zone_bind_cooling_device (struct thermal_zone_device*,int,struct thermal_cooling_device*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int db8500_cdev_bind(struct thermal_zone_device *thermal,
		struct thermal_cooling_device *cdev)
{
	struct db8500_thermal_zone *pzone = thermal->devdata;
	struct db8500_thsens_platform_data *ptrips = pzone->trip_tab;
	unsigned long max_state, upper, lower;
	int i, ret = -EINVAL;

	cdev->ops->get_max_state(cdev, &max_state);

	for (i = 0; i < ptrips->num_trips; i++) {
		if (db8500_thermal_match_cdev(cdev, &ptrips->trip_points[i]))
			continue;

		upper = lower = i > max_state ? max_state : i;

		ret = thermal_zone_bind_cooling_device(thermal, i, cdev,
			upper, lower, THERMAL_WEIGHT_DEFAULT);

		dev_info(&cdev->device, "%s bind to %d: %d-%s\n", cdev->type,
			i, ret, ret ? "fail" : "succeed");
	}

	return ret;
}