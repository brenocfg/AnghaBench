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
struct thermal_zone_device {int last_temperature; int temperature; int /*<<< orphan*/  device; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EAGAIN ; 
 int THERMAL_TEMP_INVALID ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int thermal_zone_get_temp (struct thermal_zone_device*,int*) ; 
 int /*<<< orphan*/  trace_thermal_temperature (struct thermal_zone_device*) ; 

__attribute__((used)) static void update_temperature(struct thermal_zone_device *tz)
{
	int temp, ret;

	ret = thermal_zone_get_temp(tz, &temp);
	if (ret) {
		if (ret != -EAGAIN)
			dev_warn(&tz->device,
				 "failed to read out thermal zone (%d)\n",
				 ret);
		return;
	}

	mutex_lock(&tz->lock);
	tz->last_temperature = tz->temperature;
	tz->temperature = temp;
	mutex_unlock(&tz->lock);

	trace_thermal_temperature(tz);
	if (tz->last_temperature == THERMAL_TEMP_INVALID)
		dev_dbg(&tz->device, "last_temperature N/A, current_temperature=%d\n",
			tz->temperature);
	else
		dev_dbg(&tz->device, "last_temperature=%d, current_temperature=%d\n",
			tz->last_temperature, tz->temperature);
}