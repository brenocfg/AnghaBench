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
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct usb_host_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_match_device (struct usb_device*,struct usb_device_id const*) ; 
 int usb_match_one_id_intf (struct usb_device*,struct usb_host_interface*,struct usb_device_id const*) ; 

int usb_match_one_id(struct usb_interface *interface,
		     const struct usb_device_id *id)
{
	struct usb_host_interface *intf;
	struct usb_device *dev;

	/* proc_connectinfo in devio.c may call us with id == NULL. */
	if (id == NULL)
		return 0;

	intf = interface->cur_altsetting;
	dev = interface_to_usbdev(interface);

	if (!usb_match_device(dev, id))
		return 0;

	return usb_match_one_id_intf(dev, intf, id);
}