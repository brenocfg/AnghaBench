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
typedef  int /*<<< orphan*/  u32 ;
struct toshiba_acpi_dev {int /*<<< orphan*/  usbsc_mode_base; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SCI_USB_CHARGE_ALTERNATE ; 
 int /*<<< orphan*/  SCI_USB_CHARGE_AUTO ; 
 int /*<<< orphan*/  SCI_USB_CHARGE_DISABLED ; 
 int /*<<< orphan*/  SCI_USB_CHARGE_TYPICAL ; 
 struct toshiba_acpi_dev* dev_get_drvdata (struct device*) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int toshiba_usb_sleep_charge_set (struct toshiba_acpi_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t usb_sleep_charge_store(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	struct toshiba_acpi_dev *toshiba = dev_get_drvdata(dev);
	int state;
	u32 mode;
	int ret;

	ret = kstrtoint(buf, 0, &state);
	if (ret)
		return ret;
	/*
	 * Check for supported values, where:
	 * 0 - Disabled
	 * 1 - Alternate (Non USB conformant devices that require more power)
	 * 2 - Auto (USB conformant devices)
	 * 3 - Typical
	 */
	if (state != 0 && state != 1 && state != 2 && state != 3)
		return -EINVAL;

	/* Set the USB charging mode to internal value */
	mode = toshiba->usbsc_mode_base;
	if (state == 0)
		mode |= SCI_USB_CHARGE_DISABLED;
	else if (state == 1)
		mode |= SCI_USB_CHARGE_ALTERNATE;
	else if (state == 2)
		mode |= SCI_USB_CHARGE_AUTO;
	else if (state == 3)
		mode |= SCI_USB_CHARGE_TYPICAL;

	ret = toshiba_usb_sleep_charge_set(toshiba, mode);
	if (ret)
		return ret;

	return count;
}