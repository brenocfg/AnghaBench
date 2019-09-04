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
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_BB_THERM_ADC_3 ; 
 int /*<<< orphan*/  AR_PHY_BB_THERM_ADC_3_THERM_ADC_OFFSET ; 
 int /*<<< orphan*/  AR_PHY_BB_THERM_ADC_3_THERM_ADC_SCALE_GAIN ; 
 int /*<<< orphan*/  AR_SREV_9462_20_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar9300_otp_read_word (struct ath_hw*,int,int*) ; 

__attribute__((used)) static void ar9003_hw_thermo_cal_apply(struct ath_hw *ah)
{
	u32 data, ko, kg;

	if (!AR_SREV_9462_20_OR_LATER(ah))
		return;

	ar9300_otp_read_word(ah, 1, &data);
	ko = data & 0xff;
	kg = (data >> 8) & 0xff;
	if (ko || kg) {
		REG_RMW_FIELD(ah, AR_PHY_BB_THERM_ADC_3,
			      AR_PHY_BB_THERM_ADC_3_THERM_ADC_OFFSET, ko);
		REG_RMW_FIELD(ah, AR_PHY_BB_THERM_ADC_3,
			      AR_PHY_BB_THERM_ADC_3_THERM_ADC_SCALE_GAIN,
			      kg + 256);
	}
}