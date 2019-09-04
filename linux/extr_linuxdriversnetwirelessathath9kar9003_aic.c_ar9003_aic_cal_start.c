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
typedef  int u8 ;
struct ath9k_hw_aic {int aic_cal_start_time; int aic_cal_state; scalar_t__ aic_caled_chan; scalar_t__* aic_sram; } ;
struct TYPE_2__ {struct ath9k_hw_aic aic; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;

/* Variables and functions */
 int AIC_CAL_STATE_STARTED ; 
 int /*<<< orphan*/  AR_PHY_AIC_BTTX_PWR_THR ; 
 int /*<<< orphan*/  AR_PHY_AIC_BT_IDLE_CFG ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_BT_REF_DELAY ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_CH_VALID_RESET ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_COM_ATT_DB_BACKOFF ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_COM_ATT_DB_EST_ISO ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_COM_ATT_DB_FIXED ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_CONV_CHECK_FACTOR ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_ENABLE ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_ISO_EST_INIT_SETTING ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_MAX_HOP_COUNT ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_MIN_VALID_COUNT ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_PERF_CHECK_FACTOR ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_PWR_EST_LONG ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_ROT_ATT_DB_EST_ISO ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_ROT_IDX_CORR ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_STEP_SIZE_CORR ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_SYNTH_AFTER_BTRX ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_SYNTH_SETTLING ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_SYNTH_TOGGLE ; 
 int /*<<< orphan*/  AR_PHY_AIC_CAL_TARGET_MAG_SETTING ; 
 scalar_t__ AR_PHY_AIC_CTRL_0_B0 ; 
 scalar_t__ AR_PHY_AIC_CTRL_0_B1 ; 
 scalar_t__ AR_PHY_AIC_CTRL_1_B0 ; 
 scalar_t__ AR_PHY_AIC_CTRL_1_B1 ; 
 scalar_t__ AR_PHY_AIC_CTRL_2_B0 ; 
 scalar_t__ AR_PHY_AIC_CTRL_3_B0 ; 
 scalar_t__ AR_PHY_AIC_CTRL_4_B0 ; 
 scalar_t__ AR_PHY_AIC_CTRL_4_B1 ; 
 int /*<<< orphan*/  AR_PHY_AIC_ENABLE ; 
 int /*<<< orphan*/  AR_PHY_AIC_F_WLAN ; 
 int /*<<< orphan*/  AR_PHY_AIC_MON_ENABLE ; 
 int /*<<< orphan*/  AR_PHY_AIC_MON_MAX_HOP_COUNT ; 
 int /*<<< orphan*/  AR_PHY_AIC_MON_MIN_STALE_COUNT ; 
 int /*<<< orphan*/  AR_PHY_AIC_MON_PD_TALLY_SCALING ; 
 int /*<<< orphan*/  AR_PHY_AIC_MON_PERF_THR ; 
 int /*<<< orphan*/  AR_PHY_AIC_MON_PWR_EST_LONG ; 
 int /*<<< orphan*/  AR_PHY_AIC_RADIO_DELAY ; 
 int /*<<< orphan*/  AR_PHY_AIC_ROT_IDX_COUNT_MAX ; 
 int /*<<< orphan*/  AR_PHY_AIC_RSSI_MAX ; 
 int /*<<< orphan*/  AR_PHY_AIC_RSSI_MIN ; 
 scalar_t__ AR_PHY_AIC_SRAM_ADDR_B0 ; 
 scalar_t__ AR_PHY_AIC_SRAM_DATA_B0 ; 
 int /*<<< orphan*/  AR_PHY_AIC_STDBY_COM_ATT_DB ; 
 int /*<<< orphan*/  AR_PHY_AIC_STDBY_COND ; 
 int /*<<< orphan*/  AR_PHY_AIC_STDBY_ROT_ATT_DB ; 
 scalar_t__ AR_TSF_L32 ; 
 int ATH_AIC_BT_AIC_ENABLE ; 
 scalar_t__ ATH_AIC_BT_JUPITER_CTRL ; 
 int ATH_AIC_MAX_BT_CHANNEL ; 
 int ATH_AIC_SRAM_AUTO_INCREMENT ; 
 int ATH_AIC_SRAM_CAL_OFFSET ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,scalar_t__,int /*<<< orphan*/ ) ; 
 int REG_READ (struct ath_hw*,scalar_t__) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,scalar_t__,int) ; 
 int SM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9003_aic_gain_table (struct ath_hw*) ; 

