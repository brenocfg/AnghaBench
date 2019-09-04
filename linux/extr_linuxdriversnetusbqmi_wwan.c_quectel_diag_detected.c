#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct usb_interface_descriptor {int bNumEndpoints; } ;
struct usb_interface {TYPE_1__* cur_altsetting; } ;
struct TYPE_4__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_2__ descriptor; } ;
struct TYPE_3__ {struct usb_interface_descriptor desc; } ;

/* Variables and functions */
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool quectel_diag_detected(struct usb_interface *intf)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	struct usb_interface_descriptor intf_desc = intf->cur_altsetting->desc;
	u16 id_vendor = le16_to_cpu(dev->descriptor.idVendor);
	u16 id_product = le16_to_cpu(dev->descriptor.idProduct);

	if (id_vendor != 0x2c7c || intf_desc.bNumEndpoints != 2)
		return false;

	if (id_product == 0x0306 || id_product == 0x0512)
		return true;
	else
		return false;
}