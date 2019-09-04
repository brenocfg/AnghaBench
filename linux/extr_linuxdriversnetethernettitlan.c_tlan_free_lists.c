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
struct tlan_priv {int /*<<< orphan*/  pci_dev; struct tlan_list* rx_list; struct tlan_list* tx_list; } ;
struct tlan_list {TYPE_1__* buffer; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ address; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  TLAN_MAX_FRAME_SIZE ; 
 scalar_t__ TLAN_MIN_FRAME_SIZE ; 
 int TLAN_NUM_RX_LISTS ; 
 int TLAN_NUM_TX_LISTS ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,unsigned int) ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* tlan_get_skb (struct tlan_list*) ; 

__attribute__((used)) static void tlan_free_lists(struct net_device *dev)
{
	struct tlan_priv *priv = netdev_priv(dev);
	int		i;
	struct tlan_list	*list;
	struct sk_buff	*skb;

	for (i = 0; i < TLAN_NUM_TX_LISTS; i++) {
		list = priv->tx_list + i;
		skb = tlan_get_skb(list);
		if (skb) {
			pci_unmap_single(
				priv->pci_dev,
				list->buffer[0].address,
				max(skb->len,
				    (unsigned int)TLAN_MIN_FRAME_SIZE),
				PCI_DMA_TODEVICE);
			dev_kfree_skb_any(skb);
			list->buffer[8].address = 0;
			list->buffer[9].address = 0;
		}
	}

	for (i = 0; i < TLAN_NUM_RX_LISTS; i++) {
		list = priv->rx_list + i;
		skb = tlan_get_skb(list);
		if (skb) {
			pci_unmap_single(priv->pci_dev,
					 list->buffer[0].address,
					 TLAN_MAX_FRAME_SIZE,
					 PCI_DMA_FROMDEVICE);
			dev_kfree_skb_any(skb);
			list->buffer[8].address = 0;
			list->buffer[9].address = 0;
		}
	}
}