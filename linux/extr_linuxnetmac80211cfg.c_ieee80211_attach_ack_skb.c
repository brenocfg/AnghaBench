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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct ieee80211_local {int /*<<< orphan*/  ack_status_lock; int /*<<< orphan*/  ack_status_frames; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_3__ {int /*<<< orphan*/  cookie; } ;
struct TYPE_4__ {int ack_frame_id; TYPE_1__ ack; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 TYPE_2__* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct sk_buff*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_mgmt_tx_cookie (struct ieee80211_local*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ieee80211_attach_ack_skb(struct ieee80211_local *local, struct sk_buff *skb,
			     u64 *cookie, gfp_t gfp)
{
	unsigned long spin_flags;
	struct sk_buff *ack_skb;
	int id;

	ack_skb = skb_copy(skb, gfp);
	if (!ack_skb)
		return -ENOMEM;

	spin_lock_irqsave(&local->ack_status_lock, spin_flags);
	id = idr_alloc(&local->ack_status_frames, ack_skb,
		       1, 0x10000, GFP_ATOMIC);
	spin_unlock_irqrestore(&local->ack_status_lock, spin_flags);

	if (id < 0) {
		kfree_skb(ack_skb);
		return -ENOMEM;
	}

	IEEE80211_SKB_CB(skb)->ack_frame_id = id;

	*cookie = ieee80211_mgmt_tx_cookie(local);
	IEEE80211_SKB_CB(ack_skb)->ack.cookie = *cookie;

	return 0;
}