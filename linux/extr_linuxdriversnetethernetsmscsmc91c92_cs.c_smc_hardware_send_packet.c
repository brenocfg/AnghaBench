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
typedef  int u_int ;
typedef  int u_char ;
struct smc_private {struct sk_buff* saved_skb; } ;
struct sk_buff {int len; int* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_bytes; } ;
struct net_device {unsigned int base_addr; TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ DATA_1 ; 
 int IM_TX_EMPTY_INT ; 
 int IM_TX_INT ; 
 scalar_t__ INTERRUPT ; 
 int MC_ENQUEUE ; 
 scalar_t__ MMU_CMD ; 
 scalar_t__ PNR_ARR ; 
 scalar_t__ POINTER ; 
 int PTR_AUTOINC ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  outsw (scalar_t__,int*,int) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static void smc_hardware_send_packet(struct net_device * dev)
{
    struct smc_private *smc = netdev_priv(dev);
    struct sk_buff *skb = smc->saved_skb;
    unsigned int ioaddr = dev->base_addr;
    u_char packet_no;

    if (!skb) {
	netdev_err(dev, "In XMIT with no packet to send\n");
	return;
    }

    /* There should be a packet slot waiting. */
    packet_no = inw(ioaddr + PNR_ARR) >> 8;
    if (packet_no & 0x80) {
	/* If not, there is a hardware problem!  Likely an ejected card. */
	netdev_warn(dev, "hardware Tx buffer allocation failed, status %#2.2x\n",
		    packet_no);
	dev_kfree_skb_irq(skb);
	smc->saved_skb = NULL;
	netif_start_queue(dev);
	return;
    }

    dev->stats.tx_bytes += skb->len;
    /* The card should use the just-allocated buffer. */
    outw(packet_no, ioaddr + PNR_ARR);
    /* point to the beginning of the packet */
    outw(PTR_AUTOINC , ioaddr + POINTER);

    /* Send the packet length (+6 for status, length and ctl byte)
       and the status word (set to zeros). */
    {
	u_char *buf = skb->data;
	u_int length = skb->len; /* The chip will pad to ethernet min. */

	netdev_dbg(dev, "Trying to xmit packet of length %d\n", length);
	
	/* send the packet length: +6 for status word, length, and ctl */
	outw(0, ioaddr + DATA_1);
	outw(length + 6, ioaddr + DATA_1);
	outsw(ioaddr + DATA_1, buf, length >> 1);
	
	/* The odd last byte, if there is one, goes in the control word. */
	outw((length & 1) ? 0x2000 | buf[length-1] : 0, ioaddr + DATA_1);
    }

    /* Enable the Tx interrupts, both Tx (TxErr) and TxEmpty. */
    outw(((IM_TX_INT|IM_TX_EMPTY_INT)<<8) |
	 (inw(ioaddr + INTERRUPT) & 0xff00),
	 ioaddr + INTERRUPT);

    /* The chip does the rest of the work. */
    outw(MC_ENQUEUE , ioaddr + MMU_CMD);

    smc->saved_skb = NULL;
    dev_kfree_skb_irq(skb);
    netif_trans_update(dev);
    netif_start_queue(dev);
}