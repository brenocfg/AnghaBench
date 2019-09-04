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
typedef  int u32 ;
struct ath9k_hw_aic {int* aic_sram; int aic_caled_chan; int /*<<< orphan*/  aic_cal_state; } ;
struct ath9k_hw_mci {int /*<<< orphan*/  config; } ;
struct TYPE_2__ {struct ath9k_hw_aic aic; struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC_CAL_STATE_ERROR ; 
 int AR_PHY_AIC_CAL_CH_VALID_RESET ; 
 int AR_PHY_AIC_CAL_ENABLE ; 
 int /*<<< orphan*/  AR_PHY_AIC_CTRL_0_B1 ; 
 int /*<<< orphan*/  AR_PHY_AIC_SRAM_ADDR_B1 ; 
 int /*<<< orphan*/  AR_PHY_AIC_SRAM_DATA_B1 ; 
 int ATH_AIC_MAX_BT_CHANNEL ; 
 int ATH_AIC_SRAM_AUTO_INCREMENT ; 
 int ATH_AIC_SRAM_CAL_OFFSET ; 
 int /*<<< orphan*/  ATH_MCI_CONFIG_AIC_CAL_NUM_CHAN ; 
 int /*<<< orphan*/  MCI ; 
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar9003_aic_cal_done (struct ath_hw*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u8 ar9003_aic_cal_continue(struct ath_hw *ah, bool cal_once)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	struct ath9k_hw_aic *aic = &ah->btcoex_hw.aic;
	int i, num_chan;

	num_chan = MS(mci_hw->config, ATH_MCI_CONFIG_AIC_CAL_NUM_CHAN);

	if (!num_chan) {
		aic->aic_cal_state = AIC_CAL_STATE_ERROR;
		return aic->aic_cal_state;
	}

	if (cal_once) {
		for (i = 0; i < 10000; i++) {
			if ((REG_READ(ah, AR_PHY_AIC_CTRL_0_B1) &
			     AR_PHY_AIC_CAL_ENABLE) == 0)
				break;

			udelay(100);
		}
	}

	/*
	 * Use AR_PHY_AIC_CAL_ENABLE bit instead of AR_PHY_AIC_CAL_DONE.
	 * Sometimes CAL_DONE bit is not asserted.
	 */
	if ((REG_READ(ah, AR_PHY_AIC_CTRL_0_B1) &
	     AR_PHY_AIC_CAL_ENABLE) != 0) {
		ath_dbg(common, MCI, "AIC cal is not done after 40ms");
		goto exit;
	}

	REG_WRITE(ah, AR_PHY_AIC_SRAM_ADDR_B1,
		  (ATH_AIC_SRAM_CAL_OFFSET | ATH_AIC_SRAM_AUTO_INCREMENT));

	for (i = 0; i < ATH_AIC_MAX_BT_CHANNEL; i++) {
		u32 value;

		value = REG_READ(ah, AR_PHY_AIC_SRAM_DATA_B1);

		if (value & 0x01) {
			if (aic->aic_sram[i] == 0)
				aic->aic_caled_chan++;

			aic->aic_sram[i] = value;

			if (!cal_once)
				break;
		}
	}

	if ((aic->aic_caled_chan >= num_chan) || cal_once) {
		ar9003_aic_cal_done(ah);
	} else {
		/* Start calibration */
		REG_CLR_BIT(ah, AR_PHY_AIC_CTRL_0_B1, AR_PHY_AIC_CAL_ENABLE);
		REG_SET_BIT(ah, AR_PHY_AIC_CTRL_0_B1,
			    AR_PHY_AIC_CAL_CH_VALID_RESET);
		REG_SET_BIT(ah, AR_PHY_AIC_CTRL_0_B1, AR_PHY_AIC_CAL_ENABLE);
	}
exit:
	return aic->aic_cal_state;

}