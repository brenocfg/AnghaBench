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
struct ieee80211_supported_band {void* n_bitrates; void* bitrates; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int EINVAL ; 
#define  NL80211_BAND_2GHZ 129 
#define  NL80211_BAND_5GHZ 128 
 void* p54_arates ; 
 void* p54_bgrates ; 

__attribute__((used)) static int p54_fill_band_bitrates(struct ieee80211_hw *dev,
				  struct ieee80211_supported_band *band_entry,
				  enum nl80211_band band)
{
	/* TODO: generate rate array dynamically */

	switch (band) {
	case NL80211_BAND_2GHZ:
		band_entry->bitrates = p54_bgrates;
		band_entry->n_bitrates = ARRAY_SIZE(p54_bgrates);
		break;
	case NL80211_BAND_5GHZ:
		band_entry->bitrates = p54_arates;
		band_entry->n_bitrates = ARRAY_SIZE(p54_arates);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}