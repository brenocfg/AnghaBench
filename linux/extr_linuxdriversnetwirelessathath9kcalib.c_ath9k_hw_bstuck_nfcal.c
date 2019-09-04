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
struct ath_hw {int /*<<< orphan*/  curchan; struct ath9k_hw_cal_data* caldata; } ;
struct ath9k_hw_cal_data {int /*<<< orphan*/  cal_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_AGC_CONTROL ; 
 int AR_PHY_AGC_CONTROL_NF ; 
 int /*<<< orphan*/  NFCAL_INTF ; 
 int /*<<< orphan*/  NFCAL_PENDING ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_getnf (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_start_nfcal (struct ath_hw*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void ath9k_hw_bstuck_nfcal(struct ath_hw *ah)
{
	struct ath9k_hw_cal_data *caldata = ah->caldata;

	if (unlikely(!caldata))
		return;

	/*
	 * If beacons are stuck, the most likely cause is interference.
	 * Triggering a noise floor calibration at this point helps the
	 * hardware adapt to a noisy environment much faster.
	 * To ensure that we recover from stuck beacons quickly, let
	 * the baseband update the internal NF value itself, similar to
	 * what is being done after a full reset.
	 */
	if (!test_bit(NFCAL_PENDING, &caldata->cal_flags))
		ath9k_hw_start_nfcal(ah, true);
	else if (!(REG_READ(ah, AR_PHY_AGC_CONTROL) & AR_PHY_AGC_CONTROL_NF))
		ath9k_hw_getnf(ah, ah->curchan);

	set_bit(NFCAL_INTF, &caldata->cal_flags);
}