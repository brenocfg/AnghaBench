#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mwl8k_priv {TYPE_3__* hw; } ;
struct ieee80211_supported_band {int n_channels; TYPE_1__* channels; } ;
struct TYPE_6__ {TYPE_2__* wiphy; } ;
struct TYPE_5__ {struct ieee80211_supported_band** bands; } ;
struct TYPE_4__ {int center_freq; } ;

/* Variables and functions */
 int NL80211_BAND_2GHZ ; 
 int NUM_NL80211_BANDS ; 

__attribute__((used)) static int freq_to_idx(struct mwl8k_priv *priv, int freq)
{
	struct ieee80211_supported_band *sband;
	int band, ch, idx = 0;

	for (band = NL80211_BAND_2GHZ; band < NUM_NL80211_BANDS; band++) {
		sband = priv->hw->wiphy->bands[band];
		if (!sband)
			continue;

		for (ch = 0; ch < sband->n_channels; ch++, idx++)
			if (sband->channels[ch].center_freq == freq)
				goto exit;
	}

exit:
	return idx;
}