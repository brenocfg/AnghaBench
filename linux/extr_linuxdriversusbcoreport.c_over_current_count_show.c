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
struct usb_port {int over_current_count; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct usb_port* to_usb_port (struct device*) ; 

__attribute__((used)) static ssize_t over_current_count_show(struct device *dev,
				       struct device_attribute *attr, char *buf)
{
	struct usb_port *port_dev = to_usb_port(dev);

	return sprintf(buf, "%u\n", port_dev->over_current_count);
}