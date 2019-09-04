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
struct z8530_channel {size_t tx_dma_used; int /*<<< orphan*/  lock; struct sk_buff* tx_next_skb; scalar_t__ tx_next_ptr; scalar_t__* tx_dma_buf; scalar_t__ dma_tx; int /*<<< orphan*/  netdevice; } ;
struct sk_buff {scalar_t__ data; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  RT_LOCK ; 
 int /*<<< orphan*/  RT_UNLOCK ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,scalar_t__,scalar_t__) ; 
 scalar_t__ spans_boundary (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ virt_to_bus (scalar_t__) ; 
 int /*<<< orphan*/  z8530_tx_begin (struct z8530_channel*) ; 

netdev_tx_t z8530_queue_xmit(struct z8530_channel *c, struct sk_buff *skb)
{
	unsigned long flags;
	
	netif_stop_queue(c->netdevice);
	if(c->tx_next_skb)
		return NETDEV_TX_BUSY;

	
	/* PC SPECIFIC - DMA limits */
	
	/*
	 *	If we will DMA the transmit and its gone over the ISA bus
	 *	limit, then copy to the flip buffer
	 */
	 
	if(c->dma_tx && ((unsigned long)(virt_to_bus(skb->data+skb->len))>=16*1024*1024 || spans_boundary(skb)))
	{
		/* 
		 *	Send the flip buffer, and flip the flippy bit.
		 *	We don't care which is used when just so long as
		 *	we never use the same buffer twice in a row. Since
		 *	only one buffer can be going out at a time the other
		 *	has to be safe.
		 */
		c->tx_next_ptr=c->tx_dma_buf[c->tx_dma_used];
		c->tx_dma_used^=1;	/* Flip temp buffer */
		skb_copy_from_linear_data(skb, c->tx_next_ptr, skb->len);
	}
	else
		c->tx_next_ptr=skb->data;	
	RT_LOCK;
	c->tx_next_skb=skb;
	RT_UNLOCK;
	
	spin_lock_irqsave(c->lock, flags);
	z8530_tx_begin(c);
	spin_unlock_irqrestore(c->lock, flags);
	
	return NETDEV_TX_OK;
}