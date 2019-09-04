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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct rtl_priv {scalar_t__ use_new_trx_flow; TYPE_2__* cfg; } ;
struct rtl_pci {int /*<<< orphan*/  pdev; struct rtl8192_tx_ring* tx_ring; } ;
struct rtl8192_tx_ring {size_t idx; int entries; int /*<<< orphan*/ * buffer_desc; int /*<<< orphan*/  buffer_desc_dma; int /*<<< orphan*/ * desc; int /*<<< orphan*/  dma; int /*<<< orphan*/  queue; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_desc ) (struct ieee80211_hw*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HW_DESC_TXBUFF_ADDR ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _rtl_pci_free_tx_ring(struct ieee80211_hw *hw,
				  unsigned int prio)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl8192_tx_ring *ring = &rtlpci->tx_ring[prio];

	/* free every desc in this ring */
	while (skb_queue_len(&ring->queue)) {
		u8 *entry;
		struct sk_buff *skb = __skb_dequeue(&ring->queue);

		if (rtlpriv->use_new_trx_flow)
			entry = (u8 *)(&ring->buffer_desc[ring->idx]);
		else
			entry = (u8 *)(&ring->desc[ring->idx]);

		pci_unmap_single(rtlpci->pdev,
				 rtlpriv->cfg->ops->get_desc(hw, (u8 *)entry,
						   true,
						   HW_DESC_TXBUFF_ADDR),
				 skb->len, PCI_DMA_TODEVICE);
		kfree_skb(skb);
		ring->idx = (ring->idx + 1) % ring->entries;
	}

	/* free dma of this ring */
	pci_free_consistent(rtlpci->pdev,
			    sizeof(*ring->desc) * ring->entries,
			    ring->desc, ring->dma);
	ring->desc = NULL;
	if (rtlpriv->use_new_trx_flow) {
		pci_free_consistent(rtlpci->pdev,
				    sizeof(*ring->buffer_desc) * ring->entries,
				    ring->buffer_desc, ring->buffer_desc_dma);
		ring->buffer_desc = NULL;
	}
}