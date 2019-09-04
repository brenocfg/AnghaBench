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
struct thermal_zone_device {struct db8500_thermal_zone* devdata; } ;
struct thermal_cooling_device {int /*<<< orphan*/  type; int /*<<< orphan*/  device; } ;
struct db8500_thsens_platform_data {int num_trips; int /*<<< orphan*/ * trip_points; } ;
struct db8500_thermal_zone {struct db8500_thsens_platform_data* trip_tab; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ db8500_thermal_match_cdev (struct thermal_cooling_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,char*) ; 
 int thermal_zone_unbind_cooling_device (struct thermal_zone_device*,int,struct thermal_cooling_device*) ; 

__attribute__((used)) static int db8500_cdev_unbind(struct thermal_zone_device *thermal,
		struct thermal_cooling_device *cdev)
{
	struct db8500_thermal_zone *pzone = thermal->devdata;
	struct db8500_thsens_platform_data *ptrips = pzone->trip_tab;
	int i, ret = -EINVAL;

	for (i = 0; i < ptrips->num_trips; i++) {
		if (db8500_thermal_match_cdev(cdev, &ptrips->trip_points[i]))
			continue;

		ret = thermal_zone_unbind_cooling_device(thermal, i, cdev);

		dev_info(&cdev->device, "%s unbind from %d: %s\n", cdev->type,
			i, ret ? "fail" : "succeed");
	}

	return ret;
}