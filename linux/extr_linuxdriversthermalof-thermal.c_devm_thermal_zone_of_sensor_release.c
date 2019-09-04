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
struct thermal_zone_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  thermal_zone_of_sensor_unregister (struct device*,struct thermal_zone_device*) ; 

__attribute__((used)) static void devm_thermal_zone_of_sensor_release(struct device *dev, void *res)
{
	thermal_zone_of_sensor_unregister(dev,
					  *(struct thermal_zone_device **)res);
}