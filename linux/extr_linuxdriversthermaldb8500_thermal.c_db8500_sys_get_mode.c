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
struct db8500_thermal_zone {int mode; int /*<<< orphan*/  th_lock; } ;
typedef  enum thermal_device_mode { ____Placeholder_thermal_device_mode } thermal_device_mode ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int db8500_sys_get_mode(struct thermal_zone_device *thermal,
		enum thermal_device_mode *mode)
{
	struct db8500_thermal_zone *pzone = thermal->devdata;

	mutex_lock(&pzone->th_lock);
	*mode = pzone->mode;
	mutex_unlock(&pzone->th_lock);

	return 0;
}