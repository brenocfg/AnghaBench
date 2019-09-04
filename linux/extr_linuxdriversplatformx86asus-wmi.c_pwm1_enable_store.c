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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct asus_wmi {int asus_hwmon_fan_manual_mode; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ASUS_FAN_CTRL_MANUAL ; 
 int asus_hwmon_fan_set_auto (struct asus_wmi*) ; 
 struct asus_wmi* dev_get_drvdata (struct device*) ; 
 int kstrtouint (char const*,int,int*) ; 

__attribute__((used)) static ssize_t pwm1_enable_store(struct device *dev,
						  struct device_attribute *attr,
						  const char *buf, size_t count)
{
	struct asus_wmi *asus = dev_get_drvdata(dev);
	int status = 0;
	int state;
	int ret;

	ret = kstrtouint(buf, 10, &state);

	if (ret)
		return ret;

	if (state == ASUS_FAN_CTRL_MANUAL)
		asus->asus_hwmon_fan_manual_mode = true;
	else
		status = asus_hwmon_fan_set_auto(asus);

	if (status)
		return status;

	return count;
}