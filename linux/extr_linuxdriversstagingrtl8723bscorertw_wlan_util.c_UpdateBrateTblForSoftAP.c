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
typedef  size_t u32 ;

/* Variables and functions */
 size_t IEEE80211_BASIC_RATE_MASK ; 
#define  IEEE80211_CCK_RATE_11MB 131 
#define  IEEE80211_CCK_RATE_1MB 130 
#define  IEEE80211_CCK_RATE_2MB 129 
#define  IEEE80211_CCK_RATE_5MB 128 

void UpdateBrateTblForSoftAP(u8 *bssrateset, u32 bssratelen)
{
	u8 i;
	u8 rate;

	for (i = 0; i < bssratelen; i++) {
		rate = bssrateset[i] & 0x7f;
		switch (rate) {
		case IEEE80211_CCK_RATE_1MB:
		case IEEE80211_CCK_RATE_2MB:
		case IEEE80211_CCK_RATE_5MB:
		case IEEE80211_CCK_RATE_11MB:
			bssrateset[i] |= IEEE80211_BASIC_RATE_MASK;
			break;
		}
	}
}