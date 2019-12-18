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
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_sta_reset_conn_monitor (struct ieee80211_sub_if_data*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 

void ieee80211_sta_rx_notify(struct ieee80211_sub_if_data *sdata,
			     struct ieee80211_hdr *hdr)
{
	/*
	 * We can postpone the mgd.timer whenever receiving unicast frames
	 * from AP because we know that the connection is working both ways
	 * at that time. But multicast frames (and hence also beacons) must
	 * be ignored here, because we need to trigger the timer during
	 * data idle periods for sending the periodic probe request to the
	 * AP we're connected to.
	 */
	if (is_multicast_ether_addr(hdr->addr1))
		return;

	ieee80211_sta_reset_conn_monitor(sdata);
}