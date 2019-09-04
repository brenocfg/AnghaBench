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
struct thermal_cooling_device {int /*<<< orphan*/  type; } ;
struct db8500_trip_point {int /*<<< orphan*/ * cdev_name; } ;

/* Variables and functions */
 int COOLING_DEV_MAX ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int db8500_thermal_match_cdev(struct thermal_cooling_device *cdev,
		struct db8500_trip_point *trip_point)
{
	int i;

	if (!strlen(cdev->type))
		return -EINVAL;

	for (i = 0; i < COOLING_DEV_MAX; i++) {
		if (!strcmp(trip_point->cdev_name[i], cdev->type))
			return 0;
	}

	return -ENODEV;
}