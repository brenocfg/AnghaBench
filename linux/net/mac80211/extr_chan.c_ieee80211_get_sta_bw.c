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
struct TYPE_2__ {int /*<<< orphan*/  ht_supported; } ;
struct ieee80211_sta {int bandwidth; TYPE_1__ ht_cap; } ;
typedef  enum nl80211_chan_width { ____Placeholder_nl80211_chan_width } nl80211_chan_width ;

/* Variables and functions */
#define  IEEE80211_STA_RX_BW_160 131 
#define  IEEE80211_STA_RX_BW_20 130 
#define  IEEE80211_STA_RX_BW_40 129 
#define  IEEE80211_STA_RX_BW_80 128 
 int NL80211_CHAN_WIDTH_160 ; 
 int NL80211_CHAN_WIDTH_20 ; 
 int NL80211_CHAN_WIDTH_20_NOHT ; 
 int NL80211_CHAN_WIDTH_40 ; 
 int NL80211_CHAN_WIDTH_80 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

enum nl80211_chan_width ieee80211_get_sta_bw(struct ieee80211_sta *sta)
{
	switch (sta->bandwidth) {
	case IEEE80211_STA_RX_BW_20:
		if (sta->ht_cap.ht_supported)
			return NL80211_CHAN_WIDTH_20;
		else
			return NL80211_CHAN_WIDTH_20_NOHT;
	case IEEE80211_STA_RX_BW_40:
		return NL80211_CHAN_WIDTH_40;
	case IEEE80211_STA_RX_BW_80:
		return NL80211_CHAN_WIDTH_80;
	case IEEE80211_STA_RX_BW_160:
		/*
		 * This applied for both 160 and 80+80. since we use
		 * the returned value to consider degradation of
		 * ctx->conf.min_def, we have to make sure to take
		 * the bigger one (NL80211_CHAN_WIDTH_160).
		 * Otherwise we might try degrading even when not
		 * needed, as the max required sta_bw returned (80+80)
		 * might be smaller than the configured bw (160).
		 */
		return NL80211_CHAN_WIDTH_160;
	default:
		WARN_ON(1);
		return NL80211_CHAN_WIDTH_20;
	}
}