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
struct db8500_thermal_zone {int cur_temp_pseudo; } ;

/* Variables and functions */

__attribute__((used)) static int db8500_sys_get_temp(struct thermal_zone_device *thermal, int *temp)
{
	struct db8500_thermal_zone *pzone = thermal->devdata;

	/*
	 * TODO: There is no PRCMU interface to get temperature data currently,
	 * so a pseudo temperature is returned , it works for thermal framework
	 * and this will be fixed when the PRCMU interface is available.
	 */
	*temp = pzone->cur_temp_pseudo;

	return 0;
}