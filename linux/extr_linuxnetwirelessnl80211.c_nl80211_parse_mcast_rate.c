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
struct wiphy {struct ieee80211_supported_band** bands; } ;
struct ieee80211_supported_band {int n_bitrates; TYPE_1__* bitrates; } ;
struct cfg80211_registered_device {struct wiphy wiphy; } ;
struct TYPE_2__ {int bitrate; } ;

/* Variables and functions */
 int NUM_NL80211_BANDS ; 

__attribute__((used)) static bool
nl80211_parse_mcast_rate(struct cfg80211_registered_device *rdev,
			 int mcast_rate[NUM_NL80211_BANDS],
			 int rateval)
{
	struct wiphy *wiphy = &rdev->wiphy;
	bool found = false;
	int band, i;

	for (band = 0; band < NUM_NL80211_BANDS; band++) {
		struct ieee80211_supported_band *sband;

		sband = wiphy->bands[band];
		if (!sband)
			continue;

		for (i = 0; i < sband->n_bitrates; i++) {
			if (sband->bitrates[i].bitrate == rateval) {
				mcast_rate[band] = i + 1;
				found = true;
				break;
			}
		}
	}

	return found;
}