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
 int BIT (int) ; 
 int BW_20 ; 
 int BW_40 ; 
 int BW_80 ; 
#define  IEEE80211_VHT_MCS_SUPPORT_0_7 130 
#define  IEEE80211_VHT_MCS_SUPPORT_0_8 129 
#define  IEEE80211_VHT_MCS_SUPPORT_0_9 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16
minstrel_get_valid_vht_rates(int bw, int nss, __le16 mcs_map)
{
	u16 mask = 0;

	if (bw == BW_20) {
		if (nss != 3 && nss != 6)
			mask = BIT(9);
	} else if (bw == BW_80) {
		if (nss == 3 || nss == 7)
			mask = BIT(6);
		else if (nss == 6)
			mask = BIT(9);
	} else {
		WARN_ON(bw != BW_40);
	}

	switch ((le16_to_cpu(mcs_map) >> (2 * (nss - 1))) & 3) {
	case IEEE80211_VHT_MCS_SUPPORT_0_7:
		mask |= 0x300;
		break;
	case IEEE80211_VHT_MCS_SUPPORT_0_8:
		mask |= 0x200;
		break;
	case IEEE80211_VHT_MCS_SUPPORT_0_9:
		break;
	default:
		mask = 0x3ff;
	}

	return 0x3ff & ~mask;
}