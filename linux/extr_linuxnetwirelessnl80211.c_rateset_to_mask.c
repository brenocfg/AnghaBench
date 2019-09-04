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
typedef  size_t u8 ;
typedef  int u32 ;
struct ieee80211_supported_band {int n_bitrates; struct ieee80211_rate* bitrates; } ;
struct ieee80211_rate {int bitrate; } ;

/* Variables and functions */

__attribute__((used)) static u32 rateset_to_mask(struct ieee80211_supported_band *sband,
			   u8 *rates, u8 rates_len)
{
	u8 i;
	u32 mask = 0;

	for (i = 0; i < rates_len; i++) {
		int rate = (rates[i] & 0x7f) * 5;
		int ridx;

		for (ridx = 0; ridx < sband->n_bitrates; ridx++) {
			struct ieee80211_rate *srate =
				&sband->bitrates[ridx];
			if (rate == srate->bitrate) {
				mask |= 1 << ridx;
				break;
			}
		}
		if (ridx == sband->n_bitrates)
			return 0; /* rate not found */
	}

	return mask;
}