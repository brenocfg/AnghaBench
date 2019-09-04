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
struct ieee80211_supported_band {int n_channels; TYPE_1__* channels; } ;
struct ath10k {scalar_t__ low_5ghz_chan; scalar_t__ high_5ghz_chan; } ;
struct TYPE_2__ {scalar_t__ center_freq; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHAN_DISABLED ; 

__attribute__((used)) static void ath10k_mac_update_channel_list(struct ath10k *ar,
					   struct ieee80211_supported_band *band)
{
	int i;

	if (ar->low_5ghz_chan && ar->high_5ghz_chan) {
		for (i = 0; i < band->n_channels; i++) {
			if (band->channels[i].center_freq < ar->low_5ghz_chan ||
			    band->channels[i].center_freq > ar->high_5ghz_chan)
				band->channels[i].flags |=
					IEEE80211_CHAN_DISABLED;
		}
	}
}