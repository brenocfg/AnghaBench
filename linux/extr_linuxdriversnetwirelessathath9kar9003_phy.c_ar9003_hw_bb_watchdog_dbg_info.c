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
struct ath_hw {int /*<<< orphan*/  bb_watchdog_last_status; } ;
struct TYPE_2__ {int cycles; int rx_busy; int rx_frame; int tx_frame; } ;
struct ath_common {int debug_mask; TYPE_1__ cc_survey; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_GEN_CTRL ; 
 int /*<<< orphan*/  AR_PHY_WATCHDOG_AGC_SM ; 
 int /*<<< orphan*/  AR_PHY_WATCHDOG_CTL_1 ; 
 int /*<<< orphan*/  AR_PHY_WATCHDOG_CTL_2 ; 
 int /*<<< orphan*/  AR_PHY_WATCHDOG_DET_HANG ; 
 int /*<<< orphan*/  AR_PHY_WATCHDOG_INFO ; 
 int /*<<< orphan*/  AR_PHY_WATCHDOG_RADAR_SM ; 
 int /*<<< orphan*/  AR_PHY_WATCHDOG_RX_CCK_SM ; 
 int /*<<< orphan*/  AR_PHY_WATCHDOG_RX_OFDM_SM ; 
 int /*<<< orphan*/  AR_PHY_WATCHDOG_SRCH_SM ; 
 int /*<<< orphan*/  AR_PHY_WATCHDOG_TX_CCK_SM ; 
 int /*<<< orphan*/  AR_PHY_WATCHDOG_TX_OFDM_SM ; 
 int ATH_DBG_RESET ; 
 int /*<<< orphan*/  MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESET ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ likely (int) ; 

void ar9003_hw_bb_watchdog_dbg_info(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	u32 status;

	if (likely(!(common->debug_mask & ATH_DBG_RESET)))
		return;

	status = ah->bb_watchdog_last_status;
	ath_dbg(common, RESET,
		"\n==== BB update: BB status=0x%08x ====\n", status);
	ath_dbg(common, RESET,
		"** BB state: wd=%u det=%u rdar=%u rOFDM=%d rCCK=%u tOFDM=%u tCCK=%u agc=%u src=%u **\n",
		MS(status, AR_PHY_WATCHDOG_INFO),
		MS(status, AR_PHY_WATCHDOG_DET_HANG),
		MS(status, AR_PHY_WATCHDOG_RADAR_SM),
		MS(status, AR_PHY_WATCHDOG_RX_OFDM_SM),
		MS(status, AR_PHY_WATCHDOG_RX_CCK_SM),
		MS(status, AR_PHY_WATCHDOG_TX_OFDM_SM),
		MS(status, AR_PHY_WATCHDOG_TX_CCK_SM),
		MS(status, AR_PHY_WATCHDOG_AGC_SM),
		MS(status, AR_PHY_WATCHDOG_SRCH_SM));

	ath_dbg(common, RESET, "** BB WD cntl: cntl1=0x%08x cntl2=0x%08x **\n",
		REG_READ(ah, AR_PHY_WATCHDOG_CTL_1),
		REG_READ(ah, AR_PHY_WATCHDOG_CTL_2));
	ath_dbg(common, RESET, "** BB mode: BB_gen_controls=0x%08x **\n",
		REG_READ(ah, AR_PHY_GEN_CTRL));

#define PCT(_field) (common->cc_survey._field * 100 / common->cc_survey.cycles)
	if (common->cc_survey.cycles)
		ath_dbg(common, RESET,
			"** BB busy times: rx_clear=%d%%, rx_frame=%d%%, tx_frame=%d%% **\n",
			PCT(rx_busy), PCT(rx_frame), PCT(tx_frame));

	ath_dbg(common, RESET, "==== BB update: done ====\n\n");
}