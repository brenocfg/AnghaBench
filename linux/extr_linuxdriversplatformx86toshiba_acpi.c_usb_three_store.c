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
struct toshiba_acpi_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct toshiba_acpi_dev* dev_get_drvdata (struct device*) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int toshiba_usb_three_set (struct toshiba_acpi_dev*,int) ; 

__attribute__((used)) static ssize_t usb_three_store(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	struct toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	int state;
	int ret;

	ret = kstrtoint(buf, 0, &state);
	if (ret)
		return ret;
	/*
	 * Check for USB 3 mode where:
	 * 0 - Disabled (Acts like a USB 2 port, saving power)
	 * 1 - Enabled
	 */
	if (state != 0 && state != 1)
		return -EINVAL;

	ret = toshiba_usb_three_set(toshiba, state);
	if (ret)
		return ret;

	pr_info("Reboot for changes to USB 3 to take effect");

	return count;
}