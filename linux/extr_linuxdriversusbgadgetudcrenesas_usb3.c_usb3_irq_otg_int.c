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
 int USB_OTG_IDMON ; 
 int /*<<< orphan*/  usb3_irq_idmon_change (struct renesas_usb3*) ; 

__attribute__((used)) static void usb3_irq_otg_int(struct renesas_usb3 *usb3, u32 otg_int_sta)
{
	if (otg_int_sta & USB_OTG_IDMON)
		usb3_irq_idmon_change(usb3);
}