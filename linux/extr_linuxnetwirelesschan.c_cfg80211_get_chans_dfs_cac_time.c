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
typedef  scalar_t__ u32 ;
struct wiphy {int dummy; } ;
struct ieee80211_channel {int flags; unsigned int dfs_cac_ms; } ;

/* Variables and functions */
 int IEEE80211_CHAN_DISABLED ; 
 int IEEE80211_CHAN_RADAR ; 
 scalar_t__ cfg80211_get_end_freq (scalar_t__,scalar_t__) ; 
 scalar_t__ cfg80211_get_start_freq (scalar_t__,scalar_t__) ; 
 struct ieee80211_channel* ieee80211_get_channel (struct wiphy*,scalar_t__) ; 

__attribute__((used)) static unsigned int cfg80211_get_chans_dfs_cac_time(struct wiphy *wiphy,
						    u32 center_freq,
						    u32 bandwidth)
{
	struct ieee80211_channel *c;
	u32 start_freq, end_freq, freq;
	unsigned int dfs_cac_ms = 0;

	start_freq = cfg80211_get_start_freq(center_freq, bandwidth);
	end_freq = cfg80211_get_end_freq(center_freq, bandwidth);

	for (freq = start_freq; freq <= end_freq; freq += 20) {
		c = ieee80211_get_channel(wiphy, freq);
		if (!c)
			return 0;

		if (c->flags & IEEE80211_CHAN_DISABLED)
			return 0;

		if (!(c->flags & IEEE80211_CHAN_RADAR))
			continue;

		if (c->dfs_cac_ms > dfs_cac_ms)
			dfs_cac_ms = c->dfs_cac_ms;
	}

	return dfs_cac_ms;
}