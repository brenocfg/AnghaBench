#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usbnet {int /*<<< orphan*/  data; } ;
struct usb_interface {int dummy; } ;
struct cdc_state {int /*<<< orphan*/  data; TYPE_1__* ether; } ;
struct TYPE_2__ {int /*<<< orphan*/  iMACAddress; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  driver_of (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_driver_release_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usbnet_ether_cdc_bind (struct usbnet*,struct usb_interface*) ; 
 int usbnet_get_ethernet_addr (struct usbnet*,int /*<<< orphan*/ ) ; 

int usbnet_cdc_bind(struct usbnet *dev, struct usb_interface *intf)
{
	int				status;
	struct cdc_state		*info = (void *) &dev->data;

	BUILD_BUG_ON((sizeof(((struct usbnet *)0)->data)
			< sizeof(struct cdc_state)));

	status = usbnet_ether_cdc_bind(dev, intf);
	if (status < 0)
		return status;

	status = usbnet_get_ethernet_addr(dev, info->ether->iMACAddress);
	if (status < 0) {
		usb_set_intfdata(info->data, NULL);
		usb_driver_release_interface(driver_of(intf), info->data);
		return status;
	}

	return 0;
}