__attribute__((used)) static u8 ar9003_aic_cal_start(struct ath_hw *ah, u8 min_valid_count)
{
	struct ath9k_hw_aic *aic = &ah->btcoex_hw.aic;
	int i;

	/* Write to Gain table with auto increment enabled. */
	REG_WRITE(ah, (AR_PHY_AIC_SRAM_ADDR_B0 + 0x3000),
		  (ATH_AIC_SRAM_AUTO_INCREMENT |
		   ATH_AIC_SRAM_CAL_OFFSET));

	for (i = 0; i < ATH_AIC_MAX_BT_CHANNEL; i++) {
		REG_WRITE(ah, (AR_PHY_AIC_SRAM_DATA_B0 + 0x3000), 0);
		aic->aic_sram[i] = 0;
	}

	REG_WRITE(ah, AR_PHY_AIC_CTRL_0_B0,
		  (SM(0, AR_PHY_AIC_MON_ENABLE) |
		   SM(127, AR_PHY_AIC_CAL_MAX_HOP_COUNT) |
		   SM(min_valid_count, AR_PHY_AIC_CAL_MIN_VALID_COUNT) |
		   SM(37, AR_PHY_AIC_F_WLAN) |
		   SM(1, AR_PHY_AIC_CAL_CH_VALID_RESET) |
		   SM(0, AR_PHY_AIC_CAL_ENABLE) |
		   SM(0x40, AR_PHY_AIC_BTTX_PWR_THR) |
		   SM(0, AR_PHY_AIC_ENABLE)));

	REG_WRITE(ah, AR_PHY_AIC_CTRL_0_B1,
		  (SM(0, AR_PHY_AIC_MON_ENABLE) |
		   SM(1, AR_PHY_AIC_CAL_CH_VALID_RESET) |
		   SM(0, AR_PHY_AIC_CAL_ENABLE) |
		   SM(0x40, AR_PHY_AIC_BTTX_PWR_THR) |
		   SM(0, AR_PHY_AIC_ENABLE)));

	REG_WRITE(ah, AR_PHY_AIC_CTRL_1_B0,
		  (SM(8, AR_PHY_AIC_CAL_BT_REF_DELAY) |
		   SM(0, AR_PHY_AIC_BT_IDLE_CFG) |
		   SM(1, AR_PHY_AIC_STDBY_COND) |
		   SM(37, AR_PHY_AIC_STDBY_ROT_ATT_DB) |
		   SM(5, AR_PHY_AIC_STDBY_COM_ATT_DB) |
		   SM(15, AR_PHY_AIC_RSSI_MAX) |
		   SM(0, AR_PHY_AIC_RSSI_MIN)));

	REG_WRITE(ah, AR_PHY_AIC_CTRL_1_B1,
		  (SM(15, AR_PHY_AIC_RSSI_MAX) |
		   SM(0, AR_PHY_AIC_RSSI_MIN)));

	REG_WRITE(ah, AR_PHY_AIC_CTRL_2_B0,
		  (SM(44, AR_PHY_AIC_RADIO_DELAY) |
		   SM(8, AR_PHY_AIC_CAL_STEP_SIZE_CORR) |
		   SM(12, AR_PHY_AIC_CAL_ROT_IDX_CORR) |
		   SM(2, AR_PHY_AIC_CAL_CONV_CHECK_FACTOR) |
		   SM(5, AR_PHY_AIC_ROT_IDX_COUNT_MAX) |
		   SM(0, AR_PHY_AIC_CAL_SYNTH_TOGGLE) |
		   SM(0, AR_PHY_AIC_CAL_SYNTH_AFTER_BTRX) |
		   SM(200, AR_PHY_AIC_CAL_SYNTH_SETTLING)));

	REG_WRITE(ah, AR_PHY_AIC_CTRL_3_B0,
		  (SM(2, AR_PHY_AIC_MON_MAX_HOP_COUNT) |
		   SM(1, AR_PHY_AIC_MON_MIN_STALE_COUNT) |
		   SM(1, AR_PHY_AIC_MON_PWR_EST_LONG) |
		   SM(2, AR_PHY_AIC_MON_PD_TALLY_SCALING) |
		   SM(10, AR_PHY_AIC_MON_PERF_THR) |
		   SM(2, AR_PHY_AIC_CAL_TARGET_MAG_SETTING) |
		   SM(1, AR_PHY_AIC_CAL_PERF_CHECK_FACTOR) |
		   SM(1, AR_PHY_AIC_CAL_PWR_EST_LONG)));

	REG_WRITE(ah, AR_PHY_AIC_CTRL_4_B0,
		  (SM(2, AR_PHY_AIC_CAL_ROT_ATT_DB_EST_ISO) |
		   SM(3, AR_PHY_AIC_CAL_COM_ATT_DB_EST_ISO) |
		   SM(0, AR_PHY_AIC_CAL_ISO_EST_INIT_SETTING) |
		   SM(2, AR_PHY_AIC_CAL_COM_ATT_DB_BACKOFF) |
		   SM(1, AR_PHY_AIC_CAL_COM_ATT_DB_FIXED)));

	REG_WRITE(ah, AR_PHY_AIC_CTRL_4_B1,
		  (SM(2, AR_PHY_AIC_CAL_ROT_ATT_DB_EST_ISO) |
		   SM(3, AR_PHY_AIC_CAL_COM_ATT_DB_EST_ISO) |
		   SM(0, AR_PHY_AIC_CAL_ISO_EST_INIT_SETTING) |
		   SM(2, AR_PHY_AIC_CAL_COM_ATT_DB_BACKOFF) |
		   SM(1, AR_PHY_AIC_CAL_COM_ATT_DB_FIXED)));

	ar9003_aic_gain_table(ah);

	/* Need to enable AIC reference signal in BT modem. */
	REG_WRITE(ah, ATH_AIC_BT_JUPITER_CTRL,
		  (REG_READ(ah, ATH_AIC_BT_JUPITER_CTRL) |
		   ATH_AIC_BT_AIC_ENABLE));

	aic->aic_cal_start_time = REG_READ(ah, AR_TSF_L32);

	/* Start calibration */
	REG_CLR_BIT(ah, AR_PHY_AIC_CTRL_0_B1, AR_PHY_AIC_CAL_ENABLE);
	REG_SET_BIT(ah, AR_PHY_AIC_CTRL_0_B1, AR_PHY_AIC_CAL_CH_VALID_RESET);
	REG_SET_BIT(ah, AR_PHY_AIC_CTRL_0_B1, AR_PHY_AIC_CAL_ENABLE);

	aic->aic_caled_chan = 0;
	aic->aic_cal_state = AIC_CAL_STATE_STARTED;

	return aic->aic_cal_state;
}