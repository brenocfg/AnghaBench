#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {TYPE_2__* altsetting; } ;
struct usb_device {TYPE_4__* config; } ;
struct TYPE_7__ {int bNumInterfaces; } ;
struct TYPE_8__ {TYPE_3__ desc; } ;
struct TYPE_5__ {int bInterfaceNumber; } ;
struct TYPE_6__ {TYPE_1__ desc; } ;

/* Variables and functions */
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uea_enters (struct usb_device*) ; 
 int /*<<< orphan*/  uea_info (struct usb_device*,char*) ; 
 int /*<<< orphan*/  uea_leaves (struct usb_device*) ; 
 int /*<<< orphan*/  uea_mutex ; 
 int /*<<< orphan*/  usbatm_usb_disconnect (struct usb_interface*) ; 

__attribute__((used)) static void uea_disconnect(struct usb_interface *intf)
{
	struct usb_device *usb = interface_to_usbdev(intf);
	int ifnum = intf->altsetting->desc.bInterfaceNumber;
	uea_enters(usb);

	/* ADI930 has 2 interfaces and eagle 3 interfaces.
	 * Pre-firmware device has one interface
	 */
	if (usb->config->desc.bNumInterfaces != 1 && ifnum == 0) {
		mutex_lock(&uea_mutex);
		usbatm_usb_disconnect(intf);
		mutex_unlock(&uea_mutex);
		uea_info(usb, "ADSL device removed\n");
	}

	uea_leaves(usb);
}