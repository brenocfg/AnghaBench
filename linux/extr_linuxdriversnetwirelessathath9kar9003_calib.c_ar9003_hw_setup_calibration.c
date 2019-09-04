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
struct ath_hw {int dummy; } ;
struct ath_common {int dummy; } ;
struct ath9k_cal_list {TYPE_1__* calData; } ;
struct TYPE_2__ {int calType; int /*<<< orphan*/  calCountMax; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_CALMODE ; 
 int /*<<< orphan*/  AR_PHY_CALMODE_IQ ; 
 int /*<<< orphan*/  AR_PHY_TIMING4 ; 
 int /*<<< orphan*/  AR_PHY_TIMING4_DO_CAL ; 
 int /*<<< orphan*/  AR_PHY_TIMING4_IQCAL_LOG_COUNT_MAX ; 
 int /*<<< orphan*/  CALIBRATE ; 
#define  IQ_MISMATCH_CAL 128 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 

__attribute__((used)) static void ar9003_hw_setup_calibration(struct ath_hw *ah,
					struct ath9k_cal_list *currCal)
{
	struct ath_common *common = ath9k_hw_common(ah);

	/* Select calibration to run */
	switch (currCal->calData->calType) {
	case IQ_MISMATCH_CAL:
		/*
		 * Start calibration with
		 * 2^(INIT_IQCAL_LOG_COUNT_MAX+1) samples
		 */
		REG_RMW_FIELD(ah, AR_PHY_TIMING4,
			      AR_PHY_TIMING4_IQCAL_LOG_COUNT_MAX,
			      currCal->calData->calCountMax);
		REG_WRITE(ah, AR_PHY_CALMODE, AR_PHY_CALMODE_IQ);

		ath_dbg(common, CALIBRATE,
			"starting IQ Mismatch Calibration\n");

		/* Kick-off cal */
		REG_SET_BIT(ah, AR_PHY_TIMING4, AR_PHY_TIMING4_DO_CAL);
		break;
	default:
		ath_err(common, "Invalid calibration type\n");
		break;
	}
}