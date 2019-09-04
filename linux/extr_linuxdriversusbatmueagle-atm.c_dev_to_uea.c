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
struct usbatm_data {struct uea_softc* driver_data; } ;
struct usb_interface {int dummy; } ;
struct uea_softc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct usbatm_data* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static struct uea_softc *dev_to_uea(struct device *dev)
{
	struct usb_interface *intf;
	struct usbatm_data *usbatm;

	intf = to_usb_interface(dev);
	if (!intf)
		return NULL;

	usbatm = usb_get_intfdata(intf);
	if (!usbatm)
		return NULL;

	return usbatm->driver_data;
}