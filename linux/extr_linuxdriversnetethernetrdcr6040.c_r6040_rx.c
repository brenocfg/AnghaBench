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
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  protocol; int /*<<< orphan*/  dev; } ;
struct r6040_private {struct r6040_descriptor* rx_remove_ptr; int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;
struct r6040_descriptor {int status; struct r6040_descriptor* vndescp; struct sk_buff* skb_ptr; int /*<<< orphan*/  buf; scalar_t__ len; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_frame_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 int DSC_OWNER_MAC ; 
 int DSC_RX_ERR ; 
 int DSC_RX_ERR_BUF ; 
 int DSC_RX_ERR_CRC ; 
 int DSC_RX_ERR_DRI ; 
 int DSC_RX_ERR_LONG ; 
 int DSC_RX_ERR_RUNT ; 
 int /*<<< orphan*/  MAX_BUF_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 struct r6040_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r6040_rx(struct net_device *dev, int limit)
{
	struct r6040_private *priv = netdev_priv(dev);
	struct r6040_descriptor *descptr = priv->rx_remove_ptr;
	struct sk_buff *skb_ptr, *new_skb;
	int count = 0;
	u16 err;

	/* Limit not reached and the descriptor belongs to the CPU */
	while (count < limit && !(descptr->status & DSC_OWNER_MAC)) {
		/* Read the descriptor status */
		err = descptr->status;
		/* Global error status set */
		if (err & DSC_RX_ERR) {
			/* RX dribble */
			if (err & DSC_RX_ERR_DRI)
				dev->stats.rx_frame_errors++;
			/* Buffer length exceeded */
			if (err & DSC_RX_ERR_BUF)
				dev->stats.rx_length_errors++;
			/* Packet too long */
			if (err & DSC_RX_ERR_LONG)
				dev->stats.rx_length_errors++;
			/* Packet < 64 bytes */
			if (err & DSC_RX_ERR_RUNT)
				dev->stats.rx_length_errors++;
			/* CRC error */
			if (err & DSC_RX_ERR_CRC) {
				spin_lock(&priv->lock);
				dev->stats.rx_crc_errors++;
				spin_unlock(&priv->lock);
			}
			goto next_descr;
		}

		/* Packet successfully received */
		new_skb = netdev_alloc_skb(dev, MAX_BUF_SIZE);
		if (!new_skb) {
			dev->stats.rx_dropped++;
			goto next_descr;
		}
		skb_ptr = descptr->skb_ptr;
		skb_ptr->dev = priv->dev;

		/* Do not count the CRC */
		skb_put(skb_ptr, descptr->len - 4);
		pci_unmap_single(priv->pdev, le32_to_cpu(descptr->buf),
					MAX_BUF_SIZE, PCI_DMA_FROMDEVICE);
		skb_ptr->protocol = eth_type_trans(skb_ptr, priv->dev);

		/* Send to upper layer */
		netif_receive_skb(skb_ptr);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += descptr->len - 4;

		/* put new skb into descriptor */
		descptr->skb_ptr = new_skb;
		descptr->buf = cpu_to_le32(pci_map_single(priv->pdev,
						descptr->skb_ptr->data,
					MAX_BUF_SIZE, PCI_DMA_FROMDEVICE));

next_descr:
		/* put the descriptor back to the MAC */
		descptr->status = DSC_OWNER_MAC;
		descptr = descptr->vndescp;
		count++;
	}
	priv->rx_remove_ptr = descptr;

	return count;
}