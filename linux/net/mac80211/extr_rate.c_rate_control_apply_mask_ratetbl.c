#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sta_info {TYPE_5__* sdata; int /*<<< orphan*/  sta; } ;
struct ieee80211_supported_band {int dummy; } ;
struct ieee80211_sta_rates {TYPE_4__* rate; } ;
typedef  enum nl80211_chan_width { ____Placeholder_nl80211_chan_width } nl80211_chan_width ;
struct TYPE_6__ {int width; } ;
struct TYPE_7__ {TYPE_1__ chandef; } ;
struct TYPE_8__ {TYPE_2__ bss_conf; } ;
struct TYPE_10__ {TYPE_3__ vif; } ;
struct TYPE_9__ {scalar_t__ idx; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int IEEE80211_HT_MCS_MASK_LEN ; 
 int IEEE80211_TX_RATE_TABLE_SIZE ; 
 int NL80211_VHT_NSS_MAX ; 
 int /*<<< orphan*/  rate_control_cap_mask (TYPE_5__*,struct ieee80211_supported_band*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rate_idx_match_mask (scalar_t__*,int /*<<< orphan*/ *,struct ieee80211_supported_band*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rate_control_apply_mask_ratetbl(struct sta_info *sta,
				struct ieee80211_supported_band *sband,
				struct ieee80211_sta_rates *rates)
{
	int i;
	u32 mask;
	u8 mcs_mask[IEEE80211_HT_MCS_MASK_LEN];
	u16 vht_mask[NL80211_VHT_NSS_MAX];
	enum nl80211_chan_width chan_width;

	if (!rate_control_cap_mask(sta->sdata, sband, &sta->sta, &mask,
				   mcs_mask, vht_mask))
		return;

	chan_width = sta->sdata->vif.bss_conf.chandef.width;
	for (i = 0; i < IEEE80211_TX_RATE_TABLE_SIZE; i++) {
		if (rates->rate[i].idx < 0)
			break;

		rate_idx_match_mask(&rates->rate[i].idx, &rates->rate[i].flags,
				    sband, chan_width, mask, mcs_mask,
				    vht_mask);
	}
}