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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wiphy {int dummy; } ;
struct ieee80211_ht_operation {int primary_chan; } ;
struct ieee80211_channel {int flags; int /*<<< orphan*/  band; } ;
typedef  enum nl80211_bss_scan_width { ____Placeholder_nl80211_bss_scan_width } nl80211_bss_scan_width ;

/* Variables and functions */
 int IEEE80211_CHAN_DISABLED ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int NL80211_BSS_CHAN_WIDTH_10 ; 
 int NL80211_BSS_CHAN_WIDTH_5 ; 
 int /*<<< orphan*/  WLAN_EID_DS_PARAMS ; 
 int /*<<< orphan*/  WLAN_EID_HT_OPERATION ; 
 int* cfg80211_find_ie (int /*<<< orphan*/ ,int const*,size_t) ; 
 int /*<<< orphan*/  ieee80211_channel_to_frequency (int,int /*<<< orphan*/ ) ; 
 struct ieee80211_channel* ieee80211_get_channel (struct wiphy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ieee80211_channel *
cfg80211_get_bss_channel(struct wiphy *wiphy, const u8 *ie, size_t ielen,
			 struct ieee80211_channel *channel,
			 enum nl80211_bss_scan_width scan_width)
{
	const u8 *tmp;
	u32 freq;
	int channel_number = -1;
	struct ieee80211_channel *alt_channel;

	tmp = cfg80211_find_ie(WLAN_EID_DS_PARAMS, ie, ielen);
	if (tmp && tmp[1] == 1) {
		channel_number = tmp[2];
	} else {
		tmp = cfg80211_find_ie(WLAN_EID_HT_OPERATION, ie, ielen);
		if (tmp && tmp[1] >= sizeof(struct ieee80211_ht_operation)) {
			struct ieee80211_ht_operation *htop = (void *)(tmp + 2);

			channel_number = htop->primary_chan;
		}
	}

	if (channel_number < 0) {
		/* No channel information in frame payload */
		return channel;
	}

	freq = ieee80211_channel_to_frequency(channel_number, channel->band);
	alt_channel = ieee80211_get_channel(wiphy, freq);
	if (!alt_channel) {
		if (channel->band == NL80211_BAND_2GHZ) {
			/*
			 * Better not allow unexpected channels when that could
			 * be going beyond the 1-11 range (e.g., discovering
			 * BSS on channel 12 when radio is configured for
			 * channel 11.
			 */
			return NULL;
		}

		/* No match for the payload channel number - ignore it */
		return channel;
	}

	if (scan_width == NL80211_BSS_CHAN_WIDTH_10 ||
	    scan_width == NL80211_BSS_CHAN_WIDTH_5) {
		/*
		 * Ignore channel number in 5 and 10 MHz channels where there
		 * may not be an n:1 or 1:n mapping between frequencies and
		 * channel numbers.
		 */
		return channel;
	}

	/*
	 * Use the channel determined through the payload channel number
	 * instead of the RX channel reported by the driver.
	 */
	if (alt_channel->flags & IEEE80211_CHAN_DISABLED)
		return NULL;
	return alt_channel;
}