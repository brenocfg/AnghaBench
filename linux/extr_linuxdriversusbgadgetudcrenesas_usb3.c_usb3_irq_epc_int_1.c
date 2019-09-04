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
typedef  int u32 ;
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int USB_INT_1_B2_RSUM ; 
 int USB_INT_1_B2_USBRST ; 
 int USB_INT_1_B3_DISABLE ; 
 int USB_INT_1_B3_HOTRST ; 
 int USB_INT_1_B3_LUPSUCS ; 
 int USB_INT_1_B3_PLLWKUP ; 
 int USB_INT_1_B3_WRMRST ; 
 int USB_INT_1_SPEED ; 
 int USB_INT_1_VBUS_CNG ; 
 int /*<<< orphan*/  usb3_irq_epc_int_1_bus_reset (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_irq_epc_int_1_disable (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_irq_epc_int_1_hot_reset (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_irq_epc_int_1_linkup_success (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_irq_epc_int_1_pll_wakeup (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_irq_epc_int_1_resume (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_irq_epc_int_1_speed (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_irq_epc_int_1_vbus_change (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_irq_epc_int_1_warm_reset (struct renesas_usb3*) ; 

__attribute__((used)) static void usb3_irq_epc_int_1(struct renesas_usb3 *usb3, u32 int_sta_1)
{
	if (int_sta_1 & USB_INT_1_B3_PLLWKUP)
		usb3_irq_epc_int_1_pll_wakeup(usb3);

	if (int_sta_1 & USB_INT_1_B3_LUPSUCS)
		usb3_irq_epc_int_1_linkup_success(usb3);

	if (int_sta_1 & USB_INT_1_B3_HOTRST)
		usb3_irq_epc_int_1_hot_reset(usb3);

	if (int_sta_1 & USB_INT_1_B3_WRMRST)
		usb3_irq_epc_int_1_warm_reset(usb3);

	if (int_sta_1 & USB_INT_1_B3_DISABLE)
		usb3_irq_epc_int_1_disable(usb3);

	if (int_sta_1 & USB_INT_1_B2_USBRST)
		usb3_irq_epc_int_1_bus_reset(usb3);

	if (int_sta_1 & USB_INT_1_B2_RSUM)
		usb3_irq_epc_int_1_resume(usb3);

	if (int_sta_1 & USB_INT_1_SPEED)
		usb3_irq_epc_int_1_speed(usb3);

	if (int_sta_1 & USB_INT_1_VBUS_CNG)
		usb3_irq_epc_int_1_vbus_change(usb3);
}