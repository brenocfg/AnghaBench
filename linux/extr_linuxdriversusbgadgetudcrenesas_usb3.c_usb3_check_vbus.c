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
struct renesas_usb3 {int extcon_usb; int /*<<< orphan*/  extcon_work; scalar_t__ workaround_for_vbus; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB3_USB_STA ; 
 int USB_STA_VBUS_STA ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb3_connect (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_disconnect (struct renesas_usb3*) ; 
 int usb3_read (struct renesas_usb3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb3_check_vbus(struct renesas_usb3 *usb3)
{
	if (usb3->workaround_for_vbus) {
		usb3_connect(usb3);
	} else {
		usb3->extcon_usb = !!(usb3_read(usb3, USB3_USB_STA) &
							USB_STA_VBUS_STA);
		if (usb3->extcon_usb)
			usb3_connect(usb3);
		else
			usb3_disconnect(usb3);

		schedule_work(&usb3->extcon_work);
	}
}