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
typedef  int u32 ;
struct TYPE_2__ {int wow_event_mask; } ;
struct ath_hw {TYPE_1__ wow; } ;

/* Variables and functions */
 int AH_WOW_BEACON_MISS ; 
 int AH_WOW_LINK_CHANGE ; 
 int AH_WOW_MAGIC_PATTERN_EN ; 
 int /*<<< orphan*/  AR_PCIE_PHY_REG3 ; 
 int /*<<< orphan*/  AR_PCIE_PM_CTRL ; 
 int AR_PCIE_PM_CTRL_ENA ; 
 int /*<<< orphan*/  AR_PCU_MISC_MODE3 ; 
 int AR_PMCTRL_AUX_PWR_DET ; 
 int AR_PMCTRL_HOST_PME_EN ; 
 int AR_PMCTRL_PWR_PM_CTRL_ENA ; 
 int AR_PMCTRL_PWR_STATE_D1D3 ; 
 int AR_PMCTRL_PWR_STATE_D1D3_REAL ; 
 int AR_PMCTRL_WOW_PME_CLR ; 
 int /*<<< orphan*/  AR_RSSI_THR ; 
 int /*<<< orphan*/  AR_RSSI_THR_BM_THR ; 
 int /*<<< orphan*/  AR_RTC_KEEP_AWAKE ; 
 scalar_t__ AR_SREV_9462 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_STA_ID1 ; 
 int AR_STA_ID1_PRESERVE_SEQNUM ; 
 int AR_WOW_AIFS_CNT (int /*<<< orphan*/ ) ; 
 int AR_WOW_BACK_OFF_SHIFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR_WOW_BCN_EN ; 
 int /*<<< orphan*/  AR_WOW_BCN_TIMO ; 
 int AR_WOW_BEACON_FAIL ; 
 int AR_WOW_BEACON_FAIL_EN ; 
 int AR_WOW_BEACON_TIMO ; 
 int AR_WOW_BEACON_TIMO_MAX ; 
 int /*<<< orphan*/  AR_WOW_BMISSTHRESHOLD ; 
 int /*<<< orphan*/  AR_WOW_CNT_AIFS_CNT ; 
 int /*<<< orphan*/  AR_WOW_CNT_KA_CNT ; 
 int /*<<< orphan*/  AR_WOW_CNT_SLOT_CNT ; 
 int /*<<< orphan*/  AR_WOW_COUNT ; 
 int /*<<< orphan*/  AR_WOW_KEEP_ALIVE ; 
 int AR_WOW_KEEP_ALIVE_AUTO_DIS ; 
 int AR_WOW_KEEP_ALIVE_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR_WOW_KEEP_ALIVE_DELAY ; 
 int AR_WOW_KEEP_ALIVE_FAIL ; 
 int AR_WOW_KEEP_ALIVE_FAIL_DIS ; 
 int AR_WOW_KEEP_ALIVE_NEVER ; 
 int /*<<< orphan*/  AR_WOW_KEEP_ALIVE_TIMO ; 
 int AR_WOW_MAC_INTR_EN ; 
 int AR_WOW_MAGIC_EN ; 
 int AR_WOW_MAGIC_PAT_FOUND ; 
 int /*<<< orphan*/  AR_WOW_PATTERN ; 
 int /*<<< orphan*/  AR_WOW_PATTERN_MATCH_LT_256B ; 
 int AR_WOW_PATTERN_SUPPORTED ; 
 int /*<<< orphan*/  AR_WOW_PAT_BACKOFF ; 
 int AR_WOW_SLOT_CNT (int /*<<< orphan*/ ) ; 
 int BIT (int) ; 
 int KAL_DELAY ; 
 int KAL_TIMEOUT ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ath9k_hw_mci_is_enabled (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_powermode_wow_sleep (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_wow_set_arwr_reg (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_wow_create_keep_alive_pattern (struct ath_hw*) ; 

void ath9k_hw_wow_enable(struct ath_hw *ah, u32 pattern_enable)
{
	u32 wow_event_mask;
	u32 keep_alive, magic_pattern, host_pm_ctrl;

	wow_event_mask = ah->wow.wow_event_mask;

	/*
	 * AR_PMCTRL_HOST_PME_EN - Override PME enable in configuration
	 *                         space and allow MAC to generate WoW anyway.
	 *
	 * AR_PMCTRL_PWR_PM_CTRL_ENA - ???
	 *
	 * AR_PMCTRL_AUX_PWR_DET - PCI core SYS_AUX_PWR_DET signal,
	 *                         needs to be set for WoW in PCI mode.
	 *
	 * AR_PMCTRL_WOW_PME_CLR - WoW Clear Signal going to the MAC.
	 *
	 * Set the power states appropriately and enable PME.
	 *
	 * Set and clear WOW_PME_CLEAR for the chip
	 * to generate next wow signal.
	 */
	REG_SET_BIT(ah, AR_PCIE_PM_CTRL, AR_PMCTRL_HOST_PME_EN |
		    			 AR_PMCTRL_PWR_PM_CTRL_ENA |
		    			 AR_PMCTRL_AUX_PWR_DET |
		    			 AR_PMCTRL_WOW_PME_CLR);
	REG_CLR_BIT(ah, AR_PCIE_PM_CTRL, AR_PMCTRL_WOW_PME_CLR);

	/*
	 * Random Backoff.
	 *
	 * 31:28 in AR_WOW_PATTERN : Indicates the number of bits used in the
	 *                           contention window. For value N,
	 *                           the random backoff will be selected between
	 *                           0 and (2 ^ N) - 1.
	 */
	REG_SET_BIT(ah, AR_WOW_PATTERN,
		    AR_WOW_BACK_OFF_SHIFT(AR_WOW_PAT_BACKOFF));

	/*
	 * AIFS time, Slot time, Keep Alive count.
	 */
	REG_SET_BIT(ah, AR_WOW_COUNT, AR_WOW_AIFS_CNT(AR_WOW_CNT_AIFS_CNT) |
		    		      AR_WOW_SLOT_CNT(AR_WOW_CNT_SLOT_CNT) |
		    		      AR_WOW_KEEP_ALIVE_CNT(AR_WOW_CNT_KA_CNT));
	/*
	 * Beacon timeout.
	 */
	if (pattern_enable & AH_WOW_BEACON_MISS)
		REG_WRITE(ah, AR_WOW_BCN_TIMO, AR_WOW_BEACON_TIMO);
	else
		REG_WRITE(ah, AR_WOW_BCN_TIMO, AR_WOW_BEACON_TIMO_MAX);

	/*
	 * Keep alive timeout in ms.
	 */
	if (!pattern_enable)
		REG_WRITE(ah, AR_WOW_KEEP_ALIVE_TIMO, AR_WOW_KEEP_ALIVE_NEVER);
	else
		REG_WRITE(ah, AR_WOW_KEEP_ALIVE_TIMO, KAL_TIMEOUT * 32);

	/*
	 * Keep alive delay in us.
	 */
	REG_WRITE(ah, AR_WOW_KEEP_ALIVE_DELAY, KAL_DELAY * 1000);

	/*
	 * Create keep alive pattern to respond to beacons.
	 */
	ath9k_wow_create_keep_alive_pattern(ah);

	/*
	 * Configure keep alive register.
	 */
	keep_alive = REG_READ(ah, AR_WOW_KEEP_ALIVE);

	/* Send keep alive timeouts anyway */
	keep_alive &= ~AR_WOW_KEEP_ALIVE_AUTO_DIS;

	if (pattern_enable & AH_WOW_LINK_CHANGE) {
		keep_alive &= ~AR_WOW_KEEP_ALIVE_FAIL_DIS;
		wow_event_mask |= AR_WOW_KEEP_ALIVE_FAIL;
	} else {
		keep_alive |= AR_WOW_KEEP_ALIVE_FAIL_DIS;
	}

	REG_WRITE(ah, AR_WOW_KEEP_ALIVE, keep_alive);

	/*
	 * We are relying on a bmiss failure, ensure we have
	 * enough threshold to prevent false positives.
	 */
	REG_RMW_FIELD(ah, AR_RSSI_THR, AR_RSSI_THR_BM_THR,
		      AR_WOW_BMISSTHRESHOLD);

	if (pattern_enable & AH_WOW_BEACON_MISS) {
		wow_event_mask |= AR_WOW_BEACON_FAIL;
		REG_SET_BIT(ah, AR_WOW_BCN_EN, AR_WOW_BEACON_FAIL_EN);
	} else {
		REG_CLR_BIT(ah, AR_WOW_BCN_EN, AR_WOW_BEACON_FAIL_EN);
	}

	/*
	 * Enable the magic packet registers.
	 */
	magic_pattern = REG_READ(ah, AR_WOW_PATTERN);
	magic_pattern |= AR_WOW_MAC_INTR_EN;

	if (pattern_enable & AH_WOW_MAGIC_PATTERN_EN) {
		magic_pattern |= AR_WOW_MAGIC_EN;
		wow_event_mask |= AR_WOW_MAGIC_PAT_FOUND;
	} else {
		magic_pattern &= ~AR_WOW_MAGIC_EN;
	}

	REG_WRITE(ah, AR_WOW_PATTERN, magic_pattern);

	/*
	 * Enable pattern matching for packets which are less
	 * than 256 bytes.
	 */
	REG_WRITE(ah, AR_WOW_PATTERN_MATCH_LT_256B,
		  AR_WOW_PATTERN_SUPPORTED);

	/*
	 * Set the power states appropriately and enable PME.
	 */
	host_pm_ctrl = REG_READ(ah, AR_PCIE_PM_CTRL);
	host_pm_ctrl |= AR_PMCTRL_PWR_STATE_D1D3 |
			AR_PMCTRL_HOST_PME_EN |
			AR_PMCTRL_PWR_PM_CTRL_ENA;
	host_pm_ctrl &= ~AR_PCIE_PM_CTRL_ENA;

	if (AR_SREV_9462(ah)) {
		/*
		 * This is needed to prevent the chip waking up
		 * the host within 3-4 seconds with certain
		 * platform/BIOS.
		 */
		host_pm_ctrl &= ~AR_PMCTRL_PWR_STATE_D1D3;
		host_pm_ctrl |= AR_PMCTRL_PWR_STATE_D1D3_REAL;
	}

	REG_WRITE(ah, AR_PCIE_PM_CTRL, host_pm_ctrl);

	/*
	 * Enable sequence number generation when asleep.
	 */
	REG_CLR_BIT(ah, AR_STA_ID1, AR_STA_ID1_PRESERVE_SEQNUM);

	/* To bring down WOW power low margin */
	REG_SET_BIT(ah, AR_PCIE_PHY_REG3, BIT(13));

	ath9k_hw_wow_set_arwr_reg(ah);

	if (ath9k_hw_mci_is_enabled(ah))
		REG_WRITE(ah, AR_RTC_KEEP_AWAKE, 0x2);

	/* HW WoW */
	REG_CLR_BIT(ah, AR_PCU_MISC_MODE3, BIT(5));

	ath9k_hw_set_powermode_wow_sleep(ah);
	ah->wow.wow_event_mask = wow_event_mask;
}