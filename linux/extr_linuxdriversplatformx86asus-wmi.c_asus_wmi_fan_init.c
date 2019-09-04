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
struct asus_wmi {int asus_hwmon_pwm; int asus_hwmon_num_fans; int asus_hwmon_fan_manual_mode; } ;

/* Variables and functions */
 int ENXIO ; 
 int asus_hwmon_get_fan_number (struct asus_wmi*,int*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static int asus_wmi_fan_init(struct asus_wmi *asus)
{
	int status;

	asus->asus_hwmon_pwm = -1;
	asus->asus_hwmon_num_fans = -1;
	asus->asus_hwmon_fan_manual_mode = false;

	status = asus_hwmon_get_fan_number(asus, &asus->asus_hwmon_num_fans);
	if (status) {
		asus->asus_hwmon_num_fans = 0;
		pr_warn("Could not determine number of fans: %d\n", status);
		return -ENXIO;
	}

	pr_info("Number of fans: %d\n", asus->asus_hwmon_num_fans);
	return 0;
}