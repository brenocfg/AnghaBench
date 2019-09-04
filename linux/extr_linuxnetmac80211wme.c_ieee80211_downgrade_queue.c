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
typedef  int u16 ;
struct sta_info {scalar_t__ reserved_tid; } ;
struct sk_buff {size_t priority; } ;
struct ieee80211_if_managed {TYPE_1__* tx_tspec; } ;
struct TYPE_4__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {int wmm_acm; TYPE_2__ u; } ;
struct TYPE_3__ {scalar_t__ up; scalar_t__ admitted_time; } ;

/* Variables and functions */
 int BIT (size_t) ; 
 scalar_t__ ieee80211_fix_reserved_tid (scalar_t__) ; 
 int* ieee802_1d_to_ac ; 
 scalar_t__ wme_downgrade_ac (struct sk_buff*) ; 

__attribute__((used)) static u16 ieee80211_downgrade_queue(struct ieee80211_sub_if_data *sdata,
				     struct sta_info *sta, struct sk_buff *skb)
{
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;

	/* in case we are a client verify acm is not set for this ac */
	while (sdata->wmm_acm & BIT(skb->priority)) {
		int ac = ieee802_1d_to_ac[skb->priority];

		if (ifmgd->tx_tspec[ac].admitted_time &&
		    skb->priority == ifmgd->tx_tspec[ac].up)
			return ac;

		if (wme_downgrade_ac(skb)) {
			/*
			 * This should not really happen. The AP has marked all
			 * lower ACs to require admission control which is not
			 * a reasonable configuration. Allow the frame to be
			 * transmitted using AC_BK as a workaround.
			 */
			break;
		}
	}

	/* Check to see if this is a reserved TID */
	if (sta && sta->reserved_tid == skb->priority)
		skb->priority = ieee80211_fix_reserved_tid(skb->priority);

	/* look up which queue to use for frames with this 1d tag */
	return ieee802_1d_to_ac[skb->priority];
}