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

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
#define  IEEE80211_HE_MCS_NOT_SUPPORTED 131 
#define  IEEE80211_HE_MCS_SUPPORT_0_11 130 
#define  IEEE80211_HE_MCS_SUPPORT_0_7 129 
#define  IEEE80211_HE_MCS_SUPPORT_0_9 128 
 int /*<<< orphan*/  IWL_TLC_MNG_HT_RATE_MCS11 ; 
 int /*<<< orphan*/  IWL_TLC_MNG_HT_RATE_MCS7 ; 
 int /*<<< orphan*/  IWL_TLC_MNG_HT_RATE_MCS9 ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 

__attribute__((used)) static u16 rs_fw_he_ieee80211_mcs_to_rs_mcs(u16 mcs)
{
	switch (mcs) {
	case IEEE80211_HE_MCS_SUPPORT_0_7:
		return BIT(IWL_TLC_MNG_HT_RATE_MCS7 + 1) - 1;
	case IEEE80211_HE_MCS_SUPPORT_0_9:
		return BIT(IWL_TLC_MNG_HT_RATE_MCS9 + 1) - 1;
	case IEEE80211_HE_MCS_SUPPORT_0_11:
		return BIT(IWL_TLC_MNG_HT_RATE_MCS11 + 1) - 1;
	case IEEE80211_HE_MCS_NOT_SUPPORTED:
		return 0;
	}

	WARN(1, "invalid HE MCS %d\n", mcs);
	return 0;
}