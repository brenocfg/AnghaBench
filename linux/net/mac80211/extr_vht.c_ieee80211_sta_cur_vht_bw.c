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
struct sta_info {int /*<<< orphan*/  cur_max_bandwidth; struct ieee80211_sub_if_data* sdata; } ;
struct TYPE_4__ {int width; } ;
struct TYPE_5__ {TYPE_1__ chandef; } ;
struct TYPE_6__ {TYPE_2__ bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_3__ vif; } ;
typedef  enum nl80211_chan_width { ____Placeholder_nl80211_chan_width } nl80211_chan_width ;
typedef  enum ieee80211_sta_rx_bandwidth { ____Placeholder_ieee80211_sta_rx_bandwidth } ieee80211_sta_rx_bandwidth ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_STA_TDLS_PEER ; 
 int /*<<< orphan*/  WLAN_STA_TDLS_WIDER_BW ; 
 int /*<<< orphan*/  ieee80211_chan_width_to_rx_bw (int) ; 
 int ieee80211_sta_cap_rx_bw (struct sta_info*) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

enum ieee80211_sta_rx_bandwidth ieee80211_sta_cur_vht_bw(struct sta_info *sta)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	enum ieee80211_sta_rx_bandwidth bw;
	enum nl80211_chan_width bss_width = sdata->vif.bss_conf.chandef.width;

	bw = ieee80211_sta_cap_rx_bw(sta);
	bw = min(bw, sta->cur_max_bandwidth);

	/* Don't consider AP's bandwidth for TDLS peers, section 11.23.1 of
	 * IEEE80211-2016 specification makes higher bandwidth operation
	 * possible on the TDLS link if the peers have wider bandwidth
	 * capability.
	 */
	if (test_sta_flag(sta, WLAN_STA_TDLS_PEER) &&
	    test_sta_flag(sta, WLAN_STA_TDLS_WIDER_BW))
		return bw;

	bw = min(bw, ieee80211_chan_width_to_rx_bw(bss_width));

	return bw;
}