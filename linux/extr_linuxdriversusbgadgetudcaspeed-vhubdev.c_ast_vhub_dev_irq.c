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
struct ast_vhub_dev {int /*<<< orphan*/  ep0; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ AST_VHUB_DEV_ISR ; 
 int VHUV_DEV_IRQ_EP0_IN_ACK_STALL ; 
 int VHUV_DEV_IRQ_EP0_OUT_ACK_STALL ; 
 int VHUV_DEV_IRQ_EP0_SETUP ; 
 int /*<<< orphan*/  ast_vhub_ep0_handle_ack (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ast_vhub_ep0_handle_setup (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void ast_vhub_dev_irq(struct ast_vhub_dev *d)
{
	u32 istat = readl(d->regs + AST_VHUB_DEV_ISR);

	writel(istat, d->regs + AST_VHUB_DEV_ISR);

	if (istat & VHUV_DEV_IRQ_EP0_IN_ACK_STALL)
		ast_vhub_ep0_handle_ack(&d->ep0, true);
	if (istat & VHUV_DEV_IRQ_EP0_OUT_ACK_STALL)
		ast_vhub_ep0_handle_ack(&d->ep0, false);
	if (istat & VHUV_DEV_IRQ_EP0_SETUP)
		ast_vhub_ep0_handle_setup(&d->ep0);
}