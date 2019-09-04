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
struct sta_info {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  addr1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_get_qos_ctl (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_mpsp_trigger_process (int /*<<< orphan*/ ,struct sta_info*,int,int) ; 
 scalar_t__ is_unicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_set_sta_nonpeer_pm (struct sta_info*,struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  mps_set_sta_peer_pm (struct sta_info*,struct ieee80211_hdr*) ; 

void ieee80211_mps_rx_h_sta_process(struct sta_info *sta,
				    struct ieee80211_hdr *hdr)
{
	if (is_unicast_ether_addr(hdr->addr1) &&
	    ieee80211_is_data_qos(hdr->frame_control)) {
		/*
		 * individually addressed QoS Data/Null frames contain
		 * peer link-specific PS mode towards the local STA
		 */
		mps_set_sta_peer_pm(sta, hdr);

		/* check for mesh Peer Service Period trigger frames */
		ieee80211_mpsp_trigger_process(ieee80211_get_qos_ctl(hdr),
					       sta, false, false);
	} else {
		/*
		 * can only determine non-peer PS mode
		 * (see IEEE802.11-2012 8.2.4.1.7)
		 */
		mps_set_sta_nonpeer_pm(sta, hdr);
	}
}