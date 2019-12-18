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
typedef  int u16 ;
typedef  int s8 ;

/* Variables and functions */
 int BIT (int) ; 
 int NL80211_VHT_NSS_MAX ; 

__attribute__((used)) static bool rate_idx_match_vht_mcs_mask(s8 *rate_idx, u16 *vht_mask)
{
	int i, j;
	int ridx, rbit;

	ridx = *rate_idx >> 4;
	rbit = *rate_idx & 0xf;

	if (ridx < 0 || ridx >= NL80211_VHT_NSS_MAX)
		return false;

	/* See whether the selected rate or anything below it is allowed. */
	for (i = ridx; i >= 0; i--) {
		for (j = rbit; j >= 0; j--) {
			if (vht_mask[i] & BIT(j)) {
				*rate_idx = (i << 4) | j;
				return true;
			}
		}
		rbit = 15;
	}

	/* Try to find a higher rate that would be allowed */
	ridx = (*rate_idx + 1) >> 4;
	rbit = (*rate_idx + 1) & 0xf;

	for (i = ridx; i < NL80211_VHT_NSS_MAX; i++) {
		for (j = rbit; j < 16; j++) {
			if (vht_mask[i] & BIT(j)) {
				*rate_idx = (i << 4) | j;
				return true;
			}
		}
		rbit = 0;
	}
	return false;
}