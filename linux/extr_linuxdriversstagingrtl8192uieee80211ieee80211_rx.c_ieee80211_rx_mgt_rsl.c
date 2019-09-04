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
struct rtl_80211_hdr_4addr {int /*<<< orphan*/  frame_ctl; } ;
struct ieee80211_rx_stats {int dummy; } ;
struct ieee80211_probe_response {int dummy; } ;
struct ieee80211_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_DEBUG_MGMT (char*,int) ; 
 int /*<<< orphan*/  IEEE80211_DEBUG_SCAN (char*) ; 
#define  IEEE80211_STYPE_BEACON 129 
#define  IEEE80211_STYPE_PROBE_RESP 128 
 int WLAN_FC_GET_STYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_process_probe_response (struct ieee80211_device*,struct ieee80211_probe_response*,struct ieee80211_rx_stats*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

void ieee80211_rx_mgt(struct ieee80211_device *ieee,
		      struct rtl_80211_hdr_4addr *header,
		      struct ieee80211_rx_stats *stats)
{
	switch (WLAN_FC_GET_STYPE(le16_to_cpu(header->frame_ctl))) {

	case IEEE80211_STYPE_BEACON:
		IEEE80211_DEBUG_MGMT("received BEACON (%d)\n",
			WLAN_FC_GET_STYPE(le16_to_cpu(header->frame_ctl)));
		IEEE80211_DEBUG_SCAN("Beacon\n");
		ieee80211_process_probe_response(
			ieee, (struct ieee80211_probe_response *)header, stats);
		break;

	case IEEE80211_STYPE_PROBE_RESP:
		IEEE80211_DEBUG_MGMT("received PROBE RESPONSE (%d)\n",
			WLAN_FC_GET_STYPE(le16_to_cpu(header->frame_ctl)));
		IEEE80211_DEBUG_SCAN("Probe response\n");
		ieee80211_process_probe_response(
			ieee, (struct ieee80211_probe_response *)header, stats);
		break;

	}
}