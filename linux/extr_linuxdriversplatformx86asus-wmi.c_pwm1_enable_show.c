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
struct asus_wmi {scalar_t__ asus_hwmon_fan_manual_mode; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ASUS_FAN_CTRL_AUTO ; 
 int ASUS_FAN_CTRL_MANUAL ; 
 struct asus_wmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t pwm1_enable_show(struct device *dev,
						 struct device_attribute *attr,
						 char *buf)
{
	struct asus_wmi *asus = dev_get_drvdata(dev);

	if (asus->asus_hwmon_fan_manual_mode)
		return sprintf(buf, "%d\n", ASUS_FAN_CTRL_MANUAL);

	return sprintf(buf, "%d\n", ASUS_FAN_CTRL_AUTO);
}