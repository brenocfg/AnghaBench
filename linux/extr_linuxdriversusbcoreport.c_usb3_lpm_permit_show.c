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
struct usb_port {scalar_t__ usb3_lpm_u2_permit; scalar_t__ usb3_lpm_u1_permit; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 struct usb_port* to_usb_port (struct device*) ; 

__attribute__((used)) static ssize_t usb3_lpm_permit_show(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	struct usb_port *port_dev = to_usb_port(dev);
	const char *p;

	if (port_dev->usb3_lpm_u1_permit) {
		if (port_dev->usb3_lpm_u2_permit)
			p = "u1_u2";
		else
			p = "u1";
	} else {
		if (port_dev->usb3_lpm_u2_permit)
			p = "u2";
		else
			p = "0";
	}

	return sprintf(buf, "%s\n", p);
}