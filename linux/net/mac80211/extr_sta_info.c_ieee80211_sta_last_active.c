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
struct TYPE_2__ {unsigned long last_ack; } ;
struct sta_info {TYPE_1__ status_stats; } ;
struct ieee80211_sta_rx_stats {unsigned long last_rx; } ;

/* Variables and functions */
 struct ieee80211_sta_rx_stats* sta_get_last_rx_stats (struct sta_info*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

unsigned long ieee80211_sta_last_active(struct sta_info *sta)
{
	struct ieee80211_sta_rx_stats *stats = sta_get_last_rx_stats(sta);

	if (!sta->status_stats.last_ack ||
	    time_after(stats->last_rx, sta->status_stats.last_ack))
		return stats->last_rx;
	return sta->status_stats.last_ack;
}