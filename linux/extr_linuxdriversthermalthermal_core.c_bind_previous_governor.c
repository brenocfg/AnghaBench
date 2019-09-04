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
struct thermal_zone_device {TYPE_1__* governor; int /*<<< orphan*/  type; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; scalar_t__ (* bind_to_tz ) (struct thermal_zone_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct thermal_zone_device*) ; 

__attribute__((used)) static void bind_previous_governor(struct thermal_zone_device *tz,
				   const char *failed_gov_name)
{
	if (tz->governor && tz->governor->bind_to_tz) {
		if (tz->governor->bind_to_tz(tz)) {
			dev_err(&tz->device,
				"governor %s failed to bind and the previous one (%s) failed to bind again, thermal zone %s has no governor\n",
				failed_gov_name, tz->governor->name, tz->type);
			tz->governor = NULL;
		}
	}
}