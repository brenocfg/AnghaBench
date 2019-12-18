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
typedef  int /*<<< orphan*/  u8 ;
struct cfg80211_chan_def {int width; scalar_t__ center_freq2; scalar_t__ center_freq1; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_VHT_CHANWIDTH_160MHZ ; 
 int /*<<< orphan*/  IEEE80211_VHT_CHANWIDTH_80MHZ ; 
 int /*<<< orphan*/  IEEE80211_VHT_CHANWIDTH_80P80MHZ ; 
 int /*<<< orphan*/  IEEE80211_VHT_CHANWIDTH_USE_HT ; 
#define  NL80211_CHAN_WIDTH_160 130 
#define  NL80211_CHAN_WIDTH_80 129 
#define  NL80211_CHAN_WIDTH_80P80 128 
 int /*<<< orphan*/  WLAN_EID_WIDE_BW_CHANNEL_SWITCH ; 
 void* ieee80211_frequency_to_channel (scalar_t__) ; 

void ieee80211_ie_build_wide_bw_cs(u8 *pos,
				   const struct cfg80211_chan_def *chandef)
{
	*pos++ = WLAN_EID_WIDE_BW_CHANNEL_SWITCH;	/* EID */
	*pos++ = 3;					/* IE length */
	/* New channel width */
	switch (chandef->width) {
	case NL80211_CHAN_WIDTH_80:
		*pos++ = IEEE80211_VHT_CHANWIDTH_80MHZ;
		break;
	case NL80211_CHAN_WIDTH_160:
		*pos++ = IEEE80211_VHT_CHANWIDTH_160MHZ;
		break;
	case NL80211_CHAN_WIDTH_80P80:
		*pos++ = IEEE80211_VHT_CHANWIDTH_80P80MHZ;
		break;
	default:
		*pos++ = IEEE80211_VHT_CHANWIDTH_USE_HT;
	}

	/* new center frequency segment 0 */
	*pos++ = ieee80211_frequency_to_channel(chandef->center_freq1);
	/* new center frequency segment 1 */
	if (chandef->center_freq2)
		*pos++ = ieee80211_frequency_to_channel(chandef->center_freq2);
	else
		*pos++ = 0;
}