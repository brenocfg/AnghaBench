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
struct wusb_dev {int /*<<< orphan*/  cdid; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ ENODEV ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ ckhdid_printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  to_usb_device (struct device*) ; 
 struct wusb_dev* wusb_dev_get_by_usb_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wusb_dev_put (struct wusb_dev*) ; 

__attribute__((used)) static ssize_t wusb_cdid_show(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	ssize_t result;
	struct wusb_dev *wusb_dev;

	wusb_dev = wusb_dev_get_by_usb_dev(to_usb_device(dev));
	if (wusb_dev == NULL)
		return -ENODEV;
	result = ckhdid_printf(buf, PAGE_SIZE, &wusb_dev->cdid);
	strcat(buf, "\n");
	wusb_dev_put(wusb_dev);
	return result + 1;
}