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
struct thermal_zone_device {int temperature; int /*<<< orphan*/  device; TYPE_1__* ops; } ;
typedef  enum thermal_trip_type { ____Placeholder_thermal_trip_type } thermal_trip_type ;
struct TYPE_2__ {int /*<<< orphan*/  (* notify ) (struct thermal_zone_device*,int,int) ;int /*<<< orphan*/  (* get_trip_temp ) (struct thermal_zone_device*,int,int*) ;} ;

/* Variables and functions */
 int THERMAL_TRIP_CRITICAL ; 
 int /*<<< orphan*/  dev_emerg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  orderly_poweroff (int) ; 
 int power_off_triggered ; 
 int /*<<< orphan*/  poweroff_lock ; 
 int /*<<< orphan*/  stub1 (struct thermal_zone_device*,int,int*) ; 
 int /*<<< orphan*/  stub2 (struct thermal_zone_device*,int,int) ; 
 int /*<<< orphan*/  thermal_emergency_poweroff () ; 
 int /*<<< orphan*/  trace_thermal_zone_trip (struct thermal_zone_device*,int,int) ; 

__attribute__((used)) static void handle_critical_trips(struct thermal_zone_device *tz,
				  int trip, enum thermal_trip_type trip_type)
{
	int trip_temp;

	tz->ops->get_trip_temp(tz, trip, &trip_temp);

	/* If we have not crossed the trip_temp, we do not care. */
	if (trip_temp <= 0 || tz->temperature < trip_temp)
		return;

	trace_thermal_zone_trip(tz, trip, trip_type);

	if (tz->ops->notify)
		tz->ops->notify(tz, trip, trip_type);

	if (trip_type == THERMAL_TRIP_CRITICAL) {
		dev_emerg(&tz->device,
			  "critical temperature reached (%d C), shutting down\n",
			  tz->temperature / 1000);
		mutex_lock(&poweroff_lock);
		if (!power_off_triggered) {
			/*
			 * Queue a backup emergency shutdown in the event of
			 * orderly_poweroff failure
			 */
			thermal_emergency_poweroff();
			orderly_poweroff(true);
			power_off_triggered = true;
		}
		mutex_unlock(&poweroff_lock);
	}
}