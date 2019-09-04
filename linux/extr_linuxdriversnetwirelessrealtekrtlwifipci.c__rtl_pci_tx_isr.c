#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct sk_buff {scalar_t__ data; int /*<<< orphan*/  len; } ;
struct TYPE_11__ {int num_rx_inperiod; int num_tx_inperiod; int /*<<< orphan*/ * tidtx_inperiod; } ;
struct TYPE_16__ {int state_inap; } ;
struct TYPE_15__ {int offchan_delay; } ;
struct TYPE_14__ {scalar_t__ earlymode_enable; } ;
struct rtl_priv {TYPE_10__ link_info; TYPE_5__ psc; TYPE_4__ mac80211; TYPE_3__ rtlhal; TYPE_2__* cfg; scalar_t__ use_new_trx_flow; } ;
struct rtl_pci {int /*<<< orphan*/  pdev; struct rtl8192_tx_ring* tx_ring; } ;
struct rtl8192_tx_ring {size_t idx; int entries; int /*<<< orphan*/  queue; int /*<<< orphan*/ * desc; int /*<<< orphan*/ * buffer_desc; } ;
struct ieee80211_tx_info {int /*<<< orphan*/  flags; } ;
struct TYPE_17__ {scalar_t__ action; } ;
struct TYPE_18__ {TYPE_6__ ht_smps; } ;
struct TYPE_19__ {TYPE_7__ u; } ;
struct TYPE_20__ {TYPE_8__ action; } ;
struct ieee80211_mgmt {TYPE_9__ u; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_13__ {TYPE_1__* ops; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* get_desc ) (struct ieee80211_hw*,int*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* is_tx_desc_closed ) (struct ieee80211_hw*,int,size_t) ;} ;

/* Variables and functions */
 int COMP_ERR ; 
 int COMP_INTR ; 
 int COMP_SEND ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  EM_HDR_LEN ; 
 int /*<<< orphan*/  HW_DESC_TXBUFF_ADDR ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int TXCMD_QUEUE ; 
 scalar_t__ WLAN_HT_ACTION_SMPS ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ ieee80211_has_pm (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_action (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_nullfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_info_clear_status (struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_wake_queue (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_get_fc (struct sk_buff*) ; 
 int rtl_get_tid (struct sk_buff*) ; 
 int /*<<< orphan*/  rtl_lps_leave (struct ieee80211_hw*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_tx_ackqueue (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int,size_t) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _rtl_pci_tx_isr(struct ieee80211_hw *hw, int prio)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));

	struct rtl8192_tx_ring *ring = &rtlpci->tx_ring[prio];

	while (skb_queue_len(&ring->queue)) {
		struct sk_buff *skb;
		struct ieee80211_tx_info *info;
		__le16 fc;
		u8 tid;
		u8 *entry;

		if (rtlpriv->use_new_trx_flow)
			entry = (u8 *)(&ring->buffer_desc[ring->idx]);
		else
			entry = (u8 *)(&ring->desc[ring->idx]);

		if (!rtlpriv->cfg->ops->is_tx_desc_closed(hw, prio, ring->idx))
			return;
		ring->idx = (ring->idx + 1) % ring->entries;

		skb = __skb_dequeue(&ring->queue);
		pci_unmap_single(rtlpci->pdev,
				 rtlpriv->cfg->ops->
					     get_desc(hw, (u8 *)entry, true,
						      HW_DESC_TXBUFF_ADDR),
				 skb->len, PCI_DMA_TODEVICE);

		/* remove early mode header */
		if (rtlpriv->rtlhal.earlymode_enable)
			skb_pull(skb, EM_HDR_LEN);

		RT_TRACE(rtlpriv, (COMP_INTR | COMP_SEND), DBG_TRACE,
			 "new ring->idx:%d, free: skb_queue_len:%d, free: seq:%x\n",
			 ring->idx,
			 skb_queue_len(&ring->queue),
			 *(u16 *)(skb->data + 22));

		if (prio == TXCMD_QUEUE) {
			dev_kfree_skb(skb);
			goto tx_status_ok;
		}

		/* for sw LPS, just after NULL skb send out, we can
		 * sure AP knows we are sleeping, we should not let
		 * rf sleep
		 */
		fc = rtl_get_fc(skb);
		if (ieee80211_is_nullfunc(fc)) {
			if (ieee80211_has_pm(fc)) {
				rtlpriv->mac80211.offchan_delay = true;
				rtlpriv->psc.state_inap = true;
			} else {
				rtlpriv->psc.state_inap = false;
			}
		}
		if (ieee80211_is_action(fc)) {
			struct ieee80211_mgmt *action_frame =
				(struct ieee80211_mgmt *)skb->data;
			if (action_frame->u.action.u.ht_smps.action ==
			    WLAN_HT_ACTION_SMPS) {
				dev_kfree_skb(skb);
				goto tx_status_ok;
			}
		}

		/* update tid tx pkt num */
		tid = rtl_get_tid(skb);
		if (tid <= 7)
			rtlpriv->link_info.tidtx_inperiod[tid]++;

		info = IEEE80211_SKB_CB(skb);

		if (likely(!ieee80211_is_nullfunc(fc))) {
			ieee80211_tx_info_clear_status(info);
			info->flags |= IEEE80211_TX_STAT_ACK;
			/*info->status.rates[0].count = 1; */
			ieee80211_tx_status_irqsafe(hw, skb);
		} else {
			rtl_tx_ackqueue(hw, skb);
		}

		if ((ring->entries - skb_queue_len(&ring->queue)) <= 4) {
			RT_TRACE(rtlpriv, COMP_ERR, DBG_DMESG,
				 "more desc left, wake skb_queue@%d, ring->idx = %d, skb_queue_len = 0x%x\n",
				 prio, ring->idx,
				 skb_queue_len(&ring->queue));

			ieee80211_wake_queue(hw, skb_get_queue_mapping(skb));
		}
tx_status_ok:
		skb = NULL;
	}

	if (((rtlpriv->link_info.num_rx_inperiod +
	      rtlpriv->link_info.num_tx_inperiod) > 8) ||
	      rtlpriv->link_info.num_rx_inperiod > 2)
		rtl_lps_leave(hw);
}