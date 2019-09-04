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
struct usb_interface {scalar_t__ condition; } ;
struct usb_device {scalar_t__ state; } ;

/* Variables and functions */
 int EBUSY ; 
 int EHOSTUNREACH ; 
 int EINTR ; 
 int ENODEV ; 
 unsigned long HZ ; 
 scalar_t__ USB_INTERFACE_UNBINDING ; 
 scalar_t__ USB_INTERFACE_UNBOUND ; 
 scalar_t__ USB_STATE_NOTATTACHED ; 
 scalar_t__ USB_STATE_SUSPENDED ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usb_trylock_device (struct usb_device*) ; 

int usb_lock_device_for_reset(struct usb_device *udev,
			      const struct usb_interface *iface)
{
	unsigned long jiffies_expire = jiffies + HZ;

	if (udev->state == USB_STATE_NOTATTACHED)
		return -ENODEV;
	if (udev->state == USB_STATE_SUSPENDED)
		return -EHOSTUNREACH;
	if (iface && (iface->condition == USB_INTERFACE_UNBINDING ||
			iface->condition == USB_INTERFACE_UNBOUND))
		return -EINTR;

	while (!usb_trylock_device(udev)) {

		/* If we can't acquire the lock after waiting one second,
		 * we're probably deadlocked */
		if (time_after(jiffies, jiffies_expire))
			return -EBUSY;

		msleep(15);
		if (udev->state == USB_STATE_NOTATTACHED)
			return -ENODEV;
		if (udev->state == USB_STATE_SUSPENDED)
			return -EHOSTUNREACH;
		if (iface && (iface->condition == USB_INTERFACE_UNBINDING ||
				iface->condition == USB_INTERFACE_UNBOUND))
			return -EINTR;
	}
	return 0;
}