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
typedef  int u8 ;
typedef  int s8 ;

/* Variables and functions */
 int BIT (int) ; 
 int IEEE80211_HT_MCS_MASK_LEN ; 

__attribute__((used)) static bool rate_idx_match_mcs_mask(s8 *rate_idx, u8 *mcs_mask)
{
	int i, j;
	int ridx, rbit;

	ridx = *rate_idx / 8;
	rbit = *rate_idx % 8;

	/* sanity check */
	if (ridx < 0 || ridx >= IEEE80211_HT_MCS_MASK_LEN)
		return false;

	/* See whether the selected rate or anything below it is allowed. */
	for (i = ridx; i >= 0; i--) {
		for (j = rbit; j >= 0; j--)
			if (mcs_mask[i] & BIT(j)) {
				*rate_idx = i * 8 + j;
				return true;
			}
		rbit = 7;
	}

	/* Try to find a higher rate that would be allowed */
	ridx = (*rate_idx + 1) / 8;
	rbit = (*rate_idx + 1) % 8;

	for (i = ridx; i < IEEE80211_HT_MCS_MASK_LEN; i++) {
		for (j = rbit; j < 8; j++)
			if (mcs_mask[i] & BIT(j)) {
				*rate_idx = i * 8 + j;
				return true;
			}
		rbit = 0;
	}
	return false;
}