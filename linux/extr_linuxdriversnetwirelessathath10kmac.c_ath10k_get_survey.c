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
struct survey_info {int /*<<< orphan*/  filled; int /*<<< orphan*/ * channel; } ;
struct ieee80211_supported_band {int n_channels; int /*<<< orphan*/ * channels; } ;
struct ieee80211_hw {TYPE_1__* wiphy; struct ath10k* priv; } ;
struct ath10k {int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/ * rx_channel; int /*<<< orphan*/  data_lock; struct survey_info* survey; } ;
struct TYPE_2__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int ENOENT ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  SURVEY_INFO_IN_USE ; 
 int /*<<< orphan*/  ath10k_mac_update_bss_chan_survey (struct ath10k*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct survey_info*,struct survey_info*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_get_survey(struct ieee80211_hw *hw, int idx,
			     struct survey_info *survey)
{
	struct ath10k *ar = hw->priv;
	struct ieee80211_supported_band *sband;
	struct survey_info *ar_survey = &ar->survey[idx];
	int ret = 0;

	mutex_lock(&ar->conf_mutex);

	sband = hw->wiphy->bands[NL80211_BAND_2GHZ];
	if (sband && idx >= sband->n_channels) {
		idx -= sband->n_channels;
		sband = NULL;
	}

	if (!sband)
		sband = hw->wiphy->bands[NL80211_BAND_5GHZ];

	if (!sband || idx >= sband->n_channels) {
		ret = -ENOENT;
		goto exit;
	}

	ath10k_mac_update_bss_chan_survey(ar, &sband->channels[idx]);

	spin_lock_bh(&ar->data_lock);
	memcpy(survey, ar_survey, sizeof(*survey));
	spin_unlock_bh(&ar->data_lock);

	survey->channel = &sband->channels[idx];

	if (ar->rx_channel == survey->channel)
		survey->filled |= SURVEY_INFO_IN_USE;

exit:
	mutex_unlock(&ar->conf_mutex);
	return ret;
}