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
struct mv_udc {TYPE_1__* op_regs; scalar_t__ stopped; } ;
struct TYPE_2__ {int /*<<< orphan*/  usbcmd; int /*<<< orphan*/  usbintr; } ;

/* Variables and functions */
 int USBCMD_RUN_STOP ; 
 int USBINTR_DEVICE_SUSPEND ; 
 int USBINTR_ERR_INT_EN ; 
 int USBINTR_INT_EN ; 
 int USBINTR_PORT_CHANGE_DETECT_EN ; 
 int USBINTR_RESET_EN ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void udc_start(struct mv_udc *udc)
{
	u32 usbintr;

	usbintr = USBINTR_INT_EN | USBINTR_ERR_INT_EN
		| USBINTR_PORT_CHANGE_DETECT_EN
		| USBINTR_RESET_EN | USBINTR_DEVICE_SUSPEND;
	/* Enable interrupts */
	writel(usbintr, &udc->op_regs->usbintr);

	udc->stopped = 0;

	/* Set the Run bit in the command register */
	writel(USBCMD_RUN_STOP, &udc->op_regs->usbcmd);
}