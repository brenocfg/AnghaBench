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
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw {int bb_watchdog_last_status; } ;

/* Variables and functions */
 int AR9300_DFS_FIRPWR ; 
 int /*<<< orphan*/  AR_PHY_RADAR_0 ; 
 int /*<<< orphan*/  AR_PHY_RADAR_0_FIRPWR ; 
 int /*<<< orphan*/  AR_SREV_9340 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9531 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9561 (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool ar9003_hw_bb_watchdog_check(struct ath_hw *ah)
{
	u32 val;

	switch(ah->bb_watchdog_last_status) {
	case 0x04000539:
		val = REG_READ(ah, AR_PHY_RADAR_0);
		val &= (~AR_PHY_RADAR_0_FIRPWR);
		val |= SM(0x7f, AR_PHY_RADAR_0_FIRPWR);
		REG_WRITE(ah, AR_PHY_RADAR_0, val);
		udelay(1);
		val = REG_READ(ah, AR_PHY_RADAR_0);
		val &= ~AR_PHY_RADAR_0_FIRPWR;
		val |= SM(AR9300_DFS_FIRPWR, AR_PHY_RADAR_0_FIRPWR);
		REG_WRITE(ah, AR_PHY_RADAR_0, val);

		return false;
	case 0x1300000a:
		return false;
	case 0x0400000a:
	case 0x04000b09:
		return true;
	case 0x04000409:
		if (AR_SREV_9340(ah) || AR_SREV_9531(ah) || AR_SREV_9561(ah))
			return false;
		else
			return true;
	default:
		/*
		 * For any other unknown signatures, do a
		 * full chip reset.
		 */
		return true;
	}
}