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
typedef  scalar_t__ u32 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct port {size_t id; void** tx_buff_tab; TYPE_1__* plat; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_2__ stats; int /*<<< orphan*/  dev; } ;
struct desc {int buf_len; int pkt_len; scalar_t__ data; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx; } ;
struct TYPE_4__ {unsigned int txreadyq; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HDLC_MAX_MRU ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  debug_pkt (struct net_device*,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct port* dev_to_port (struct net_device*) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_swab32 (void*,scalar_t__*,int) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 scalar_t__ qmgr_stat_below_low_watermark (unsigned int) ; 
 int queue_get_desc (unsigned int,struct port*,int) ; 
 TYPE_3__* queue_ids ; 
 int /*<<< orphan*/  queue_put_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct desc*) ; 
 int /*<<< orphan*/  tx_desc_phys (struct port*,int) ; 
 struct desc* tx_desc_ptr (struct port*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int hss_hdlc_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct port *port = dev_to_port(dev);
	unsigned int txreadyq = port->plat->txreadyq;
	int len, offset, bytes, n;
	void *mem;
	u32 phys;
	struct desc *desc;

#if DEBUG_TX
	printk(KERN_DEBUG "%s: hss_hdlc_xmit\n", dev->name);
#endif

	if (unlikely(skb->len > HDLC_MAX_MRU)) {
		dev_kfree_skb(skb);
		dev->stats.tx_errors++;
		return NETDEV_TX_OK;
	}

	debug_pkt(dev, "hss_hdlc_xmit", skb->data, skb->len);

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
	dev_kfree_skb(skb);
#endif

	phys = dma_map_single(&dev->dev, mem, bytes, DMA_TO_DEVICE);
	if (dma_mapping_error(&dev->dev, phys)) {
#ifdef __ARMEB__
		dev_kfree_skb(skb);
#else
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

	wmb();
	queue_put_desc(queue_ids[port->id].tx, tx_desc_phys(port, n), desc);

	if (qmgr_stat_below_low_watermark(txreadyq)) { /* empty */
#if DEBUG_TX
		printk(KERN_DEBUG "%s: hss_hdlc_xmit queue full\n", dev->name);
#endif
		netif_stop_queue(dev);
		/* we could miss TX ready interrupt */
		if (!qmgr_stat_below_low_watermark(txreadyq)) {
#if DEBUG_TX
			printk(KERN_DEBUG "%s: hss_hdlc_xmit ready again\n",
			       dev->name);
#endif
			netif_wake_queue(dev);
		}
	}

#if DEBUG_TX
	printk(KERN_DEBUG "%s: hss_hdlc_xmit end\n", dev->name);
#endif
	return NETDEV_TX_OK;
}