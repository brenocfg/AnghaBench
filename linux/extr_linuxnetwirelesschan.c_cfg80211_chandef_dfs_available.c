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
struct wiphy {int dummy; } ;
struct cfg80211_chan_def {int center_freq1; int width; int center_freq2; } ;

/* Variables and functions */
#define  NL80211_CHAN_WIDTH_80P80 128 
 scalar_t__ WARN_ON (int) ; 
 int cfg80211_chandef_get_width (struct cfg80211_chan_def const*) ; 
 int /*<<< orphan*/  cfg80211_chandef_valid (struct cfg80211_chan_def const*) ; 
 int cfg80211_get_chans_dfs_available (struct wiphy*,int,int) ; 

__attribute__((used)) static bool cfg80211_chandef_dfs_available(struct wiphy *wiphy,
				const struct cfg80211_chan_def *chandef)
{
	int width;
	int r;

	if (WARN_ON(!cfg80211_chandef_valid(chandef)))
		return false;

	width = cfg80211_chandef_get_width(chandef);
	if (width < 0)
		return false;

	r = cfg80211_get_chans_dfs_available(wiphy, chandef->center_freq1,
					     width);

	/* If any of channels unavailable for cf1 just return */
	if (!r)
		return r;

	switch (chandef->width) {
	case NL80211_CHAN_WIDTH_80P80:
		WARN_ON(!chandef->center_freq2);
		r = cfg80211_get_chans_dfs_available(wiphy,
						     chandef->center_freq2,
						     width);
		break;
	default:
		WARN_ON(chandef->center_freq2);
		break;
	}

	return r;
}