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
struct TYPE_2__ {int /*<<< orphan*/  groups; } ;
struct thermal_cooling_device {TYPE_1__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  cooling_device_attr_groups ; 
 int /*<<< orphan*/  cooling_device_stats_setup (struct thermal_cooling_device*) ; 

void thermal_cooling_device_setup_sysfs(struct thermal_cooling_device *cdev)
{
	cooling_device_stats_setup(cdev);
	cdev->device.groups = cooling_device_attr_groups;
}