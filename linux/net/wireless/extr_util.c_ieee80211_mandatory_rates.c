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
typedef  int u32 ;
struct ieee80211_supported_band {scalar_t__ band; int n_bitrates; struct ieee80211_rate* bitrates; } ;
struct ieee80211_rate {int flags; } ;
typedef  enum nl80211_bss_scan_width { ____Placeholder_nl80211_bss_scan_width } nl80211_bss_scan_width ;
typedef  enum ieee80211_rate_flags { ____Placeholder_ieee80211_rate_flags } ieee80211_rate_flags ;

/* Variables and functions */
 int BIT (int) ; 
 int IEEE80211_RATE_MANDATORY_A ; 
 int IEEE80211_RATE_MANDATORY_B ; 
 int IEEE80211_RATE_MANDATORY_G ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 int NL80211_BSS_CHAN_WIDTH_10 ; 
 int NL80211_BSS_CHAN_WIDTH_5 ; 
 scalar_t__ WARN_ON (int) ; 

u32 ieee80211_mandatory_rates(struct ieee80211_supported_band *sband,
			      enum nl80211_bss_scan_width scan_width)
{
	struct ieee80211_rate *bitrates;
	u32 mandatory_rates = 0;
	enum ieee80211_rate_flags mandatory_flag;
	int i;

	if (WARN_ON(!sband))
		return 1;

	if (sband->band == NL80211_BAND_2GHZ) {
		if (scan_width == NL80211_BSS_CHAN_WIDTH_5 ||
		    scan_width == NL80211_BSS_CHAN_WIDTH_10)
			mandatory_flag = IEEE80211_RATE_MANDATORY_G;
		else
			mandatory_flag = IEEE80211_RATE_MANDATORY_B;
	} else {
		mandatory_flag = IEEE80211_RATE_MANDATORY_A;
	}

	bitrates = sband->bitrates;
	for (i = 0; i < sband->n_bitrates; i++)
		if (bitrates[i].flags & mandatory_flag)
			mandatory_rates |= BIT(i);
	return mandatory_rates;
}