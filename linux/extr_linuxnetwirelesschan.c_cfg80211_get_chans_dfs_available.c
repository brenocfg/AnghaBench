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
struct ieee80211_channel {int flags; scalar_t__ dfs_state; } ;

/* Variables and functions */
 int IEEE80211_CHAN_DISABLED ; 
 int IEEE80211_CHAN_RADAR ; 
 scalar_t__ NL80211_DFS_AVAILABLE ; 
 scalar_t__ NL80211_DFS_USABLE ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_DFS_OFFLOAD ; 
 scalar_t__ cfg80211_get_end_freq (scalar_t__,scalar_t__) ; 
 scalar_t__ cfg80211_get_start_freq (scalar_t__,scalar_t__) ; 
 struct ieee80211_channel* ieee80211_get_channel (struct wiphy*,scalar_t__) ; 
 int wiphy_ext_feature_isset (struct wiphy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cfg80211_get_chans_dfs_available(struct wiphy *wiphy,
					     u32 center_freq,
					     u32 bandwidth)
{
	struct ieee80211_channel *c;
	u32 freq, start_freq, end_freq;
	bool dfs_offload;

	dfs_offload = wiphy_ext_feature_isset(wiphy,
					      NL80211_EXT_FEATURE_DFS_OFFLOAD);

	start_freq = cfg80211_get_start_freq(center_freq, bandwidth);
	end_freq = cfg80211_get_end_freq(center_freq, bandwidth);

	/*
	 * Check entire range of channels for the bandwidth.
	 * If any channel in between is disabled or has not
	 * had gone through CAC return false
	 */
	for (freq = start_freq; freq <= end_freq; freq += 20) {
		c = ieee80211_get_channel(wiphy, freq);
		if (!c)
			return false;

		if (c->flags & IEEE80211_CHAN_DISABLED)
			return false;

		if ((c->flags & IEEE80211_CHAN_RADAR) &&
		    (c->dfs_state != NL80211_DFS_AVAILABLE) &&
		    !(c->dfs_state == NL80211_DFS_USABLE && dfs_offload))
			return false;
	}

	return true;
}