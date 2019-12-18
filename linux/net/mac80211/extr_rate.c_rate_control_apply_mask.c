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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_tx_rate {scalar_t__ idx; int /*<<< orphan*/  flags; } ;
struct ieee80211_supported_band {int dummy; } ;
struct TYPE_4__ {int width; } ;
struct TYPE_5__ {TYPE_1__ chandef; } ;
struct TYPE_6__ {TYPE_2__ bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_3__ vif; } ;
struct ieee80211_sta {int dummy; } ;
typedef  enum nl80211_chan_width { ____Placeholder_nl80211_chan_width } nl80211_chan_width ;

/* Variables and functions */
 int IEEE80211_HT_MCS_MASK_LEN ; 
 int NL80211_VHT_NSS_MAX ; 
 int /*<<< orphan*/  rate_control_cap_mask (struct ieee80211_sub_if_data*,struct ieee80211_supported_band*,struct ieee80211_sta*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rate_idx_match_mask (scalar_t__*,int /*<<< orphan*/ *,struct ieee80211_supported_band*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rate_control_apply_mask(struct ieee80211_sub_if_data *sdata,
				    struct ieee80211_sta *sta,
				    struct ieee80211_supported_band *sband,
				    struct ieee80211_tx_rate *rates,
				    int max_rates)
{
	enum nl80211_chan_width chan_width;
	u8 mcs_mask[IEEE80211_HT_MCS_MASK_LEN];
	u32 mask;
	u16 rate_flags, vht_mask[NL80211_VHT_NSS_MAX];
	int i;

	/*
	 * Try to enforce the rateidx mask the user wanted. skip this if the
	 * default mask (allow all rates) is used to save some processing for
	 * the common case.
	 */
	if (!rate_control_cap_mask(sdata, sband, sta, &mask, mcs_mask,
				   vht_mask))
		return;

	/*
	 * Make sure the rate index selected for each TX rate is
	 * included in the configured mask and change the rate indexes
	 * if needed.
	 */
	chan_width = sdata->vif.bss_conf.chandef.width;
	for (i = 0; i < max_rates; i++) {
		/* Skip invalid rates */
		if (rates[i].idx < 0)
			break;

		rate_flags = rates[i].flags;
		rate_idx_match_mask(&rates[i].idx, &rate_flags, sband,
				    chan_width, mask, mcs_mask, vht_mask);
		rates[i].flags = rate_flags;
	}
}