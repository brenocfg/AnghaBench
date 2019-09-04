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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * addr; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; struct ieee80211_local* local; } ;
struct TYPE_4__ {scalar_t__ extra_tx_headroom; } ;
struct ieee80211_local {TYPE_1__ hw; } ;
struct ieee80211_bar {void* start_seq_num; void* control; int /*<<< orphan*/  ta; int /*<<< orphan*/  ra; void* frame_control; } ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ IEEE80211_BAR_CTRL_ACK_POLICY_NORMAL ; 
 scalar_t__ IEEE80211_BAR_CTRL_CBMTID_COMPRESSED_BA ; 
 int IEEE80211_BAR_CTRL_TID_INFO_SHIFT ; 
 int IEEE80211_FTYPE_CTL ; 
 TYPE_3__* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_STYPE_BACK_REQ ; 
 int IEEE80211_TX_CTL_REQ_TX_STATUS ; 
 int IEEE80211_TX_INTFL_DONT_ENCRYPT ; 
 void* cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_tx_skb_tid (struct ieee80211_sub_if_data*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ieee80211_bar* skb_put_zero (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 struct ieee80211_sub_if_data* vif_to_sdata (struct ieee80211_vif*) ; 

void ieee80211_send_bar(struct ieee80211_vif *vif, u8 *ra, u16 tid, u16 ssn)
{
	struct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	struct ieee80211_local *local = sdata->local;
	struct sk_buff *skb;
	struct ieee80211_bar *bar;
	u16 bar_control = 0;

	skb = dev_alloc_skb(sizeof(*bar) + local->hw.extra_tx_headroom);
	if (!skb)
		return;

	skb_reserve(skb, local->hw.extra_tx_headroom);
	bar = skb_put_zero(skb, sizeof(*bar));
	bar->frame_control = cpu_to_le16(IEEE80211_FTYPE_CTL |
					 IEEE80211_STYPE_BACK_REQ);
	memcpy(bar->ra, ra, ETH_ALEN);
	memcpy(bar->ta, sdata->vif.addr, ETH_ALEN);
	bar_control |= (u16)IEEE80211_BAR_CTRL_ACK_POLICY_NORMAL;
	bar_control |= (u16)IEEE80211_BAR_CTRL_CBMTID_COMPRESSED_BA;
	bar_control |= (u16)(tid << IEEE80211_BAR_CTRL_TID_INFO_SHIFT);
	bar->control = cpu_to_le16(bar_control);
	bar->start_seq_num = cpu_to_le16(ssn);

	IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_INTFL_DONT_ENCRYPT |
					IEEE80211_TX_CTL_REQ_TX_STATUS;
	ieee80211_tx_skb_tid(sdata, skb, tid);
}