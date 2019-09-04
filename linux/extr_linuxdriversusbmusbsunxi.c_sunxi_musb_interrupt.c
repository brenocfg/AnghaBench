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
struct musb {int int_usb; int /*<<< orphan*/  lock; scalar_t__ mregs; void* int_rx; void* int_tx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MUSB_FADDR ; 
 int MUSB_INTR_RESET ; 
 scalar_t__ SUNXI_MUSB_INTRRX ; 
 scalar_t__ SUNXI_MUSB_INTRTX ; 
 scalar_t__ SUNXI_MUSB_INTRUSB ; 
 int /*<<< orphan*/  is_host_active (struct musb*) ; 
 int /*<<< orphan*/  musb_ep_select (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_interrupt (struct musb*) ; 
 int /*<<< orphan*/  musb_writeb (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readb (scalar_t__) ; 
 void* readw (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writew (void*,scalar_t__) ; 

__attribute__((used)) static irqreturn_t sunxi_musb_interrupt(int irq, void *__hci)
{
	struct musb *musb = __hci;
	unsigned long flags;

	spin_lock_irqsave(&musb->lock, flags);

	musb->int_usb = readb(musb->mregs + SUNXI_MUSB_INTRUSB);
	if (musb->int_usb)
		writeb(musb->int_usb, musb->mregs + SUNXI_MUSB_INTRUSB);

	if ((musb->int_usb & MUSB_INTR_RESET) && !is_host_active(musb)) {
		/* ep0 FADDR must be 0 when (re)entering peripheral mode */
		musb_ep_select(musb->mregs, 0);
		musb_writeb(musb->mregs, MUSB_FADDR, 0);
	}

	musb->int_tx = readw(musb->mregs + SUNXI_MUSB_INTRTX);
	if (musb->int_tx)
		writew(musb->int_tx, musb->mregs + SUNXI_MUSB_INTRTX);

	musb->int_rx = readw(musb->mregs + SUNXI_MUSB_INTRRX);
	if (musb->int_rx)
		writew(musb->int_rx, musb->mregs + SUNXI_MUSB_INTRRX);

	musb_interrupt(musb);

	spin_unlock_irqrestore(&musb->lock, flags);

	return IRQ_HANDLED;
}