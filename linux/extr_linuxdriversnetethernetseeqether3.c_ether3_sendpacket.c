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
struct sk_buff {unsigned int len; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_5__ {unsigned int command; } ;
struct TYPE_6__ {int tx_head; unsigned int tx_tail; TYPE_2__ regs; scalar_t__ broken; } ;

/* Variables and functions */
 unsigned int CMD_TXON ; 
 unsigned int ETH_ZLEN ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  REG_COMMAND ; 
 int /*<<< orphan*/  REG_STATUS ; 
 int /*<<< orphan*/  REG_TRANSMITPTR ; 
 int STAT_TXON ; 
 int TXHDR_CHAINCONTINUE ; 
 int TXHDR_DATAFOLLOWS ; 
 int TXHDR_ENSUCCESS ; 
 int TXHDR_TRANSMIT ; 
 int /*<<< orphan*/  buffer_write ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int ether3_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether3_ledon (struct net_device*) ; 
 int /*<<< orphan*/  ether3_outw (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether3_setbuffer (struct net_device*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ether3_writebuffer (struct net_device*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ether3_writelong (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether3_writeword (struct net_device*,int) ; 
 int htons (unsigned int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 TYPE_3__* priv (struct net_device*) ; 
 scalar_t__ skb_padto (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static netdev_tx_t
ether3_sendpacket(struct sk_buff *skb, struct net_device *dev)
{
	unsigned long flags;
	unsigned int length = ETH_ZLEN < skb->len ? skb->len : ETH_ZLEN;
	unsigned int ptr, next_ptr;

	if (priv(dev)->broken) {
		dev_kfree_skb(skb);
		dev->stats.tx_dropped++;
		netif_start_queue(dev);
		return NETDEV_TX_OK;
	}

	length = (length + 1) & ~1;
	if (length != skb->len) {
		if (skb_padto(skb, length))
			goto out;
	}

	next_ptr = (priv(dev)->tx_head + 1) & 15;

	local_irq_save(flags);

	if (priv(dev)->tx_tail == next_ptr) {
		local_irq_restore(flags);
		return NETDEV_TX_BUSY;	/* unable to queue */
	}

	ptr		 = 0x600 * priv(dev)->tx_head;
	priv(dev)->tx_head = next_ptr;
	next_ptr	*= 0x600;

#define TXHDR_FLAGS (TXHDR_TRANSMIT|TXHDR_CHAINCONTINUE|TXHDR_DATAFOLLOWS|TXHDR_ENSUCCESS)

	ether3_setbuffer(dev, buffer_write, next_ptr);
	ether3_writelong(dev, 0);
	ether3_setbuffer(dev, buffer_write, ptr);
	ether3_writelong(dev, 0);
	ether3_writebuffer(dev, skb->data, length);
	ether3_writeword(dev, htons(next_ptr));
	ether3_writeword(dev, TXHDR_CHAINCONTINUE >> 16);
	ether3_setbuffer(dev, buffer_write, ptr);
	ether3_writeword(dev, htons((ptr + length + 4)));
	ether3_writeword(dev, TXHDR_FLAGS >> 16);
	ether3_ledon(dev);

	if (!(ether3_inw(REG_STATUS) & STAT_TXON)) {
		ether3_outw(ptr, REG_TRANSMITPTR);
		ether3_outw(priv(dev)->regs.command | CMD_TXON, REG_COMMAND);
	}

	next_ptr = (priv(dev)->tx_head + 1) & 15;
	local_irq_restore(flags);

	dev_kfree_skb(skb);

	if (priv(dev)->tx_tail == next_ptr)
		netif_stop_queue(dev);

 out:
	return NETDEV_TX_OK;
}