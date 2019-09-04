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
typedef  int u8 ;
struct sk_buff {int priority; scalar_t__ data; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct ath10k_skb_cb {int flags; } ;

/* Variables and functions */
 struct ath10k_skb_cb* ATH10K_SKB_CB (struct sk_buff*) ; 
 int ATH10K_SKB_F_QOS ; 
 int HTT_DATA_TX_EXT_TID_MGMT ; 
 int HTT_DATA_TX_EXT_TID_NON_QOS_MCAST_BCAST ; 
 int IEEE80211_QOS_CTL_TID_MASK ; 
 scalar_t__ ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 ath10k_htt_tx_get_tid(struct sk_buff *skb, bool is_eth)
{
	struct ieee80211_hdr *hdr = (void *)skb->data;
	struct ath10k_skb_cb *cb = ATH10K_SKB_CB(skb);

	if (!is_eth && ieee80211_is_mgmt(hdr->frame_control))
		return HTT_DATA_TX_EXT_TID_MGMT;
	else if (cb->flags & ATH10K_SKB_F_QOS)
		return skb->priority & IEEE80211_QOS_CTL_TID_MASK;
	else
		return HTT_DATA_TX_EXT_TID_NON_QOS_MCAST_BCAST;
}