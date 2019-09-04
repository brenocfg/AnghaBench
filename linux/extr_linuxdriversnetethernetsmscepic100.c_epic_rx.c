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
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  protocol; } ;
struct TYPE_3__ {short rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_length_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct epic_private {int cur_rx; int dirty_rx; TYPE_2__* rx_ring; int /*<<< orphan*/  rx_buf_sz; int /*<<< orphan*/  pci_dev; struct sk_buff** rx_skbuff; } ;
struct TYPE_4__ {int rxstatus; int /*<<< orphan*/  bufaddr; } ;

/* Variables and functions */
 int DescOwn ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int PKT_BUF_SZ ; 
 int RX_RING_SIZE ; 
 int debug ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 void* netdev_alloc_skb (struct net_device*,short) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int,...) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int,short) ; 
 struct epic_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 short rx_copybreak ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/ ,short) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,short) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static int epic_rx(struct net_device *dev, int budget)
{
	struct epic_private *ep = netdev_priv(dev);
	int entry = ep->cur_rx % RX_RING_SIZE;
	int rx_work_limit = ep->dirty_rx + RX_RING_SIZE - ep->cur_rx;
	int work_done = 0;

	if (debug > 4)
		netdev_dbg(dev, " In epic_rx(), entry %d %8.8x.\n", entry,
			   ep->rx_ring[entry].rxstatus);

	if (rx_work_limit > budget)
		rx_work_limit = budget;

	/* If we own the next entry, it's a new packet. Send it up. */
	while ((ep->rx_ring[entry].rxstatus & DescOwn) == 0) {
		int status = ep->rx_ring[entry].rxstatus;

		if (debug > 4)
			netdev_dbg(dev, "  epic_rx() status was %8.8x.\n",
				   status);
		if (--rx_work_limit < 0)
			break;
		if (status & 0x2006) {
			if (debug > 2)
				netdev_dbg(dev, "epic_rx() error status was %8.8x.\n",
					   status);
			if (status & 0x2000) {
				netdev_warn(dev, "Oversized Ethernet frame spanned multiple buffers, status %4.4x!\n",
					    status);
				dev->stats.rx_length_errors++;
			} else if (status & 0x0006)
				/* Rx Frame errors are counted in hardware. */
				dev->stats.rx_errors++;
		} else {
			/* Malloc up new buffer, compatible with net-2e. */
			/* Omit the four octet CRC from the length. */
			short pkt_len = (status >> 16) - 4;
			struct sk_buff *skb;

			if (pkt_len > PKT_BUF_SZ - 4) {
				netdev_err(dev, "Oversized Ethernet frame, status %x %d bytes.\n",
					   status, pkt_len);
				pkt_len = 1514;
			}
			/* Check if the packet is long enough to accept without copying
			   to a minimally-sized skbuff. */
			if (pkt_len < rx_copybreak &&
			    (skb = netdev_alloc_skb(dev, pkt_len + 2)) != NULL) {
				skb_reserve(skb, 2);	/* 16 byte align the IP header */
				pci_dma_sync_single_for_cpu(ep->pci_dev,
							    ep->rx_ring[entry].bufaddr,
							    ep->rx_buf_sz,
							    PCI_DMA_FROMDEVICE);
				skb_copy_to_linear_data(skb, ep->rx_skbuff[entry]->data, pkt_len);
				skb_put(skb, pkt_len);
				pci_dma_sync_single_for_device(ep->pci_dev,
							       ep->rx_ring[entry].bufaddr,
							       ep->rx_buf_sz,
							       PCI_DMA_FROMDEVICE);
			} else {
				pci_unmap_single(ep->pci_dev,
					ep->rx_ring[entry].bufaddr,
					ep->rx_buf_sz, PCI_DMA_FROMDEVICE);
				skb_put(skb = ep->rx_skbuff[entry], pkt_len);
				ep->rx_skbuff[entry] = NULL;
			}
			skb->protocol = eth_type_trans(skb, dev);
			netif_receive_skb(skb);
			dev->stats.rx_packets++;
			dev->stats.rx_bytes += pkt_len;
		}
		work_done++;
		entry = (++ep->cur_rx) % RX_RING_SIZE;
	}

	/* Refill the Rx ring buffers. */
	for (; ep->cur_rx - ep->dirty_rx > 0; ep->dirty_rx++) {
		entry = ep->dirty_rx % RX_RING_SIZE;
		if (ep->rx_skbuff[entry] == NULL) {
			struct sk_buff *skb;
			skb = ep->rx_skbuff[entry] = netdev_alloc_skb(dev, ep->rx_buf_sz + 2);
			if (skb == NULL)
				break;
			skb_reserve(skb, 2);	/* Align IP on 16 byte boundaries */
			ep->rx_ring[entry].bufaddr = pci_map_single(ep->pci_dev,
				skb->data, ep->rx_buf_sz, PCI_DMA_FROMDEVICE);
			work_done++;
		}
		/* AV: shouldn't we add a barrier here? */
		ep->rx_ring[entry].rxstatus = DescOwn;
	}
	return work_done;
}