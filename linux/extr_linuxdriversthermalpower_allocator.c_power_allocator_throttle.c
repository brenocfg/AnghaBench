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
struct thermal_zone_device {int temperature; int passive; int /*<<< orphan*/  device; TYPE_1__* ops; struct power_allocator_params* governor_data; } ;
struct power_allocator_params {int trip_max_desired_temperature; int trip_switch_on; } ;
struct TYPE_2__ {int (* get_trip_temp ) (struct thermal_zone_device*,int,int*) ;} ;

/* Variables and functions */
 int allocate_power (struct thermal_zone_device*,int) ; 
 int /*<<< orphan*/  allow_maximum_power (struct thermal_zone_device*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  reset_pid_controller (struct power_allocator_params*) ; 
 int stub1 (struct thermal_zone_device*,int,int*) ; 
 int stub2 (struct thermal_zone_device*,int,int*) ; 

__attribute__((used)) static int power_allocator_throttle(struct thermal_zone_device *tz, int trip)
{
	int ret;
	int switch_on_temp, control_temp;
	struct power_allocator_params *params = tz->governor_data;

	/*
	 * We get called for every trip point but we only need to do
	 * our calculations once
	 */
	if (trip != params->trip_max_desired_temperature)
		return 0;

	ret = tz->ops->get_trip_temp(tz, params->trip_switch_on,
				     &switch_on_temp);
	if (!ret && (tz->temperature < switch_on_temp)) {
		tz->passive = 0;
		reset_pid_controller(params);
		allow_maximum_power(tz);
		return 0;
	}

	tz->passive = 1;

	ret = tz->ops->get_trip_temp(tz, params->trip_max_desired_temperature,
				&control_temp);
	if (ret) {
		dev_warn(&tz->device,
			 "Failed to get the maximum desired temperature: %d\n",
			 ret);
		return ret;
	}

	return allocate_power(tz, control_temp);
}