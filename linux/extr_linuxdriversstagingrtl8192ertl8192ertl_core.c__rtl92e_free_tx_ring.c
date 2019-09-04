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
struct tx_desc {int /*<<< orphan*/  TxBuffAddr; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct rtl8192_tx_ring {size_t idx; int entries; struct tx_desc* desc; int /*<<< orphan*/  dma; int /*<<< orphan*/  queue; } ;
struct r8192_priv {int /*<<< orphan*/  pdev; struct rtl8192_tx_ring* tx_ring; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,struct tx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _rtl92e_free_tx_ring(struct net_device *dev, unsigned int prio)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	struct rtl8192_tx_ring *ring = &priv->tx_ring[prio];

	while (skb_queue_len(&ring->queue)) {
		struct tx_desc *entry = &ring->desc[ring->idx];
		struct sk_buff *skb = __skb_dequeue(&ring->queue);

		pci_unmap_single(priv->pdev, entry->TxBuffAddr,
			skb->len, PCI_DMA_TODEVICE);
		kfree_skb(skb);
		ring->idx = (ring->idx + 1) % ring->entries;
	}

	pci_free_consistent(priv->pdev, sizeof(*ring->desc) * ring->entries,
	ring->desc, ring->dma);
	ring->desc = NULL;
}