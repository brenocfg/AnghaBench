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
struct wiphy {struct ieee80211_supported_band** bands; } ;
struct ieee80211_supported_band {int n_channels; struct ieee80211_channel* channels; } ;
struct ieee80211_freq_range {int dummy; } ;
struct ieee80211_channel {int flags; int /*<<< orphan*/  center_freq; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int IEEE80211_CHAN_DISABLED ; 
 int NUM_NL80211_BANDS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_freq_limits_valid_chan (struct wiphy*,struct ieee80211_freq_range*,unsigned int,struct ieee80211_channel*) ; 

__attribute__((used)) static void wiphy_freq_limits_apply(struct wiphy *wiphy,
				    struct ieee80211_freq_range *freq_limits,
				    unsigned int n_freq_limits)
{
	enum nl80211_band band;
	int i;

	if (WARN_ON(!n_freq_limits))
		return;

	for (band = 0; band < NUM_NL80211_BANDS; band++) {
		struct ieee80211_supported_band *sband = wiphy->bands[band];

		if (!sband)
			continue;

		for (i = 0; i < sband->n_channels; i++) {
			struct ieee80211_channel *chan = &sband->channels[i];

			if (chan->flags & IEEE80211_CHAN_DISABLED)
				continue;

			if (!wiphy_freq_limits_valid_chan(wiphy, freq_limits,
							  n_freq_limits,
							  chan)) {
				pr_debug("Disabling freq %d MHz as it's out of OF limits\n",
					 chan->center_freq);
				chan->flags |= IEEE80211_CHAN_DISABLED;
			}
		}
	}
}