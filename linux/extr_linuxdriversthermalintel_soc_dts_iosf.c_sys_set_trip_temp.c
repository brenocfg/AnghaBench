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
struct thermal_zone_device {struct intel_soc_dts_sensor_entry* devdata; } ;
struct intel_soc_dts_sensors {int tj_max; int /*<<< orphan*/  dts_update_lock; } ;
struct intel_soc_dts_sensor_entry {int /*<<< orphan*/ * trip_types; struct intel_soc_dts_sensors* sensors; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int update_trip_temp (struct intel_soc_dts_sensor_entry*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sys_set_trip_temp(struct thermal_zone_device *tzd, int trip,
			     int temp)
{
	struct intel_soc_dts_sensor_entry *dts = tzd->devdata;
	struct intel_soc_dts_sensors *sensors = dts->sensors;
	int status;

	if (temp > sensors->tj_max)
		return -EINVAL;

	mutex_lock(&sensors->dts_update_lock);
	status = update_trip_temp(tzd->devdata, trip, temp,
				  dts->trip_types[trip]);
	mutex_unlock(&sensors->dts_update_lock);

	return status;
}