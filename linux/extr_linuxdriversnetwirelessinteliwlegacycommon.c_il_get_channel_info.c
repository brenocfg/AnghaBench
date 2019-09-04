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
typedef  int u16 ;
struct il_priv {int channel_count; struct il_channel_info const* channel_info; } ;
struct il_channel_info {int channel; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  NL80211_BAND_2GHZ 129 
#define  NL80211_BAND_5GHZ 128 

const struct il_channel_info *
il_get_channel_info(const struct il_priv *il, enum nl80211_band band,
		    u16 channel)
{
	int i;

	switch (band) {
	case NL80211_BAND_5GHZ:
		for (i = 14; i < il->channel_count; i++) {
			if (il->channel_info[i].channel == channel)
				return &il->channel_info[i];
		}
		break;
	case NL80211_BAND_2GHZ:
		if (channel >= 1 && channel <= 14)
			return &il->channel_info[channel - 1];
		break;
	default:
		BUG();
	}

	return NULL;
}