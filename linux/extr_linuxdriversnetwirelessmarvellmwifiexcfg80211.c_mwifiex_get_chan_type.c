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
typedef  int /*<<< orphan*/  u8 ;
struct mwifiex_private {int dummy; } ;
struct TYPE_2__ {int chan_width; int /*<<< orphan*/  chan2_offset; } ;
struct mwifiex_channel_band {TYPE_1__ band_config; } ;

/* Variables and functions */
#define  CHAN_BW_20MHZ 129 
#define  CHAN_BW_40MHZ 128 
 int /*<<< orphan*/  IS_11N_ENABLED (struct mwifiex_private*) ; 
 int /*<<< orphan*/  NL80211_CHAN_HT20 ; 
 int /*<<< orphan*/  NL80211_CHAN_HT40MINUS ; 
 int /*<<< orphan*/  NL80211_CHAN_HT40PLUS ; 
 int /*<<< orphan*/  NL80211_CHAN_NO_HT ; 
 int /*<<< orphan*/  SEC_CHAN_ABOVE ; 
 int mwifiex_get_chan_info (struct mwifiex_private*,struct mwifiex_channel_band*) ; 

u8 mwifiex_get_chan_type(struct mwifiex_private *priv)
{
	struct mwifiex_channel_band channel_band;
	int ret;

	ret = mwifiex_get_chan_info(priv, &channel_band);

	if (!ret) {
		switch (channel_band.band_config.chan_width) {
		case CHAN_BW_20MHZ:
			if (IS_11N_ENABLED(priv))
				return NL80211_CHAN_HT20;
			else
				return NL80211_CHAN_NO_HT;
		case CHAN_BW_40MHZ:
			if (channel_band.band_config.chan2_offset ==
			    SEC_CHAN_ABOVE)
				return NL80211_CHAN_HT40PLUS;
			else
				return NL80211_CHAN_HT40MINUS;
		default:
			return NL80211_CHAN_HT20;
		}
	}

	return NL80211_CHAN_HT20;
}