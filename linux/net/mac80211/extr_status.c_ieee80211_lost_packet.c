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
struct TYPE_8__ {scalar_t__ lost_packets; scalar_t__ last_tdls_pkt_time; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; scalar_t__ tdls; } ;
struct sta_info {TYPE_4__ status_stats; TYPE_3__ sta; TYPE_2__* sdata; TYPE_1__* local; } ;
struct ieee80211_tx_info {int flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int IEEE80211_TX_STAT_AMPDU ; 
 int /*<<< orphan*/  REPORTS_LOW_ACK ; 
 scalar_t__ STA_LOST_PKT_THRESHOLD ; 
 scalar_t__ STA_LOST_TDLS_PKT_THRESHOLD ; 
 scalar_t__ STA_LOST_TDLS_PKT_TIME ; 
 int /*<<< orphan*/  cfg80211_cqm_pktloss_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ieee80211_lost_packet(struct sta_info *sta,
				  struct ieee80211_tx_info *info)
{
	/* If driver relies on its own algorithm for station kickout, skip
	 * mac80211 packet loss mechanism.
	 */
	if (ieee80211_hw_check(&sta->local->hw, REPORTS_LOW_ACK))
		return;

	/* This packet was aggregated but doesn't carry status info */
	if ((info->flags & IEEE80211_TX_CTL_AMPDU) &&
	    !(info->flags & IEEE80211_TX_STAT_AMPDU))
		return;

	sta->status_stats.lost_packets++;
	if (!sta->sta.tdls &&
	    sta->status_stats.lost_packets < STA_LOST_PKT_THRESHOLD)
		return;

	/*
	 * If we're in TDLS mode, make sure that all STA_LOST_TDLS_PKT_THRESHOLD
	 * of the last packets were lost, and that no ACK was received in the
	 * last STA_LOST_TDLS_PKT_TIME ms, before triggering the CQM packet-loss
	 * mechanism.
	 */
	if (sta->sta.tdls &&
	    (sta->status_stats.lost_packets < STA_LOST_TDLS_PKT_THRESHOLD ||
	     time_before(jiffies,
			 sta->status_stats.last_tdls_pkt_time +
			 STA_LOST_TDLS_PKT_TIME)))
		return;

	cfg80211_cqm_pktloss_notify(sta->sdata->dev, sta->sta.addr,
				    sta->status_stats.lost_packets, GFP_ATOMIC);
	sta->status_stats.lost_packets = 0;
}