#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct port {int /*<<< orphan*/  id; void** tx_buff_tab; TYPE_1__* plat; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_2__ stats; int /*<<< orphan*/  dev; } ;
struct desc {int buf_len; int pkt_len; scalar_t__ data; } ;
struct TYPE_3__ {unsigned int txreadyq; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MAX_MRU ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  TX_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_pkt (struct net_device*,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ixp_tx_timestamp (struct port*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_swab32 (void*,scalar_t__*,int) ; 
 struct port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 scalar_t__ qmgr_stat_below_low_watermark (unsigned int) ; 
 int queue_get_desc (unsigned int,struct port*,int) ; 
 int /*<<< orphan*/  queue_put_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct desc*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  tx_desc_phys (struct port*,int) ; 
 struct desc* tx_desc_ptr (struct port*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int eth_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct port *port = netdev_priv(dev);
	unsigned int txreadyq = port->plat->txreadyq;
	int len, offset, bytes, n;
	void *mem;
	u32 phys;
	struct desc *desc;

#if DEBUG_TX
	printk(KERN_DEBUG "%s: eth_xmit\n", dev->name);
#endif

	if (unlikely(skb->len > MAX_MRU)) {
		dev_kfree_skb(skb);
		dev->stats.tx_errors++;
		return NETDEV_TX_OK;
	}

	debug_pkt(dev, "eth_xmit", skb->data, skb->len);

	len = skb->len;
#ifdef __ARMEB__
	offset = 0; /* no need to keep alignment */
	bytes = len;
	mem = skb->data;
#else
	offset = (int)skb->data & 3; /* keep 32-bit alignment */
	bytes = ALIGN(offset + len, 4);
	if (!(mem = kmalloc(bytes, GFP_ATOMIC))) {
		dev_kfree_skb(skb);
		dev->stats.tx_dropped++;
		return NETDEV_TX_OK;
	}
	memcpy_swab32(mem, (u32 *)((int)skb->data & ~3), bytes / 4);
#endif

	phys = dma_map_single(&dev->dev, mem, bytes, DMA_TO_DEVICE);
	if (dma_mapping_error(&dev->dev, phys)) {
		dev_kfree_skb(skb);
#ifndef __ARMEB__
		kfree(mem);
#endif
		dev->stats.tx_dropped++;
		return NETDEV_TX_OK;
	}

	n = queue_get_desc(txreadyq, port, 1);
	BUG_ON(n < 0);
	desc = tx_desc_ptr(port, n);

#ifdef __ARMEB__
	port->tx_buff_tab[n] = skb;
#else
	port->tx_buff_tab[n] = mem;
#endif
	desc->data = phys + offset;
	desc->buf_len = desc->pkt_len = len;

	/* NPE firmware pads short frames with zeros internally */
	wmb();
	queue_put_desc(TX_QUEUE(port->id), tx_desc_phys(port, n), desc);

	if (qmgr_stat_below_low_watermark(txreadyq)) { /* empty */
#if DEBUG_TX
		printk(KERN_DEBUG "%s: eth_xmit queue full\n", dev->name);
#endif
		netif_stop_queue(dev);
		/* we could miss TX ready interrupt */
		/* really empty in fact */
		if (!qmgr_stat_below_low_watermark(txreadyq)) {
#if DEBUG_TX
			printk(KERN_DEBUG "%s: eth_xmit ready again\n",
			       dev->name);
#endif
			netif_wake_queue(dev);
		}
	}

#if DEBUG_TX
	printk(KERN_DEBUG "%s: eth_xmit end\n", dev->name);
#endif

	ixp_tx_timestamp(port, skb);
	skb_tx_timestamp(skb);

#ifndef __ARMEB__
	dev_kfree_skb(skb);
#endif
	return NETDEV_TX_OK;
}