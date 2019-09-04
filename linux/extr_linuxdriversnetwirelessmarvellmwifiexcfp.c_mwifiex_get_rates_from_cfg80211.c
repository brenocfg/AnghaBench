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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct wiphy {struct ieee80211_supported_band** bands; } ;
struct mwifiex_private {struct cfg80211_scan_request* scan_request; TYPE_1__* adapter; } ;
struct ieee80211_supported_band {int n_bitrates; TYPE_2__* bitrates; } ;
struct cfg80211_scan_request {int* rates; } ;
struct TYPE_4__ {int bitrate; } ;
struct TYPE_3__ {struct wiphy* wiphy; } ;

/* Variables and functions */
 int BIT (int) ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 scalar_t__ WARN_ON_ONCE (int) ; 

u32 mwifiex_get_rates_from_cfg80211(struct mwifiex_private *priv,
				    u8 *rates, u8 radio_type)
{
	struct wiphy *wiphy = priv->adapter->wiphy;
	struct cfg80211_scan_request *request = priv->scan_request;
	u32 num_rates, rate_mask;
	struct ieee80211_supported_band *sband;
	int i;

	if (radio_type) {
		sband = wiphy->bands[NL80211_BAND_5GHZ];
		if (WARN_ON_ONCE(!sband))
			return 0;
		rate_mask = request->rates[NL80211_BAND_5GHZ];
	} else {
		sband = wiphy->bands[NL80211_BAND_2GHZ];
		if (WARN_ON_ONCE(!sband))
			return 0;
		rate_mask = request->rates[NL80211_BAND_2GHZ];
	}

	num_rates = 0;
	for (i = 0; i < sband->n_bitrates; i++) {
		if ((BIT(i) & rate_mask) == 0)
			continue; /* skip rate */
		rates[num_rates++] = (u8)(sband->bitrates[i].bitrate / 5);
	}

	return num_rates;
}