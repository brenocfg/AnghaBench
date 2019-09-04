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
struct ieee80211_channel {int beacon_found; int /*<<< orphan*/  orig_mpwr; int /*<<< orphan*/  max_power; int /*<<< orphan*/  orig_mag; int /*<<< orphan*/  max_antenna_gain; int /*<<< orphan*/  orig_flags; int /*<<< orphan*/  flags; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int NUM_NL80211_BANDS ; 

__attribute__((used)) static void restore_custom_reg_settings(struct wiphy *wiphy)
{
	struct ieee80211_supported_band *sband;
	enum nl80211_band band;
	struct ieee80211_channel *chan;
	int i;

	for (band = 0; band < NUM_NL80211_BANDS; band++) {
		sband = wiphy->bands[band];
		if (!sband)
			continue;
		for (i = 0; i < sband->n_channels; i++) {
			chan = &sband->channels[i];
			chan->flags = chan->orig_flags;
			chan->max_antenna_gain = chan->orig_mag;
			chan->max_power = chan->orig_mpwr;
			chan->beacon_found = false;
		}
	}
}