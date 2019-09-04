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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct port {size_t tx_out; int node; int /*<<< orphan*/  lock; TYPE_1__* card; struct sk_buff** tx_skbs; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_5__ {scalar_t__ stat; int /*<<< orphan*/  length; int /*<<< orphan*/  address; } ;
typedef  TYPE_2__ desc_t ;
struct TYPE_6__ {TYPE_2__* tx_descs; } ;
struct TYPE_4__ {scalar_t__ plx; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int DOORBELL_TO_CARD_TX_0 ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ PACKET_EMPTY ; 
 scalar_t__ PACKET_FULL ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 scalar_t__ PLX_DOORBELL_TO_CARD ; 
 int TX_BUFFERS ; 
 struct port* dev_to_port (struct net_device*) ; 
 TYPE_3__* get_status (struct port*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static netdev_tx_t wanxl_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct port *port = dev_to_port(dev);
	desc_t *desc;

        spin_lock(&port->lock);

	desc = &get_status(port)->tx_descs[port->tx_out];
        if (desc->stat != PACKET_EMPTY) {
                /* should never happen - previous xmit should stop queue */
#ifdef DEBUG_PKT
                printk(KERN_DEBUG "%s: transmitter buffer full\n", dev->name);
#endif
		netif_stop_queue(dev);
		spin_unlock(&port->lock);
		return NETDEV_TX_BUSY;       /* request packet to be queued */
	}

#ifdef DEBUG_PKT
	printk(KERN_DEBUG "%s TX(%i):", dev->name, skb->len);
	debug_frame(skb);
#endif

	port->tx_skbs[port->tx_out] = skb;
	desc->address = pci_map_single(port->card->pdev, skb->data, skb->len,
				       PCI_DMA_TODEVICE);
	desc->length = skb->len;
	desc->stat = PACKET_FULL;
	writel(1 << (DOORBELL_TO_CARD_TX_0 + port->node),
	       port->card->plx + PLX_DOORBELL_TO_CARD);

	port->tx_out = (port->tx_out + 1) % TX_BUFFERS;

	if (get_status(port)->tx_descs[port->tx_out].stat != PACKET_EMPTY) {
		netif_stop_queue(dev);
#ifdef DEBUG_PKT
		printk(KERN_DEBUG "%s: transmitter buffer full\n", dev->name);
#endif
	}

	spin_unlock(&port->lock);
	return NETDEV_TX_OK;
}