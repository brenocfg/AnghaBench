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
struct renesas_usb3 {int /*<<< orphan*/  driver; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct renesas_usb3* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ usb3_is_host (struct renesas_usb3*) ; 

__attribute__((used)) static ssize_t role_show(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct renesas_usb3 *usb3 = dev_get_drvdata(dev);

	if (!usb3->driver)
		return -ENODEV;

	return sprintf(buf, "%s\n", usb3_is_host(usb3) ? "host" : "peripheral");
}