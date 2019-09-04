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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_sta {int bandwidth; } ;

/* Variables and functions */
#define  IEEE80211_STA_RX_BW_160 131 
#define  IEEE80211_STA_RX_BW_20 130 
#define  IEEE80211_STA_RX_BW_40 129 
#define  IEEE80211_STA_RX_BW_80 128 
 int /*<<< orphan*/  RATE_MCS_CHAN_WIDTH_160 ; 
 int /*<<< orphan*/  RATE_MCS_CHAN_WIDTH_20 ; 
 int /*<<< orphan*/  RATE_MCS_CHAN_WIDTH_40 ; 
 int /*<<< orphan*/  RATE_MCS_CHAN_WIDTH_80 ; 

__attribute__((used)) static u32 rs_bw_from_sta_bw(struct ieee80211_sta *sta)
{
	switch (sta->bandwidth) {
	case IEEE80211_STA_RX_BW_160:
		return RATE_MCS_CHAN_WIDTH_160;
	case IEEE80211_STA_RX_BW_80:
		return RATE_MCS_CHAN_WIDTH_80;
	case IEEE80211_STA_RX_BW_40:
		return RATE_MCS_CHAN_WIDTH_40;
	case IEEE80211_STA_RX_BW_20:
	default:
		return RATE_MCS_CHAN_WIDTH_20;
	}
}