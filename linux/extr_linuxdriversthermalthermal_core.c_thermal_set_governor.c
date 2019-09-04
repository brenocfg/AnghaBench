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
struct thermal_zone_device {struct thermal_governor* governor; } ;
struct thermal_governor {int (* bind_to_tz ) (struct thermal_zone_device*) ;int /*<<< orphan*/  name; int /*<<< orphan*/  (* unbind_from_tz ) (struct thermal_zone_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  bind_previous_governor (struct thermal_zone_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct thermal_zone_device*) ; 
 int stub2 (struct thermal_zone_device*) ; 

__attribute__((used)) static int thermal_set_governor(struct thermal_zone_device *tz,
				struct thermal_governor *new_gov)
{
	int ret = 0;

	if (tz->governor && tz->governor->unbind_from_tz)
		tz->governor->unbind_from_tz(tz);

	if (new_gov && new_gov->bind_to_tz) {
		ret = new_gov->bind_to_tz(tz);
		if (ret) {
			bind_previous_governor(tz, new_gov->name);

			return ret;
		}
	}

	tz->governor = new_gov;

	return ret;
}