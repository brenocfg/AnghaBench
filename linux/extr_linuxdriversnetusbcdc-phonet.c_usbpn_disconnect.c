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
struct usbpn_dev {int disconnected; int /*<<< orphan*/  dev; struct usb_interface* intf; struct usb_interface* data_intf; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_driver_release_interface (int /*<<< orphan*/ *,struct usb_interface*) ; 
 struct usbpn_dev* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usbpn_driver ; 

__attribute__((used)) static void usbpn_disconnect(struct usb_interface *intf)
{
	struct usbpn_dev *pnd = usb_get_intfdata(intf);

	if (pnd->disconnected)
		return;

	pnd->disconnected = 1;
	usb_driver_release_interface(&usbpn_driver,
			(pnd->intf == intf) ? pnd->data_intf : pnd->intf);
	unregister_netdev(pnd->dev);
}