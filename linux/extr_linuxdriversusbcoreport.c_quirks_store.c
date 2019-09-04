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
struct usb_port {int /*<<< orphan*/  quirks; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ kstrtou32 (char const*,int,int /*<<< orphan*/ *) ; 
 struct usb_port* to_usb_port (struct device*) ; 

__attribute__((used)) static ssize_t quirks_store(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct usb_port *port_dev = to_usb_port(dev);
	u32 value;

	if (kstrtou32(buf, 16, &value))
		return -EINVAL;

	port_dev->quirks = value;
	return count;
}