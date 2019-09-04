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
typedef  int u8 ;
struct ath9k_hw_capabilities {int chip_chainmask; } ;
struct ath_hw {struct ath9k_hw_capabilities caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_65NM_CH0_RXTX4 ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH0_RXTX4_THERM_ON ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH0_RXTX4_THERM_ON_OVR ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH1_RXTX4 ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH2_RXTX4 ; 
 int BIT (int) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ar9003_hw_get_thermometer (struct ath_hw*) ; 

__attribute__((used)) static void ar9003_hw_thermometer_apply(struct ath_hw *ah)
{
	struct ath9k_hw_capabilities *pCap = &ah->caps;
	int thermometer = ar9003_hw_get_thermometer(ah);
	u8 therm_on = (thermometer < 0) ? 0 : 1;

	REG_RMW_FIELD(ah, AR_PHY_65NM_CH0_RXTX4,
		      AR_PHY_65NM_CH0_RXTX4_THERM_ON_OVR, therm_on);
	if (pCap->chip_chainmask & BIT(1))
		REG_RMW_FIELD(ah, AR_PHY_65NM_CH1_RXTX4,
			      AR_PHY_65NM_CH0_RXTX4_THERM_ON_OVR, therm_on);
	if (pCap->chip_chainmask & BIT(2))
		REG_RMW_FIELD(ah, AR_PHY_65NM_CH2_RXTX4,
			      AR_PHY_65NM_CH0_RXTX4_THERM_ON_OVR, therm_on);

	therm_on = thermometer == 0;
	REG_RMW_FIELD(ah, AR_PHY_65NM_CH0_RXTX4,
		      AR_PHY_65NM_CH0_RXTX4_THERM_ON, therm_on);
	if (pCap->chip_chainmask & BIT(1)) {
		therm_on = thermometer == 1;
		REG_RMW_FIELD(ah, AR_PHY_65NM_CH1_RXTX4,
			      AR_PHY_65NM_CH0_RXTX4_THERM_ON, therm_on);
	}
	if (pCap->chip_chainmask & BIT(2)) {
		therm_on = thermometer == 2;
		REG_RMW_FIELD(ah, AR_PHY_65NM_CH2_RXTX4,
			      AR_PHY_65NM_CH0_RXTX4_THERM_ON, therm_on);
	}
}