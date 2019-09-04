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
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int NUM_NL80211_BANDS ; 
 int /*<<< orphan*/  reg_copy_dfs_chan_state (struct ieee80211_channel*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  reg_dfs_domain_same (struct wiphy*,struct wiphy*) ; 

__attribute__((used)) static void wiphy_share_dfs_chan_state(struct wiphy *dst_wiphy,
				       struct wiphy *src_wiphy)
{
	struct ieee80211_supported_band *src_sband, *dst_sband;
	struct ieee80211_channel *src_chan, *dst_chan;
	int i, j, band;

	if (!reg_dfs_domain_same(dst_wiphy, src_wiphy))
		return;

	for (band = 0; band < NUM_NL80211_BANDS; band++) {
		dst_sband = dst_wiphy->bands[band];
		src_sband = src_wiphy->bands[band];
		if (!dst_sband || !src_sband)
			continue;

		for (i = 0; i < dst_sband->n_channels; i++) {
			dst_chan = &dst_sband->channels[i];
			for (j = 0; j < src_sband->n_channels; j++) {
				src_chan = &src_sband->channels[j];
				reg_copy_dfs_chan_state(dst_chan, src_chan);
			}
		}
	}
}