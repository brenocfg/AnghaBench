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
 unsigned char IEEE80211_CCK_RATE_11MB ; 
 unsigned char IEEE80211_CCK_RATE_1MB ; 
 unsigned char IEEE80211_CCK_RATE_2MB ; 
 unsigned char IEEE80211_CCK_RATE_5MB ; 
 unsigned char IEEE80211_OFDM_RATE_12MB ; 
 unsigned char IEEE80211_OFDM_RATE_18MB ; 
 unsigned char IEEE80211_OFDM_RATE_24MB ; 
 unsigned char IEEE80211_OFDM_RATE_36MB ; 
 unsigned char IEEE80211_OFDM_RATE_48MB ; 
 unsigned char IEEE80211_OFDM_RATE_54MB ; 
 unsigned char IEEE80211_OFDM_RATE_6MB ; 
 unsigned char IEEE80211_OFDM_RATE_9MB ; 

unsigned char ratetbl_val_2wifirate(unsigned char rate)
{
	unsigned char val = 0;

	switch (rate & 0x7f) 
	{
		case 0:
			val = IEEE80211_CCK_RATE_1MB;
			break;

		case 1:
			val = IEEE80211_CCK_RATE_2MB;
			break;

		case 2:
			val = IEEE80211_CCK_RATE_5MB;
			break;

		case 3:
			val = IEEE80211_CCK_RATE_11MB;
			break;
			
		case 4:
			val = IEEE80211_OFDM_RATE_6MB;
			break;

		case 5:
			val = IEEE80211_OFDM_RATE_9MB;
			break;

		case 6:
			val = IEEE80211_OFDM_RATE_12MB;
			break;
			
		case 7:
			val = IEEE80211_OFDM_RATE_18MB;
			break;

		case 8:
			val = IEEE80211_OFDM_RATE_24MB;
			break;
			
		case 9:
			val = IEEE80211_OFDM_RATE_36MB;
			break;

		case 10:
			val = IEEE80211_OFDM_RATE_48MB;
			break;
		
		case 11:
			val = IEEE80211_OFDM_RATE_54MB;
			break;

	}

	return val;

}