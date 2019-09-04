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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct TYPE_5__ {int /*<<< orphan*/  is_valid_ack_signal; int /*<<< orphan*/  ack_signal; } ;
struct ieee80211_tx_info {int flags; TYPE_2__ status; int /*<<< orphan*/  ack_frame_id; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  wdev; int /*<<< orphan*/  dev; } ;
struct ieee80211_local {int /*<<< orphan*/  ack_status_lock; int /*<<< orphan*/  ack_status_frames; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; int /*<<< orphan*/  frame_control; } ;
struct TYPE_4__ {int /*<<< orphan*/  cookie; } ;
struct TYPE_6__ {TYPE_1__ ack; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 TYPE_3__* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_INTFL_NL80211_FRAME_TX ; 
 int /*<<< orphan*/  cfg80211_mgmt_tx_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_probe_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_nullfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_qos_nullfunc (int /*<<< orphan*/ ) ; 
 struct ieee80211_sub_if_data* ieee80211_sdata_from_skb (struct ieee80211_local*,struct sk_buff*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_complete_wifi_ack (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ieee80211_report_ack_skb(struct ieee80211_local *local,
				     struct ieee80211_tx_info *info,
				     bool acked, bool dropped)
{
	struct sk_buff *skb;
	unsigned long flags;

	spin_lock_irqsave(&local->ack_status_lock, flags);
	skb = idr_remove(&local->ack_status_frames, info->ack_frame_id);
	spin_unlock_irqrestore(&local->ack_status_lock, flags);

	if (!skb)
		return;

	if (info->flags & IEEE80211_TX_INTFL_NL80211_FRAME_TX) {
		u64 cookie = IEEE80211_SKB_CB(skb)->ack.cookie;
		struct ieee80211_sub_if_data *sdata;
		struct ieee80211_hdr *hdr = (void *)skb->data;

		rcu_read_lock();
		sdata = ieee80211_sdata_from_skb(local, skb);
		if (sdata) {
			if (ieee80211_is_nullfunc(hdr->frame_control) ||
			    ieee80211_is_qos_nullfunc(hdr->frame_control))
				cfg80211_probe_status(sdata->dev, hdr->addr1,
						      cookie, acked,
						      info->status.ack_signal,
						      info->status.is_valid_ack_signal,
						      GFP_ATOMIC);
			else
				cfg80211_mgmt_tx_status(&sdata->wdev, cookie,
							skb->data, skb->len,
							acked, GFP_ATOMIC);
		}
		rcu_read_unlock();

		dev_kfree_skb_any(skb);
	} else if (dropped) {
		dev_kfree_skb_any(skb);
	} else {
		/* consumes skb */
		skb_complete_wifi_ack(skb, acked);
	}
}