#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int buf_dma; } ;
struct TYPE_4__ {scalar_t__ speed; } ;
struct ast_vhub_dev {int enabled; int index; scalar_t__ regs; TYPE_3__ ep0; TYPE_2__* vhub; TYPE_1__ gadget; } ;
struct TYPE_5__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ AST_VHUB_DEV_EN_CTRL ; 
 scalar_t__ AST_VHUB_DEV_EP0_DATA ; 
 scalar_t__ AST_VHUB_IER ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int VHUB_DEV_EN_ENABLE_PORT ; 
 int VHUB_DEV_EN_EP0_IN_ACK_IRQEN ; 
 int VHUB_DEV_EN_EP0_OUT_ACK_IRQEN ; 
 int VHUB_DEV_EN_EP0_SETUP_IRQEN ; 
 int VHUB_DEV_EN_SPEED_SEL_HIGH ; 
 int VHUB_IRQ_DEVICE1 ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ast_vhub_dev_enable(struct ast_vhub_dev *d)
{
	u32 reg, hmsk;

	if (d->enabled)
		return;

	/* Enable device and its EP0 interrupts */
	reg = VHUB_DEV_EN_ENABLE_PORT |
		VHUB_DEV_EN_EP0_IN_ACK_IRQEN |
		VHUB_DEV_EN_EP0_OUT_ACK_IRQEN |
		VHUB_DEV_EN_EP0_SETUP_IRQEN;
	if (d->gadget.speed == USB_SPEED_HIGH)
		reg |= VHUB_DEV_EN_SPEED_SEL_HIGH;
	writel(reg, d->regs + AST_VHUB_DEV_EN_CTRL);

	/* Enable device interrupt in the hub as well */
	hmsk = VHUB_IRQ_DEVICE1 << d->index;
	reg = readl(d->vhub->regs + AST_VHUB_IER);
	reg |= hmsk;
	writel(reg, d->vhub->regs + AST_VHUB_IER);

	/* Set EP0 DMA buffer address */
	writel(d->ep0.buf_dma, d->regs + AST_VHUB_DEV_EP0_DATA);

	d->enabled = true;
}