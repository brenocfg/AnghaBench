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
struct device {int dummy; } ;
struct asus_wmi {scalar_t__ asus_hwmon_fan_manual_mode; } ;

/* Variables and functions */
 int ENXIO ; 
 int asus_hwmon_agfn_fan_speed_read (struct asus_wmi*,int,int*) ; 
 struct asus_wmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static int asus_hwmon_fan_rpm_show(struct device *dev, int fan)
{
	struct asus_wmi *asus = dev_get_drvdata(dev);
	int value;
	int ret;

	/* no speed readable on manual mode */
	if (asus->asus_hwmon_fan_manual_mode)
		return -ENXIO;

	ret = asus_hwmon_agfn_fan_speed_read(asus, fan+1, &value);
	if (ret) {
		pr_warn("reading fan speed failed: %d\n", ret);
		return -ENXIO;
	}

	return value;
}