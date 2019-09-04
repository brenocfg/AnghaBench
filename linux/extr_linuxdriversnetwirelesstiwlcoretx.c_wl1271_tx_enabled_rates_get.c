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
typedef  int u32 ;
struct wl1271 {TYPE_1__* hw; } ;
struct ieee80211_supported_band {int n_bitrates; TYPE_2__* bitrates; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_6__ {struct ieee80211_supported_band** bands; } ;
struct TYPE_5__ {int hw_value; } ;
struct TYPE_4__ {TYPE_3__* wiphy; } ;

/* Variables and functions */
 int CONF_HW_BIT_RATE_MCS_0 ; 
 int HW_HT_RATES_OFFSET ; 

u32 wl1271_tx_enabled_rates_get(struct wl1271 *wl, u32 rate_set,
				enum nl80211_band rate_band)
{
	struct ieee80211_supported_band *band;
	u32 enabled_rates = 0;
	int bit;

	band = wl->hw->wiphy->bands[rate_band];
	for (bit = 0; bit < band->n_bitrates; bit++) {
		if (rate_set & 0x1)
			enabled_rates |= band->bitrates[bit].hw_value;
		rate_set >>= 1;
	}

	/* MCS rates indication are on bits 16 - 31 */
	rate_set >>= HW_HT_RATES_OFFSET - band->n_bitrates;

	for (bit = 0; bit < 16; bit++) {
		if (rate_set & 0x1)
			enabled_rates |= (CONF_HW_BIT_RATE_MCS_0 << bit);
		rate_set >>= 1;
	}

	return enabled_rates;
}