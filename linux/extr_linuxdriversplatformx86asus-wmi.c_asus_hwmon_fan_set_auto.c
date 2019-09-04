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
struct asus_wmi {int asus_hwmon_fan_manual_mode; } ;

/* Variables and functions */
 int ENXIO ; 
 int asus_hwmon_agfn_fan_speed_write (struct asus_wmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asus_hwmon_fan_set_auto(struct asus_wmi *asus)
{
	int status;

	status = asus_hwmon_agfn_fan_speed_write(asus, 0, NULL);
	if (status)
		return -ENXIO;

	asus->asus_hwmon_fan_manual_mode = false;

	return 0;
}