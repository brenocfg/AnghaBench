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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct ath_hw {int /*<<< orphan*/  txchainmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_CORRECTION_FOR_THREE_CHAIN ; 
 int /*<<< orphan*/  POWER_CORRECTION_FOR_TWO_CHAIN ; 
 int ar5416_get_ntxchains (int /*<<< orphan*/ ) ; 

u16 ath9k_hw_get_scaled_power(struct ath_hw *ah, u16 power_limit,
			      u8 antenna_reduction)
{
	u16 reduction = antenna_reduction;

	/*
	 * Reduce scaled Power by number of chains active
	 * to get the per chain tx power level.
	 */
	switch (ar5416_get_ntxchains(ah->txchainmask)) {
	case 1:
		break;
	case 2:
		reduction += POWER_CORRECTION_FOR_TWO_CHAIN;
		break;
	case 3:
		reduction += POWER_CORRECTION_FOR_THREE_CHAIN;
		break;
	}

	if (power_limit > reduction)
		power_limit -= reduction;
	else
		power_limit = 0;

	return power_limit;
}