#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thermal_zone_device {scalar_t__ trips; struct power_allocator_params* governor_data; TYPE_2__* tzp; TYPE_1__* ops; int /*<<< orphan*/  device; } ;
struct power_allocator_params {int allocated_tzp; int /*<<< orphan*/  trip_switch_on; int /*<<< orphan*/  trip_max_desired_temperature; } ;
struct TYPE_4__ {int /*<<< orphan*/  sustainable_power; } ;
struct TYPE_3__ {int (* get_trip_temp ) (struct thermal_zone_device*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  estimate_pid_constants (struct thermal_zone_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  get_governor_trips (struct thermal_zone_device*,struct power_allocator_params*) ; 
 int /*<<< orphan*/  kfree (struct power_allocator_params*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_pid_controller (struct power_allocator_params*) ; 
 int stub1 (struct thermal_zone_device*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int power_allocator_bind(struct thermal_zone_device *tz)
{
	int ret;
	struct power_allocator_params *params;
	int control_temp;

	params = kzalloc(sizeof(*params), GFP_KERNEL);
	if (!params)
		return -ENOMEM;

	if (!tz->tzp) {
		tz->tzp = kzalloc(sizeof(*tz->tzp), GFP_KERNEL);
		if (!tz->tzp) {
			ret = -ENOMEM;
			goto free_params;
		}

		params->allocated_tzp = true;
	}

	if (!tz->tzp->sustainable_power)
		dev_warn(&tz->device, "power_allocator: sustainable_power will be estimated\n");

	get_governor_trips(tz, params);

	if (tz->trips > 0) {
		ret = tz->ops->get_trip_temp(tz,
					params->trip_max_desired_temperature,
					&control_temp);
		if (!ret)
			estimate_pid_constants(tz, tz->tzp->sustainable_power,
					       params->trip_switch_on,
					       control_temp, false);
	}

	reset_pid_controller(params);

	tz->governor_data = params;

	return 0;

free_params:
	kfree(params);

	return ret;
}