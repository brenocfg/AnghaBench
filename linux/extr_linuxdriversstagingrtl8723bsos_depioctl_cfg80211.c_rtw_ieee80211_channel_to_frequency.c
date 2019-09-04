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

/* Variables and functions */
 int NL80211_BAND_2GHZ ; 

__attribute__((used)) static int rtw_ieee80211_channel_to_frequency(int chan, int band)
{
	/* see 802.11 17.3.8.3.2 and Annex J
	* there are overlapping channel numbers in 5GHz and 2GHz bands */
	if (band == NL80211_BAND_2GHZ) {
		if (chan == 14)
			return 2484;
             else if (chan < 14)
			return 2407 + chan * 5;
	}

	return 0; /* not supported */
}