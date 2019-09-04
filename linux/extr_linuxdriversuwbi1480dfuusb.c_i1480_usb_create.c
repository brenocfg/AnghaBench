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
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct i1480_usb {int /*<<< orphan*/ * neep_urb; int /*<<< orphan*/  usb_iface; int /*<<< orphan*/  usb_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/ * usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_get_intf (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_intf (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct i1480_usb*) ; 

__attribute__((used)) static
int i1480_usb_create(struct i1480_usb *i1480_usb, struct usb_interface *iface)
{
	struct usb_device *usb_dev = interface_to_usbdev(iface);
	int result = -ENOMEM;

	i1480_usb->usb_dev = usb_get_dev(usb_dev);	/* bind the USB device */
	i1480_usb->usb_iface = usb_get_intf(iface);
	usb_set_intfdata(iface, i1480_usb);		/* Bind the driver to iface0 */
	i1480_usb->neep_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (i1480_usb->neep_urb == NULL)
		goto error;
	return 0;

error:
	usb_set_intfdata(iface, NULL);
	usb_put_intf(iface);
	usb_put_dev(usb_dev);
	return result;
}