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
typedef  int u16 ;

/* Variables and functions */
#define  IEEE80211_VHT_MCS_NOT_SUPPORTED 131 
#define  IEEE80211_VHT_MCS_SUPPORT_0_7 130 
#define  IEEE80211_VHT_MCS_SUPPORT_0_8 129 
#define  IEEE80211_VHT_MCS_SUPPORT_0_9 128 

__attribute__((used)) static u16 vht_mcs_map_to_mcs_mask(u8 vht_mcs_map)
{
	u16 mcs_mask = 0;

	switch (vht_mcs_map) {
	case IEEE80211_VHT_MCS_NOT_SUPPORTED:
		break;
	case IEEE80211_VHT_MCS_SUPPORT_0_7:
		mcs_mask = 0x00FF;
		break;
	case IEEE80211_VHT_MCS_SUPPORT_0_8:
		mcs_mask = 0x01FF;
		break;
	case IEEE80211_VHT_MCS_SUPPORT_0_9:
		mcs_mask = 0x03FF;
		break;
	default:
		break;
	}

	return mcs_mask;
}