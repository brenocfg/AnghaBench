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
struct ath_hw {int WARegVal; } ;

/* Variables and functions */
 int AH_WAIT_TIMEOUT ; 
 int AR9340_INTR_SYNC_LOCAL_TIMEOUT ; 
 int /*<<< orphan*/  AR_CFG ; 
 int /*<<< orphan*/  AR_CFG_HALT_ACK ; 
 int /*<<< orphan*/  AR_CFG_HALT_REQ ; 
 int /*<<< orphan*/  AR_INTR_SYNC_CAUSE ; 
 int /*<<< orphan*/  AR_INTR_SYNC_ENABLE ; 
 int AR_INTR_SYNC_LOCAL_TIMEOUT ; 
 int AR_INTR_SYNC_RADM_CPL_TIMEOUT ; 
 int /*<<< orphan*/  AR_RC ; 
 int AR_RC_AHB ; 
 int AR_RC_HOSTIF ; 
 int /*<<< orphan*/  AR_RTC_DERIVED_CLK ; 
 int /*<<< orphan*/  AR_RTC_DERIVED_CLK_PERIOD ; 
 int /*<<< orphan*/  AR_RTC_FORCE_WAKE ; 
 int AR_RTC_FORCE_WAKE_EN ; 
 int AR_RTC_FORCE_WAKE_ON_INT ; 
 int /*<<< orphan*/  AR_RTC_RC ; 
 int AR_RTC_RC_COLD_RESET ; 
 int /*<<< orphan*/  AR_RTC_RC_M ; 
 int AR_RTC_RC_MAC_COLD ; 
 int AR_RTC_RC_MAC_WARM ; 
 int AR_RTC_RC_WARM_RESET ; 
 scalar_t__ AR_SREV_9100 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9300 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9330 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9340 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9580 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_WA ; 
 int ATH9K_RESET_COLD ; 
 int /*<<< orphan*/  ENABLE_REGWRITE_BUFFER (struct ath_hw*) ; 
 int /*<<< orphan*/  REGWRITE_BUFFER_FLUSH (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RESET ; 
 int /*<<< orphan*/  ar9003_mci_check_gpm_offset (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_ar9330_reset_war (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 scalar_t__ ath9k_hw_mci_is_enabled (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_wait (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool ath9k_hw_set_reset(struct ath_hw *ah, int type)
{
	u32 rst_flags;
	u32 tmpReg;

	if (AR_SREV_9100(ah)) {
		REG_RMW_FIELD(ah, AR_RTC_DERIVED_CLK,
			      AR_RTC_DERIVED_CLK_PERIOD, 1);
		(void)REG_READ(ah, AR_RTC_DERIVED_CLK);
	}

	ENABLE_REGWRITE_BUFFER(ah);

	if (AR_SREV_9300_20_OR_LATER(ah)) {
		REG_WRITE(ah, AR_WA, ah->WARegVal);
		udelay(10);
	}

	REG_WRITE(ah, AR_RTC_FORCE_WAKE, AR_RTC_FORCE_WAKE_EN |
		  AR_RTC_FORCE_WAKE_ON_INT);

	if (AR_SREV_9100(ah)) {
		rst_flags = AR_RTC_RC_MAC_WARM | AR_RTC_RC_MAC_COLD |
			AR_RTC_RC_COLD_RESET | AR_RTC_RC_WARM_RESET;
	} else {
		tmpReg = REG_READ(ah, AR_INTR_SYNC_CAUSE);
		if (AR_SREV_9340(ah))
			tmpReg &= AR9340_INTR_SYNC_LOCAL_TIMEOUT;
		else
			tmpReg &= AR_INTR_SYNC_LOCAL_TIMEOUT |
				  AR_INTR_SYNC_RADM_CPL_TIMEOUT;

		if (tmpReg) {
			u32 val;
			REG_WRITE(ah, AR_INTR_SYNC_ENABLE, 0);

			val = AR_RC_HOSTIF;
			if (!AR_SREV_9300_20_OR_LATER(ah))
				val |= AR_RC_AHB;
			REG_WRITE(ah, AR_RC, val);

		} else if (!AR_SREV_9300_20_OR_LATER(ah))
			REG_WRITE(ah, AR_RC, AR_RC_AHB);

		rst_flags = AR_RTC_RC_MAC_WARM;
		if (type == ATH9K_RESET_COLD)
			rst_flags |= AR_RTC_RC_MAC_COLD;
	}

	if (AR_SREV_9330(ah)) {
		if (!ath9k_hw_ar9330_reset_war(ah, type))
			return false;
	}

	if (ath9k_hw_mci_is_enabled(ah))
		ar9003_mci_check_gpm_offset(ah);

	/* DMA HALT added to resolve ar9300 and ar9580 bus error during
	 * RTC_RC reg read
	 */
	if (AR_SREV_9300(ah) || AR_SREV_9580(ah)) {
		REG_SET_BIT(ah, AR_CFG, AR_CFG_HALT_REQ);
		ath9k_hw_wait(ah, AR_CFG, AR_CFG_HALT_ACK, AR_CFG_HALT_ACK,
			      20 * AH_WAIT_TIMEOUT);
		REG_CLR_BIT(ah, AR_CFG, AR_CFG_HALT_REQ);
	}

	REG_WRITE(ah, AR_RTC_RC, rst_flags);

	REGWRITE_BUFFER_FLUSH(ah);

	if (AR_SREV_9300_20_OR_LATER(ah))
		udelay(50);
	else if (AR_SREV_9100(ah))
		mdelay(10);
	else
		udelay(100);

	REG_WRITE(ah, AR_RTC_RC, 0);
	if (!ath9k_hw_wait(ah, AR_RTC_RC, AR_RTC_RC_M, 0, AH_WAIT_TIMEOUT)) {
		ath_dbg(ath9k_hw_common(ah), RESET, "RTC stuck in MAC reset\n");
		return false;
	}

	if (!AR_SREV_9100(ah))
		REG_WRITE(ah, AR_RC, 0);

	if (AR_SREV_9100(ah))
		udelay(50);

	return true;
}