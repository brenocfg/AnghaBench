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
 int USB20_CON_B2_SUSPEND ; 
 int /*<<< orphan*/  USB3_USB20_CON ; 
 int /*<<< orphan*/  USB_INT_1_B2_RSUM ; 
 int /*<<< orphan*/  usb3_clear_bit (struct renesas_usb3*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_enable_irq_1 (struct renesas_usb3*,int /*<<< orphan*/ ) ; 
 int usb3_read (struct renesas_usb3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool usb3_wakeup_usb2_phy(struct renesas_usb3 *usb3)
{
	if (!(usb3_read(usb3, USB3_USB20_CON) & USB20_CON_B2_SUSPEND))
		return true;	/* already waked it up */

	usb3_clear_bit(usb3, USB20_CON_B2_SUSPEND, USB3_USB20_CON);
	usb3_enable_irq_1(usb3, USB_INT_1_B2_RSUM);

	return false;
}