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
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int AR_ADHOC_MCAST_KEYID_ENABLE ; 
 int AR_DIAG_RX_ABORT ; 
 int AR_DIAG_RX_DIS ; 
 int /*<<< orphan*/  AR_DIAG_SW ; 
 int AR_PCU_MISC_MODE2 ; 
 int AR_PCU_MISC_MODE2_CFP_IGNORE ; 
 int AR_PCU_MISC_MODE2_HWWAR1 ; 
 int AR_PCU_MISC_MODE2_HWWAR2 ; 
 int AR_PHY_HEAVY_CLIP_FACTOR_RIFS ; 
 int AR_PHY_RIFS_INIT_DELAY ; 
 scalar_t__ AR_SREV_9100 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9160 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9271 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9280_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9287_11_OR_LATER (struct ath_hw*) ; 
 int REG_READ (struct ath_hw*,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int,int) ; 

__attribute__((used)) static void ar5008_hw_override_ini(struct ath_hw *ah,
				   struct ath9k_channel *chan)
{
	u32 val;

	/*
	 * Set the RX_ABORT and RX_DIS and clear if off only after
	 * RXE is set for MAC. This prevents frames with corrupted
	 * descriptor status.
	 */
	REG_SET_BIT(ah, AR_DIAG_SW, (AR_DIAG_RX_DIS | AR_DIAG_RX_ABORT));

	if (AR_SREV_9280_20_OR_LATER(ah)) {
		/*
		 * For AR9280 and above, there is a new feature that allows
		 * Multicast search based on both MAC Address and Key ID.
		 * By default, this feature is enabled. But since the driver
		 * is not using this feature, we switch it off; otherwise
		 * multicast search based on MAC addr only will fail.
		 */
		val = REG_READ(ah, AR_PCU_MISC_MODE2) &
			(~AR_ADHOC_MCAST_KEYID_ENABLE);

		if (!AR_SREV_9271(ah))
			val &= ~AR_PCU_MISC_MODE2_HWWAR1;

		if (AR_SREV_9287_11_OR_LATER(ah))
			val = val & (~AR_PCU_MISC_MODE2_HWWAR2);

		val |= AR_PCU_MISC_MODE2_CFP_IGNORE;

		REG_WRITE(ah, AR_PCU_MISC_MODE2, val);
	}

	if (AR_SREV_9280_20_OR_LATER(ah))
		return;
	/*
	 * Disable BB clock gating
	 * Necessary to avoid issues on AR5416 2.0
	 */
	REG_WRITE(ah, 0x9800 + (651 << 2), 0x11);

	/*
	 * Disable RIFS search on some chips to avoid baseband
	 * hang issues.
	 */
	if (AR_SREV_9100(ah) || AR_SREV_9160(ah)) {
		val = REG_READ(ah, AR_PHY_HEAVY_CLIP_FACTOR_RIFS);
		val &= ~AR_PHY_RIFS_INIT_DELAY;
		REG_WRITE(ah, AR_PHY_HEAVY_CLIP_FACTOR_RIFS, val);
	}
}