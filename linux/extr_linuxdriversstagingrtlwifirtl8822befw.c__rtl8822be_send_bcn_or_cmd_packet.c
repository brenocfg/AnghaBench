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
typedef  size_t u8 ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct rtl_tx_desc {int dummy; } ;
struct rtl_tx_buffer_desc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq_th_lock; } ;
struct rtl_priv {TYPE_3__* cfg; TYPE_1__ locks; } ;
struct rtl_pci {int /*<<< orphan*/  pdev; struct rtl8192_tx_ring* tx_ring; } ;
struct rtl8192_tx_ring {size_t cur_tx_wp; int /*<<< orphan*/  queue; struct rtl_tx_buffer_desc* buffer_desc; struct rtl_tx_desc* desc; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {scalar_t__ (* get_available_desc ) (struct ieee80211_hw*,size_t) ;int /*<<< orphan*/  (* tx_polling ) (struct ieee80211_hw*,size_t) ;int /*<<< orphan*/  (* set_desc ) (struct ieee80211_hw*,size_t*,int,int /*<<< orphan*/ ,size_t*) ;int /*<<< orphan*/  (* fill_tx_special_desc ) (struct ieee80211_hw*,size_t*,size_t*,struct sk_buff*,size_t) ;int /*<<< orphan*/  (* get_desc ) (struct ieee80211_hw*,size_t*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t BEACON_QUEUE ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  DBG_WARNING ; 
 size_t H2C_QUEUE ; 
 int /*<<< orphan*/  HW_DESC_OWN ; 
 int /*<<< orphan*/  HW_DESC_TXBUFF_ADDR ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,size_t*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct ieee80211_hw*,size_t) ; 
 int /*<<< orphan*/  stub3 (struct ieee80211_hw*,size_t*,size_t*,struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  stub4 (struct ieee80211_hw*,size_t*,int,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  stub5 (struct ieee80211_hw*,size_t) ; 

__attribute__((used)) static bool _rtl8822be_send_bcn_or_cmd_packet(struct ieee80211_hw *hw,
					      struct sk_buff *skb, u8 hw_queue)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl8192_tx_ring *ring;
	struct rtl_tx_desc *pdesc;
	struct rtl_tx_buffer_desc *pbd_desc;
	unsigned long flags;
	struct sk_buff *pskb = NULL;
	u8 *pdesc_or_bddesc;
	dma_addr_t dma_addr;

	if (hw_queue != BEACON_QUEUE && hw_queue != H2C_QUEUE)
		return false;

	ring = &rtlpci->tx_ring[hw_queue];

	spin_lock_irqsave(&rtlpriv->locks.irq_th_lock, flags);

	if (hw_queue == BEACON_QUEUE) {
		pdesc = &ring->desc[0];
		pbd_desc = &ring->buffer_desc[0];
		pdesc_or_bddesc = (u8 *)pbd_desc;

		/* free previous beacon queue */
		pskb = __skb_dequeue(&ring->queue);

		if (!pskb)
			goto free_prev_skb_done;

		dma_addr = rtlpriv->cfg->ops->get_desc(
				hw, (u8 *)pbd_desc, true, HW_DESC_TXBUFF_ADDR);

		pci_unmap_single(rtlpci->pdev, dma_addr, pskb->len,
				 PCI_DMA_TODEVICE);
		kfree_skb(pskb);

free_prev_skb_done:
		;

	} else { /* hw_queue == TXCMD_QUEUE */
		if (rtlpriv->cfg->ops->get_available_desc(hw, hw_queue) == 0) {
			RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
				 "get_available_desc fail hw_queue=%d\n",
				 hw_queue);
			spin_unlock_irqrestore(&rtlpriv->locks.irq_th_lock,
					       flags);
			return false;
		}

		pdesc = &ring->desc[ring->cur_tx_wp];
		pbd_desc = &ring->buffer_desc[ring->cur_tx_wp];
		pdesc_or_bddesc = (u8 *)pdesc;
	}

	rtlpriv->cfg->ops->fill_tx_special_desc(hw, (u8 *)pdesc, (u8 *)pbd_desc,
						skb, hw_queue);

	__skb_queue_tail(&ring->queue, skb);

	rtlpriv->cfg->ops->set_desc(hw, (u8 *)pdesc_or_bddesc, true,
				    HW_DESC_OWN, (u8 *)&hw_queue);

	spin_unlock_irqrestore(&rtlpriv->locks.irq_th_lock, flags);

	rtlpriv->cfg->ops->tx_polling(hw, hw_queue);

	return true;
}