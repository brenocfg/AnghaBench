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
struct thermal_zone_device {struct power_allocator_params* governor_data; struct power_allocator_params* tzp; int /*<<< orphan*/  id; int /*<<< orphan*/  device; } ;
struct power_allocator_params {scalar_t__ allocated_tzp; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct power_allocator_params*) ; 

__attribute__((used)) static void power_allocator_unbind(struct thermal_zone_device *tz)
{
	struct power_allocator_params *params = tz->governor_data;

	dev_dbg(&tz->device, "Unbinding from thermal zone %d\n", tz->id);

	if (params->allocated_tzp) {
		kfree(tz->tzp);
		tz->tzp = NULL;
	}

	kfree(tz->governor_data);
	tz->governor_data = NULL;
}