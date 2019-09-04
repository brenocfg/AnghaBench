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
typedef  int u32 ;
struct wiphy {int dummy; } ;
struct ieee80211_channel {int flags; int dfs_state; int /*<<< orphan*/  dfs_state_entered; } ;
typedef  enum nl80211_dfs_state { ____Placeholder_nl80211_dfs_state } nl80211_dfs_state ;

/* Variables and functions */
 int IEEE80211_CHAN_RADAR ; 
 struct ieee80211_channel* ieee80211_get_channel (struct wiphy*,int) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void cfg80211_set_chans_dfs_state(struct wiphy *wiphy, u32 center_freq,
					 u32 bandwidth,
					 enum nl80211_dfs_state dfs_state)
{
	struct ieee80211_channel *c;
	u32 freq;

	for (freq = center_freq - bandwidth/2 + 10;
	     freq <= center_freq + bandwidth/2 - 10;
	     freq += 20) {
		c = ieee80211_get_channel(wiphy, freq);
		if (!c || !(c->flags & IEEE80211_CHAN_RADAR))
			continue;

		c->dfs_state = dfs_state;
		c->dfs_state_entered = jiffies;
	}
}