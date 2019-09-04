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
struct device {int dummy; } ;
struct usb_interface {int authorized; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 

void usb_authorize_interface(struct usb_interface *intf)
{
	struct device *dev = &intf->dev;

	if (!intf->authorized) {
		device_lock(dev);
		intf->authorized = 1; /* authorize interface */
		device_unlock(dev);
	}
}