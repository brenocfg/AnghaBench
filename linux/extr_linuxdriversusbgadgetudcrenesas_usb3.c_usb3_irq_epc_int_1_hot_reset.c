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
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB30_CON_B3_HOTRST_CMP ; 
 int /*<<< orphan*/  USB3_USB30_CON ; 
 int /*<<< orphan*/  USB3_USB_COM_CON ; 
 int /*<<< orphan*/  USB_COM_CON_EP0_EN ; 
 int /*<<< orphan*/  usb3_reset_epc (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_set_bit (struct renesas_usb3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb3_irq_epc_int_1_hot_reset(struct renesas_usb3 *usb3)
{
	usb3_reset_epc(usb3);
	usb3_set_bit(usb3, USB_COM_CON_EP0_EN, USB3_USB_COM_CON);

	/* This bit shall be set within 12ms from the start of HotReset */
	usb3_set_bit(usb3, USB30_CON_B3_HOTRST_CMP, USB3_USB30_CON);
}