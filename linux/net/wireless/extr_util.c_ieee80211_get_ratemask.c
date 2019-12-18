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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_supported_band {int n_bitrates; TYPE_1__* bitrates; } ;
struct TYPE_2__ {int bitrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 unsigned int NL80211_MAX_SUPP_RATES ; 

int ieee80211_get_ratemask(struct ieee80211_supported_band *sband,
			   const u8 *rates, unsigned int n_rates,
			   u32 *mask)
{
	int i, j;

	if (!sband)
		return -EINVAL;

	if (n_rates == 0 || n_rates > NL80211_MAX_SUPP_RATES)
		return -EINVAL;

	*mask = 0;

	for (i = 0; i < n_rates; i++) {
		int rate = (rates[i] & 0x7f) * 5;
		bool found = false;

		for (j = 0; j < sband->n_bitrates; j++) {
			if (sband->bitrates[j].bitrate == rate) {
				found = true;
				*mask |= BIT(j);
				break;
			}
		}
		if (!found)
			return -EINVAL;
	}

	/*
	 * mask must have at least one bit set here since we
	 * didn't accept a 0-length rates array nor allowed
	 * entries in the array that didn't exist
	 */

	return 0;
}