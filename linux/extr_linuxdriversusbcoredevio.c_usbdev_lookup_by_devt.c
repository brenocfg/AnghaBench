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
struct usb_device {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 struct device* bus_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_devt ; 
 struct usb_device* to_usb_device (struct device*) ; 
 int /*<<< orphan*/  usb_bus_type ; 

__attribute__((used)) static struct usb_device *usbdev_lookup_by_devt(dev_t devt)
{
	struct device *dev;

	dev = bus_find_device(&usb_bus_type, NULL,
			      (void *) (unsigned long) devt, match_devt);
	if (!dev)
		return NULL;
	return to_usb_device(dev);
}