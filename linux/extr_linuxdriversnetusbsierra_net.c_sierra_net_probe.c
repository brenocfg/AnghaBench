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
struct usbnet {int dummy; } ;
struct usb_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  sierra_net_dosync (struct usbnet*) ; 
 struct usbnet* usb_get_intfdata (struct usb_interface*) ; 
 int usbnet_probe (struct usb_interface*,struct usb_device_id const*) ; 
 int usbnet_status_start (struct usbnet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sierra_net_probe(struct usb_interface *udev, const struct usb_device_id *prod)
{
	int ret;

	ret = usbnet_probe(udev, prod);
	if (ret == 0) {
		struct usbnet *dev = usb_get_intfdata(udev);

		ret = usbnet_status_start(dev, GFP_KERNEL);
		if (ret == 0) {
			/* Interrupt URB now set up; initiate sync sequence */
			sierra_net_dosync(dev);
		}
	}
	return ret;
}