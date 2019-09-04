#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct rtl_tx_desc {int dummy; } ;
struct rtl_tcb_desc {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  txbytesunicast; int /*<<< orphan*/  txbytesbroadcast; int /*<<< orphan*/  txbytesmulticast; } ;
struct TYPE_5__ {scalar_t__ sw_ps_enabled; } ;
struct rtl_priv {TYPE_4__* cfg; TYPE_2__ stats; TYPE_1__ psc; } ;
struct ieee80211_tx_info {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/ * addr1; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_8__ {TYPE_3__* ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* led_control ) (struct ieee80211_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* fill_tx_desc ) (struct ieee80211_hw*,struct ieee80211_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ieee80211_tx_info*,struct ieee80211_sta*,struct sk_buff*,int /*<<< orphan*/ ,struct rtl_tcb_desc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_SEND ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  IEEE80211_FCTL_PM ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  LED_CTL_TX ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_has_pm (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_auth (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_nullfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct rtl_tcb_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_action_proc (struct ieee80211_hw*,struct sk_buff*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,struct ieee80211_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ieee80211_tx_info*,struct ieee80211_sta*,struct sk_buff*,int /*<<< orphan*/ ,struct rtl_tcb_desc*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _rtl_usb_tx_preprocess(struct ieee80211_hw *hw,
				   struct ieee80211_sta *sta,
				   struct sk_buff *skb,
				   u16 hw_queue)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct rtl_tx_desc *pdesc = NULL;
	struct rtl_tcb_desc tcb_desc;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)(skb->data);
	__le16 fc = hdr->frame_control;
	u8 *pda_addr = hdr->addr1;

	memset(&tcb_desc, 0, sizeof(struct rtl_tcb_desc));
	if (ieee80211_is_auth(fc)) {
		RT_TRACE(rtlpriv, COMP_SEND, DBG_DMESG, "MAC80211_LINKING\n");
	}

	if (rtlpriv->psc.sw_ps_enabled) {
		if (ieee80211_is_data(fc) && !ieee80211_is_nullfunc(fc) &&
		    !ieee80211_has_pm(fc))
			hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_PM);
	}

	rtl_action_proc(hw, skb, true);
	if (is_multicast_ether_addr(pda_addr))
		rtlpriv->stats.txbytesmulticast += skb->len;
	else if (is_broadcast_ether_addr(pda_addr))
		rtlpriv->stats.txbytesbroadcast += skb->len;
	else
		rtlpriv->stats.txbytesunicast += skb->len;
	rtlpriv->cfg->ops->fill_tx_desc(hw, hdr, (u8 *)pdesc, NULL, info, sta, skb,
					hw_queue, &tcb_desc);
	if (ieee80211_is_data(fc))
		rtlpriv->cfg->ops->led_control(hw, LED_CTL_TX);
}