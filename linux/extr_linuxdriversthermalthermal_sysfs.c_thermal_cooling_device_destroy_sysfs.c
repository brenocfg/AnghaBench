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
struct thermal_cooling_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cooling_device_stats_destroy (struct thermal_cooling_device*) ; 

void thermal_cooling_device_destroy_sysfs(struct thermal_cooling_device *cdev)
{
	cooling_device_stats_destroy(cdev);
}