#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  data; } ;
struct r6040_private {int /*<<< orphan*/  pdev; struct r6040_descriptor* rx_ring; int /*<<< orphan*/  rx_ring_dma; struct r6040_descriptor* rx_insert_ptr; struct r6040_descriptor* rx_remove_ptr; } ;
struct r6040_descriptor {struct r6040_descriptor* vndescp; int /*<<< orphan*/  status; struct sk_buff* skb_ptr; int /*<<< orphan*/  buf; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSC_OWNER_MAC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MAX_BUF_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  RX_DCNT ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 struct r6040_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r6040_free_rxbufs (struct net_device*) ; 
 int /*<<< orphan*/  r6040_init_ring_desc (struct r6040_descriptor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r6040_alloc_rxbufs(struct net_device *dev)
{
	struct r6040_private *lp = netdev_priv(dev);
	struct r6040_descriptor *desc;
	struct sk_buff *skb;
	int rc;

	lp->rx_remove_ptr = lp->rx_insert_ptr = lp->rx_ring;
	r6040_init_ring_desc(lp->rx_ring, lp->rx_ring_dma, RX_DCNT);

	/* Allocate skbs for the rx descriptors */
	desc = lp->rx_ring;
	do {
		skb = netdev_alloc_skb(dev, MAX_BUF_SIZE);
		if (!skb) {
			rc = -ENOMEM;
			goto err_exit;
		}
		desc->skb_ptr = skb;
		desc->buf = cpu_to_le32(pci_map_single(lp->pdev,
					desc->skb_ptr->data,
					MAX_BUF_SIZE, PCI_DMA_FROMDEVICE));
		desc->status = DSC_OWNER_MAC;
		desc = desc->vndescp;
	} while (desc != lp->rx_ring);

	return 0;

err_exit:
	/* Deallocate all previously allocated skbs */
	r6040_free_rxbufs(dev);
	return rc;
}