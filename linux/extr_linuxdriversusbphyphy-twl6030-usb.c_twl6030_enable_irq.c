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
struct twl6030_usb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_INT_MSK_LINE_C ; 
 int /*<<< orphan*/  REG_INT_MSK_STS_C ; 
 int TWL6030_CHARGER_CTRL_INT_MASK ; 
 int /*<<< orphan*/  TWL_MODULE_USB ; 
 int /*<<< orphan*/  USB_ID_INT_EN_HI_SET ; 
 int /*<<< orphan*/  twl6030_interrupt_unmask (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl6030_writeb (struct twl6030_usb*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6030_enable_irq(struct twl6030_usb *twl)
{
	twl6030_writeb(twl, TWL_MODULE_USB, 0x1, USB_ID_INT_EN_HI_SET);
	twl6030_interrupt_unmask(0x05, REG_INT_MSK_LINE_C);
	twl6030_interrupt_unmask(0x05, REG_INT_MSK_STS_C);

	twl6030_interrupt_unmask(TWL6030_CHARGER_CTRL_INT_MASK,
				REG_INT_MSK_LINE_C);
	twl6030_interrupt_unmask(TWL6030_CHARGER_CTRL_INT_MASK,
				REG_INT_MSK_STS_C);

	return 0;
}