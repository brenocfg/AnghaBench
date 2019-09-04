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
struct asus_wmi {int asus_hwmon_pwm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_FAN_CTRL ; 
 int asus_wmi_get_devstate (struct asus_wmi*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static void asus_hwmon_pwm_show(struct asus_wmi *asus, int fan, int *value)
{
	int err;

	if (asus->asus_hwmon_pwm >= 0) {
		*value = asus->asus_hwmon_pwm;
		return;
	}

	err = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_FAN_CTRL, value);
	if (err < 0)
		return;

	*value &= 0xFF;

	if (*value == 1) /* Low Speed */
		*value = 85;
	else if (*value == 2)
		*value = 170;
	else if (*value == 3)
		*value = 255;
	else if (*value) {
		pr_err("Unknown fan speed %#x\n", *value);
		*value = -1;
	}
}