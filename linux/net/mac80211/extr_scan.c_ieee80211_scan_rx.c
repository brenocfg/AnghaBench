#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_rx_status {int /*<<< orphan*/  freq; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  da; int /*<<< orphan*/  frame_control; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {TYPE_1__ hw; int /*<<< orphan*/  sched_scan_req; int /*<<< orphan*/  scan_req; int /*<<< orphan*/  sched_scan_sdata; int /*<<< orphan*/  scan_sdata; } ;
struct ieee80211_channel {int flags; } ;
struct ieee80211_bss {int dummy; } ;
struct cfg80211_sched_scan_request {int /*<<< orphan*/  flags; } ;
struct cfg80211_scan_request {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int IEEE80211_CHAN_DISABLED ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 struct ieee80211_bss* ieee80211_bss_info_update (struct ieee80211_local*,struct ieee80211_rx_status*,struct ieee80211_mgmt*,int,struct ieee80211_channel*) ; 
 struct ieee80211_channel* ieee80211_get_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_rx_bss_put (struct ieee80211_local*,struct ieee80211_bss*) ; 
 int /*<<< orphan*/  ieee80211_scan_accept_presp (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 

void ieee80211_scan_rx(struct ieee80211_local *local, struct sk_buff *skb)
{
	struct ieee80211_rx_status *rx_status = IEEE80211_SKB_RXCB(skb);
	struct ieee80211_sub_if_data *sdata1, *sdata2;
	struct ieee80211_mgmt *mgmt = (void *)skb->data;
	struct ieee80211_bss *bss;
	struct ieee80211_channel *channel;

	if (skb->len < 24 ||
	    (!ieee80211_is_probe_resp(mgmt->frame_control) &&
	     !ieee80211_is_beacon(mgmt->frame_control)))
		return;

	sdata1 = rcu_dereference(local->scan_sdata);
	sdata2 = rcu_dereference(local->sched_scan_sdata);

	if (likely(!sdata1 && !sdata2))
		return;

	if (ieee80211_is_probe_resp(mgmt->frame_control)) {
		struct cfg80211_scan_request *scan_req;
		struct cfg80211_sched_scan_request *sched_scan_req;
		u32 scan_req_flags = 0, sched_scan_req_flags = 0;

		scan_req = rcu_dereference(local->scan_req);
		sched_scan_req = rcu_dereference(local->sched_scan_req);

		if (scan_req)
			scan_req_flags = scan_req->flags;

		if (sched_scan_req)
			sched_scan_req_flags = sched_scan_req->flags;

		/* ignore ProbeResp to foreign address or non-bcast (OCE)
		 * unless scanning with randomised address
		 */
		if (!ieee80211_scan_accept_presp(sdata1, scan_req_flags,
						 mgmt->da) &&
		    !ieee80211_scan_accept_presp(sdata2, sched_scan_req_flags,
						 mgmt->da))
			return;
	}

	channel = ieee80211_get_channel(local->hw.wiphy, rx_status->freq);

	if (!channel || channel->flags & IEEE80211_CHAN_DISABLED)
		return;

	bss = ieee80211_bss_info_update(local, rx_status,
					mgmt, skb->len,
					channel);
	if (bss)
		ieee80211_rx_bss_put(local, bss);
}