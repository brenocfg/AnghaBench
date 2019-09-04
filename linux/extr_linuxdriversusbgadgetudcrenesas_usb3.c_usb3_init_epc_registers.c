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
struct renesas_usb3 {int /*<<< orphan*/  workaround_for_vbus; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB3_USB_INT_STA_1 ; 
 int /*<<< orphan*/  USB_INT_1_VBUS_CNG ; 
 int /*<<< orphan*/  usb3_enable_irq_1 (struct renesas_usb3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_write (struct renesas_usb3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb3_init_epc_registers(struct renesas_usb3 *usb3)
{
	usb3_write(usb3, ~0, USB3_USB_INT_STA_1);
	if (!usb3->workaround_for_vbus)
		usb3_enable_irq_1(usb3, USB_INT_1_VBUS_CNG);
}