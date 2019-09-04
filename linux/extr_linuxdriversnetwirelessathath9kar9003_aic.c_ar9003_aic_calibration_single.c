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
typedef  int /*<<< orphan*/  u8 ;
struct ath9k_hw_mci {int /*<<< orphan*/  config; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_MCI_CONFIG_AIC_CAL_NUM_CHAN ; 
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9003_aic_cal_continue (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_aic_cal_start (struct ath_hw*,int) ; 

u8 ar9003_aic_calibration_single(struct ath_hw *ah)
{
	struct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u8 cal_ret;
	int num_chan;

	num_chan = MS(mci_hw->config, ATH_MCI_CONFIG_AIC_CAL_NUM_CHAN);

	(void) ar9003_aic_cal_start(ah, num_chan);
	cal_ret = ar9003_aic_cal_continue(ah, true);

	return cal_ret;
}