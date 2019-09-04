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
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
#define  IEEE80211_VHT_MCS_NOT_SUPPORTED 131 
#define  IEEE80211_VHT_MCS_SUPPORT_0_7 130 
#define  IEEE80211_VHT_MCS_SUPPORT_0_8 129 
#define  IEEE80211_VHT_MCS_SUPPORT_0_9 128 
 int NL80211_VHT_NSS_MAX ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

void ieee80211_get_vht_mask_from_cap(__le16 vht_cap,
				     u16 vht_mask[NL80211_VHT_NSS_MAX])
{
	int i;
	u16 mask, cap = le16_to_cpu(vht_cap);

	for (i = 0; i < NL80211_VHT_NSS_MAX; i++) {
		mask = (cap >> i * 2) & IEEE80211_VHT_MCS_NOT_SUPPORTED;
		switch (mask) {
		case IEEE80211_VHT_MCS_SUPPORT_0_7:
			vht_mask[i] = 0x00FF;
			break;
		case IEEE80211_VHT_MCS_SUPPORT_0_8:
			vht_mask[i] = 0x01FF;
			break;
		case IEEE80211_VHT_MCS_SUPPORT_0_9:
			vht_mask[i] = 0x03FF;
			break;
		case IEEE80211_VHT_MCS_NOT_SUPPORTED:
		default:
			vht_mask[i] = 0;
			break;
		}
	}
}