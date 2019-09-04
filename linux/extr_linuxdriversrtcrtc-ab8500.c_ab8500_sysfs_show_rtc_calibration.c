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
typedef  int ssize_t ;

/* Variables and functions */
 int ab8500_rtc_get_calibration (struct device*,int*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t ab8500_sysfs_show_rtc_calibration(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int  retval = 0;
	int  calibration = 0;

	retval = ab8500_rtc_get_calibration(dev, &calibration);
	if (retval < 0) {
		dev_err(dev, "Failed to read RTC calibration attribute\n");
		sprintf(buf, "0\n");
		return retval;
	}

	return sprintf(buf, "%d\n", calibration);
}