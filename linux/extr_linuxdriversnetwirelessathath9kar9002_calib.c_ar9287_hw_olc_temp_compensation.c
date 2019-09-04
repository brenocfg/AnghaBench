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
typedef  int /*<<< orphan*/  u32 ;
struct ath_hw {scalar_t__ initPDADC; TYPE_1__* eep_ops; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {scalar_t__ (* get_eeprom ) (struct ath_hw*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_CH0_TX_PWRCTRL11 ; 
 int /*<<< orphan*/  AR_PHY_CH1_TX_PWRCTRL11 ; 
 int /*<<< orphan*/  AR_PHY_TX_PWRCTRL4 ; 
 int /*<<< orphan*/  AR_PHY_TX_PWRCTRL_OLPC_TEMP_COMP ; 
 int /*<<< orphan*/  AR_PHY_TX_PWRCTRL_PD_AVG_OUT ; 
 int /*<<< orphan*/  EEP_TEMPSENSE_SLOPE ; 
 scalar_t__ MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub1 (struct ath_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar9287_hw_olc_temp_compensation(struct ath_hw *ah)
{
	u32 rddata;
	int32_t delta, currPDADC, slope;

	rddata = REG_READ(ah, AR_PHY_TX_PWRCTRL4);
	currPDADC = MS(rddata, AR_PHY_TX_PWRCTRL_PD_AVG_OUT);

	if (ah->initPDADC == 0 || currPDADC == 0) {
		/*
		 * Zero value indicates that no frames have been transmitted
		 * yet, can't do temperature compensation until frames are
		 * transmitted.
		 */
		return;
	} else {
		slope = ah->eep_ops->get_eeprom(ah, EEP_TEMPSENSE_SLOPE);

		if (slope == 0) { /* to avoid divide by zero case */
			delta = 0;
		} else {
			delta = ((currPDADC - ah->initPDADC)*4) / slope;
		}
		REG_RMW_FIELD(ah, AR_PHY_CH0_TX_PWRCTRL11,
			      AR_PHY_TX_PWRCTRL_OLPC_TEMP_COMP, delta);
		REG_RMW_FIELD(ah, AR_PHY_CH1_TX_PWRCTRL11,
			      AR_PHY_TX_PWRCTRL_OLPC_TEMP_COMP, delta);
	}
}