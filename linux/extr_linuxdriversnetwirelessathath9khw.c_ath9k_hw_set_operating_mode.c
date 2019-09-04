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
typedef  int u32 ;
struct ath_hw {int /*<<< orphan*/  is_monitoring; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_CFG ; 
 int /*<<< orphan*/  AR_CFG_AP_ADHOC_INDICATION ; 
 int /*<<< orphan*/  AR_SREV_9340_13 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_STA_ID1 ; 
 int AR_STA_ID1_ADHOC ; 
 int AR_STA_ID1_KSRCH_MODE ; 
 int AR_STA_ID1_STA_AP ; 
 int /*<<< orphan*/  ENABLE_REG_RMW_BUFFER (struct ath_hw*) ; 
#define  NL80211_IFTYPE_ADHOC 132 
#define  NL80211_IFTYPE_AP 131 
#define  NL80211_IFTYPE_MESH_POINT 130 
#define  NL80211_IFTYPE_OCB 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW (struct ath_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  REG_RMW_BUFFER_FLUSH (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_hw_set_operating_mode(struct ath_hw *ah, int opmode)
{
	u32 mask = AR_STA_ID1_STA_AP | AR_STA_ID1_ADHOC;
	u32 set = AR_STA_ID1_KSRCH_MODE;

	ENABLE_REG_RMW_BUFFER(ah);
	switch (opmode) {
	case NL80211_IFTYPE_ADHOC:
		if (!AR_SREV_9340_13(ah)) {
			set |= AR_STA_ID1_ADHOC;
			REG_SET_BIT(ah, AR_CFG, AR_CFG_AP_ADHOC_INDICATION);
			break;
		}
		/* fall through */
	case NL80211_IFTYPE_OCB:
	case NL80211_IFTYPE_MESH_POINT:
	case NL80211_IFTYPE_AP:
		set |= AR_STA_ID1_STA_AP;
		/* fall through */
	case NL80211_IFTYPE_STATION:
		REG_CLR_BIT(ah, AR_CFG, AR_CFG_AP_ADHOC_INDICATION);
		break;
	default:
		if (!ah->is_monitoring)
			set = 0;
		break;
	}
	REG_RMW(ah, AR_STA_ID1, set, mask);
	REG_RMW_BUFFER_FLUSH(ah);
}