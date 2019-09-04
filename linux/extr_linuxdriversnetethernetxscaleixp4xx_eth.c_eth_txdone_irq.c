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
struct port {TYPE_3__* netdev; TYPE_2__* plat; int /*<<< orphan*/ ** tx_buff_tab; } ;
struct desc {scalar_t__ pkt_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_6__ {TYPE_1__ stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  txreadyq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MAX_NPES ; 
 int /*<<< orphan*/  TXDONE_QUEUE ; 
 int TX_DESCS ; 
 int /*<<< orphan*/  debug_desc (int,struct desc*) ; 
 int /*<<< orphan*/  dma_unmap_tx (struct port*,struct desc*) ; 
 int /*<<< orphan*/  free_buffer_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_3__*) ; 
 struct port** npe_port_tab ; 
 int qmgr_get_entry (int /*<<< orphan*/ ) ; 
 int qmgr_stat_below_low_watermark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_put_desc (int /*<<< orphan*/ ,int,struct desc*) ; 
 int /*<<< orphan*/  tx_desc_phys (struct port*,int /*<<< orphan*/ ) ; 
 struct desc* tx_desc_ptr (struct port*,int) ; 

__attribute__((used)) static void eth_txdone_irq(void *unused)
{
	u32 phys;

#if DEBUG_TX
	printk(KERN_DEBUG DRV_NAME ": eth_txdone_irq\n");
#endif
	while ((phys = qmgr_get_entry(TXDONE_QUEUE)) != 0) {
		u32 npe_id, n_desc;
		struct port *port;
		struct desc *desc;
		int start;

		npe_id = phys & 3;
		BUG_ON(npe_id >= MAX_NPES);
		port = npe_port_tab[npe_id];
		BUG_ON(!port);
		phys &= ~0x1F; /* mask out non-address bits */
		n_desc = (phys - tx_desc_phys(port, 0)) / sizeof(struct desc);
		BUG_ON(n_desc >= TX_DESCS);
		desc = tx_desc_ptr(port, n_desc);
		debug_desc(phys, desc);

		if (port->tx_buff_tab[n_desc]) { /* not the draining packet */
			port->netdev->stats.tx_packets++;
			port->netdev->stats.tx_bytes += desc->pkt_len;

			dma_unmap_tx(port, desc);
#if DEBUG_TX
			printk(KERN_DEBUG "%s: eth_txdone_irq free %p\n",
			       port->netdev->name, port->tx_buff_tab[n_desc]);
#endif
			free_buffer_irq(port->tx_buff_tab[n_desc]);
			port->tx_buff_tab[n_desc] = NULL;
		}

		start = qmgr_stat_below_low_watermark(port->plat->txreadyq);
		queue_put_desc(port->plat->txreadyq, phys, desc);
		if (start) { /* TX-ready queue was empty */
#if DEBUG_TX
			printk(KERN_DEBUG "%s: eth_txdone_irq xmit ready\n",
			       port->netdev->name);
#endif
			netif_wake_queue(port->netdev);
		}
	}
}