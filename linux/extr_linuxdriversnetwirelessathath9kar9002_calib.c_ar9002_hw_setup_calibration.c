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
#define  ADC_DC_CAL 130 
#define  ADC_GAIN_CAL 129 
 int /*<<< orphan*/  AR_PHY_CALMODE ; 
 int /*<<< orphan*/  AR_PHY_CALMODE_ADC_DC_PER ; 
 int /*<<< orphan*/  AR_PHY_CALMODE_ADC_GAIN ; 
 int /*<<< orphan*/  AR_PHY_CALMODE_IQ ; 
 int /*<<< orphan*/  AR_PHY_TIMING_CTRL4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR_PHY_TIMING_CTRL4_DO_CAL ; 
 int /*<<< orphan*/  AR_PHY_TIMING_CTRL4_IQCAL_LOG_COUNT_MAX ; 
 int /*<<< orphan*/  CALIBRATE ; 
#define  IQ_MISMATCH_CAL 128 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ar9002_hw_setup_calibration(struct ath_hw *ah,
					struct ath9k_cal_list *currCal)
{
	struct ath_common *common = ath9k_hw_common(ah);

	REG_RMW_FIELD(ah, AR_PHY_TIMING_CTRL4(0),
		      AR_PHY_TIMING_CTRL4_IQCAL_LOG_COUNT_MAX,
		      currCal->calData->calCountMax);

	switch (currCal->calData->calType) {
	case IQ_MISMATCH_CAL:
		REG_WRITE(ah, AR_PHY_CALMODE, AR_PHY_CALMODE_IQ);
		ath_dbg(common, CALIBRATE,
			"starting IQ Mismatch Calibration\n");
		break;
	case ADC_GAIN_CAL:
		REG_WRITE(ah, AR_PHY_CALMODE, AR_PHY_CALMODE_ADC_GAIN);
		ath_dbg(common, CALIBRATE, "starting ADC Gain Calibration\n");
		break;
	case ADC_DC_CAL:
		REG_WRITE(ah, AR_PHY_CALMODE, AR_PHY_CALMODE_ADC_DC_PER);
		ath_dbg(common, CALIBRATE, "starting ADC DC Calibration\n");
		break;
	}

	REG_SET_BIT(ah, AR_PHY_TIMING_CTRL4(0),
		    AR_PHY_TIMING_CTRL4_DO_CAL);
}