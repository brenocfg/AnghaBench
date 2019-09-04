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
struct adapter {int dummy; } ;

/* Variables and functions */
 size_t IEEE80211_BASIC_RATE_MASK ; 
#define  IEEE80211_CCK_RATE_11MB 134 
#define  IEEE80211_CCK_RATE_1MB 133 
#define  IEEE80211_CCK_RATE_2MB 132 
#define  IEEE80211_CCK_RATE_5MB 131 
#define  IEEE80211_OFDM_RATE_12MB 130 
#define  IEEE80211_OFDM_RATE_24MB 129 
#define  IEEE80211_OFDM_RATE_6MB 128 
 size_t NDIS_802_11_LENGTH_RATES_EX ; 

void UpdateBrateTbl(struct adapter *Adapter, u8 *mBratesOS)
{
	u8 i;
	u8 rate;

	/*  1M, 2M, 5.5M, 11M, 6M, 12M, 24M are mandatory. */
	for (i = 0; i < NDIS_802_11_LENGTH_RATES_EX; i++) {
		rate = mBratesOS[i] & 0x7f;
		switch (rate) {
		case IEEE80211_CCK_RATE_1MB:
		case IEEE80211_CCK_RATE_2MB:
		case IEEE80211_CCK_RATE_5MB:
		case IEEE80211_CCK_RATE_11MB:
		case IEEE80211_OFDM_RATE_6MB:
		case IEEE80211_OFDM_RATE_12MB:
		case IEEE80211_OFDM_RATE_24MB:
			mBratesOS[i] |= IEEE80211_BASIC_RATE_MASK;
			break;
		}
	}
}