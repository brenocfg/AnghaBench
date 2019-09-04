#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct sta_info {int dummy; } ;
struct ieee80211_supported_band {int dummy; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct TYPE_4__ {TYPE_1__* wiphy; } ;
struct ieee80211_local {TYPE_2__ hw; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_3__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 scalar_t__ __ieee80211_vht_handle_opmode (struct ieee80211_sub_if_data*,struct sta_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_recalc_min_chandef (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  rate_control_rate_update (struct ieee80211_local*,struct ieee80211_supported_band*,struct sta_info*,scalar_t__) ; 

void ieee80211_vht_handle_opmode(struct ieee80211_sub_if_data *sdata,
				 struct sta_info *sta, u8 opmode,
				 enum nl80211_band band)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_supported_band *sband = local->hw.wiphy->bands[band];

	u32 changed = __ieee80211_vht_handle_opmode(sdata, sta, opmode, band);

	if (changed > 0) {
		ieee80211_recalc_min_chandef(sdata);
		rate_control_rate_update(local, sband, sta, changed);
	}
}