#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mv_udc {int stopped; TYPE_1__* op_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  usbcmd; int /*<<< orphan*/  usbintr; } ;

/* Variables and functions */
 int USBCMD_RUN_STOP ; 
 int USBINTR_ERR_INT_EN ; 
 int USBINTR_INT_EN ; 
 int USBINTR_PORT_CHANGE_DETECT_EN ; 
 int USBINTR_RESET_EN ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void udc_stop(struct mv_udc *udc)
{
	u32 tmp;

	/* Disable interrupts */
	tmp = readl(&udc->op_regs->usbintr);
	tmp &= ~(USBINTR_INT_EN | USBINTR_ERR_INT_EN |
		USBINTR_PORT_CHANGE_DETECT_EN | USBINTR_RESET_EN);
	writel(tmp, &udc->op_regs->usbintr);

	udc->stopped = 1;

	/* Reset the Run the bit in the command register to stop VUSB */
	tmp = readl(&udc->op_regs->usbcmd);
	tmp &= ~USBCMD_RUN_STOP;
	writel(tmp, &udc->op_regs->usbcmd);
}