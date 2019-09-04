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
struct st_thermal_sensor {int /*<<< orphan*/  thermal_dev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct st_thermal_sensor* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  st_thermal_sensor_off (struct st_thermal_sensor*) ; 
 int /*<<< orphan*/  thermal_zone_device_unregister (int /*<<< orphan*/ ) ; 

int st_thermal_unregister(struct platform_device *pdev)
{
	struct st_thermal_sensor *sensor = platform_get_drvdata(pdev);

	st_thermal_sensor_off(sensor);
	thermal_zone_device_unregister(sensor->thermal_dev);

	return 0;
}