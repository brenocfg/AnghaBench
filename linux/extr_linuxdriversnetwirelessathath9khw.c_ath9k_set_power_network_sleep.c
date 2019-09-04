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
struct ath9k_hw_capabilities {int hw_caps; } ;
struct ath_hw {int WARegVal; struct ath9k_hw_capabilities caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_MCI_INTERRUPT_RX_HW_MSG_MASK ; 
 int /*<<< orphan*/  AR_MCI_INTERRUPT_RX_MSG_EN ; 
 int /*<<< orphan*/  AR_RTC_FORCE_WAKE ; 
 int /*<<< orphan*/  AR_RTC_FORCE_WAKE_EN ; 
 int AR_RTC_FORCE_WAKE_ON_INT ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_STA_ID1 ; 
 int /*<<< orphan*/  AR_STA_ID1_PWR_SAV ; 
 int /*<<< orphan*/  AR_WA ; 
 int AR_WA_D3_L1_DISABLE ; 
 int ATH9K_HW_CAP_AUTOSLEEP ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ath9k_hw_mci_is_enabled (struct ath_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ath9k_set_power_network_sleep(struct ath_hw *ah)
{
	struct ath9k_hw_capabilities *pCap = &ah->caps;

	REG_SET_BIT(ah, AR_STA_ID1, AR_STA_ID1_PWR_SAV);

	if (!(pCap->hw_caps & ATH9K_HW_CAP_AUTOSLEEP)) {
		/* Set WakeOnInterrupt bit; clear ForceWake bit */
		REG_WRITE(ah, AR_RTC_FORCE_WAKE,
			  AR_RTC_FORCE_WAKE_ON_INT);
	} else {

		/* When chip goes into network sleep, it could be waken
		 * up by MCI_INT interrupt caused by BT's HW messages
		 * (LNA_xxx, CONT_xxx) which chould be in a very fast
		 * rate (~100us). This will cause chip to leave and
		 * re-enter network sleep mode frequently, which in
		 * consequence will have WLAN MCI HW to generate lots of
		 * SYS_WAKING and SYS_SLEEPING messages which will make
		 * BT CPU to busy to process.
		 */
		if (ath9k_hw_mci_is_enabled(ah))
			REG_CLR_BIT(ah, AR_MCI_INTERRUPT_RX_MSG_EN,
				    AR_MCI_INTERRUPT_RX_HW_MSG_MASK);
		/*
		 * Clear the RTC force wake bit to allow the
		 * mac to go to sleep.
		 */
		REG_CLR_BIT(ah, AR_RTC_FORCE_WAKE, AR_RTC_FORCE_WAKE_EN);

		if (ath9k_hw_mci_is_enabled(ah))
			udelay(30);
	}

	/* Clear Bit 14 of AR_WA after putting chip into Net Sleep mode. */
	if (AR_SREV_9300_20_OR_LATER(ah))
		REG_WRITE(ah, AR_WA, ah->WARegVal & ~AR_WA_D3_L1_DISABLE);
}