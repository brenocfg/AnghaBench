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
struct z8530_channel {int sync; int* regs; int /*<<< orphan*/  lock; scalar_t__ dma_tx; int /*<<< orphan*/ * irqs; int /*<<< orphan*/ * skb2; int /*<<< orphan*/ * skb; scalar_t__ count; scalar_t__ mtu; } ;
struct net_device {scalar_t__ mtu; } ;

/* Variables and functions */
 size_t R1 ; 
 size_t R3 ; 
 int RxENABLE ; 
 int TxINT_ENAB ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  write_zsreg (struct z8530_channel*,size_t,int) ; 
 int /*<<< orphan*/  z8530_rtsdtr (struct z8530_channel*,int) ; 
 int /*<<< orphan*/  z8530_rx_done (struct z8530_channel*) ; 
 int /*<<< orphan*/  z8530_sync ; 

int z8530_sync_open(struct net_device *dev, struct z8530_channel *c)
{
	unsigned long flags;

	spin_lock_irqsave(c->lock, flags);

	c->sync = 1;
	c->mtu = dev->mtu+64;
	c->count = 0;
	c->skb = NULL;
	c->skb2 = NULL;
	c->irqs = &z8530_sync;

	/* This loads the double buffer up */
	z8530_rx_done(c);	/* Load the frame ring */
	z8530_rx_done(c);	/* Load the backup frame */
	z8530_rtsdtr(c,1);
	c->dma_tx = 0;
	c->regs[R1]|=TxINT_ENAB;
	write_zsreg(c, R1, c->regs[R1]);
	write_zsreg(c, R3, c->regs[R3]|RxENABLE);

	spin_unlock_irqrestore(c->lock, flags);
	return 0;
}