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
struct port {size_t id; TYPE_2__* plat; int /*<<< orphan*/ ** tx_buff_tab; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct desc {scalar_t__ pkt_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  txdone; } ;
struct TYPE_5__ {int /*<<< orphan*/  txreadyq; } ;

/* Variables and functions */
 struct port* dev_to_port (struct net_device*) ; 
 int /*<<< orphan*/  dma_unmap_tx (struct port*,struct desc*) ; 
 int /*<<< orphan*/  free_buffer_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int qmgr_stat_below_low_watermark (int /*<<< orphan*/ ) ; 
 int queue_get_desc (int /*<<< orphan*/ ,struct port*,int) ; 
 TYPE_3__* queue_ids ; 
 int /*<<< orphan*/  queue_put_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct desc*) ; 
 int /*<<< orphan*/  tx_desc_phys (struct port*,int) ; 
 struct desc* tx_desc_ptr (struct port*,int) ; 

__attribute__((used)) static void hss_hdlc_txdone_irq(void *pdev)
{
	struct net_device *dev = pdev;
	struct port *port = dev_to_port(dev);
	int n_desc;

#if DEBUG_TX
	printk(KERN_DEBUG DRV_NAME ": hss_hdlc_txdone_irq\n");
#endif
	while ((n_desc = queue_get_desc(queue_ids[port->id].txdone,
					port, 1)) >= 0) {
		struct desc *desc;
		int start;

		desc = tx_desc_ptr(port, n_desc);

		dev->stats.tx_packets++;
		dev->stats.tx_bytes += desc->pkt_len;

		dma_unmap_tx(port, desc);
#if DEBUG_TX
		printk(KERN_DEBUG "%s: hss_hdlc_txdone_irq free %p\n",
		       dev->name, port->tx_buff_tab[n_desc]);
#endif
		free_buffer_irq(port->tx_buff_tab[n_desc]);
		port->tx_buff_tab[n_desc] = NULL;

		start = qmgr_stat_below_low_watermark(port->plat->txreadyq);
		queue_put_desc(port->plat->txreadyq,
			       tx_desc_phys(port, n_desc), desc);
		if (start) { /* TX-ready queue was empty */
#if DEBUG_TX
			printk(KERN_DEBUG "%s: hss_hdlc_txdone_irq xmit"
			       " ready\n", dev->name);
#endif
			netif_wake_queue(dev);
		}
	}
}