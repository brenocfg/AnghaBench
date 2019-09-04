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
typedef  enum nl80211_chan_width { ____Placeholder_nl80211_chan_width } nl80211_chan_width ;
typedef  enum ieee80211_sta_rx_bandwidth { ____Placeholder_ieee80211_sta_rx_bandwidth } ieee80211_sta_rx_bandwidth ;

/* Variables and functions */
 int IEEE80211_STA_RX_BW_160 ; 
 int IEEE80211_STA_RX_BW_20 ; 
 int IEEE80211_STA_RX_BW_40 ; 
 int IEEE80211_STA_RX_BW_80 ; 
#define  NL80211_CHAN_WIDTH_160 133 
#define  NL80211_CHAN_WIDTH_20 132 
#define  NL80211_CHAN_WIDTH_20_NOHT 131 
#define  NL80211_CHAN_WIDTH_40 130 
#define  NL80211_CHAN_WIDTH_80 129 
#define  NL80211_CHAN_WIDTH_80P80 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

enum ieee80211_sta_rx_bandwidth
ieee80211_chan_width_to_rx_bw(enum nl80211_chan_width width)
{
	switch (width) {
	case NL80211_CHAN_WIDTH_20_NOHT:
	case NL80211_CHAN_WIDTH_20:
		return IEEE80211_STA_RX_BW_20;
	case NL80211_CHAN_WIDTH_40:
		return IEEE80211_STA_RX_BW_40;
	case NL80211_CHAN_WIDTH_80:
		return IEEE80211_STA_RX_BW_80;
	case NL80211_CHAN_WIDTH_160:
	case NL80211_CHAN_WIDTH_80P80:
		return IEEE80211_STA_RX_BW_160;
	default:
		WARN_ON_ONCE(1);
		return IEEE80211_STA_RX_BW_20;
	}
}