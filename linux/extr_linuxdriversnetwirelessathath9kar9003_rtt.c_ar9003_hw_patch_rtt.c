#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ath_hw {TYPE_1__* caldata; } ;
struct TYPE_2__ {int* caldac; int** rtt_table; int /*<<< orphan*/  cal_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_AGC (int) ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXRF_AGC_AGC_OVERRIDE ; 
 int REG_READ_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_PKDET_DONE ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ar9003_hw_patch_rtt(struct ath_hw *ah, int index, int chain)
{
	int agc, caldac;

	if (!test_bit(SW_PKDET_DONE, &ah->caldata->cal_flags))
		return;

	if ((index != 5) || (chain >= 2))
		return;

	agc = REG_READ_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
			     AR_PHY_65NM_RXRF_AGC_AGC_OVERRIDE);
	if (!agc)
		return;

	caldac = ah->caldata->caldac[chain];
	ah->caldata->rtt_table[chain][index] &= 0xFFFF05FF;
	caldac = (caldac & 0x20) | ((caldac & 0x1F) << 7);
	ah->caldata->rtt_table[chain][index] |= (caldac << 4);
}