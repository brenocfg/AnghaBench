#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mwl8k_rx_queue {int /*<<< orphan*/ * rxd; int /*<<< orphan*/  rxd_dma; TYPE_2__* buf; } ;
struct mwl8k_priv {TYPE_1__* rxd_ops; int /*<<< orphan*/  pdev; struct mwl8k_rx_queue* rxq; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/ * skb; } ;
struct TYPE_5__ {int rxd_size; } ;

/* Variables and functions */
 int MWL8K_RX_DESCS ; 
 int /*<<< orphan*/  MWL8K_RX_MAXSZ ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  dma_unmap_addr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mwl8k_rxq_deinit(struct ieee80211_hw *hw, int index)
{
	struct mwl8k_priv *priv = hw->priv;
	struct mwl8k_rx_queue *rxq = priv->rxq + index;
	int i;

	if (rxq->rxd == NULL)
		return;

	for (i = 0; i < MWL8K_RX_DESCS; i++) {
		if (rxq->buf[i].skb != NULL) {
			pci_unmap_single(priv->pdev,
					 dma_unmap_addr(&rxq->buf[i], dma),
					 MWL8K_RX_MAXSZ, PCI_DMA_FROMDEVICE);
			dma_unmap_addr_set(&rxq->buf[i], dma, 0);

			kfree_skb(rxq->buf[i].skb);
			rxq->buf[i].skb = NULL;
		}
	}

	kfree(rxq->buf);
	rxq->buf = NULL;

	pci_free_consistent(priv->pdev,
			    MWL8K_RX_DESCS * priv->rxd_ops->rxd_size,
			    rxq->rxd, rxq->rxd_dma);
	rxq->rxd = NULL;
}