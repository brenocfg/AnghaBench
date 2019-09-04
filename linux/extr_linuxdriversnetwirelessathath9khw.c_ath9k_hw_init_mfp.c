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
struct ath_hw {int sw_mgmt_crypto_tx; int sw_mgmt_crypto_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_AES_MUTE_MASK1 ; 
 int /*<<< orphan*/  AR_AES_MUTE_MASK1_FC_MGMT ; 
 scalar_t__ AR_DEVID_7010 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_PCU_MISC_MODE2 ; 
 int /*<<< orphan*/  AR_PCU_MISC_MODE2_MGMT_CRYPTO_ENABLE ; 
 int /*<<< orphan*/  AR_PCU_MISC_MODE2_NO_CRYPTO_FOR_NON_DATA_PKT ; 
 scalar_t__ AR_SREV_9160_10_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9271 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9280_20_OR_LATER (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_hw_init_mfp(struct ath_hw *ah)
{
	/* Setup MFP options for CCMP */
	if (AR_SREV_9280_20_OR_LATER(ah)) {
		/* Mask Retry(b11), PwrMgt(b12), MoreData(b13) to 0 in mgmt
		 * frames when constructing CCMP AAD. */
		REG_RMW_FIELD(ah, AR_AES_MUTE_MASK1, AR_AES_MUTE_MASK1_FC_MGMT,
			      0xc7ff);
		if (AR_SREV_9271(ah) || AR_DEVID_7010(ah))
			ah->sw_mgmt_crypto_tx = true;
		else
			ah->sw_mgmt_crypto_tx = false;
		ah->sw_mgmt_crypto_rx = false;
	} else if (AR_SREV_9160_10_OR_LATER(ah)) {
		/* Disable hardware crypto for management frames */
		REG_CLR_BIT(ah, AR_PCU_MISC_MODE2,
			    AR_PCU_MISC_MODE2_MGMT_CRYPTO_ENABLE);
		REG_SET_BIT(ah, AR_PCU_MISC_MODE2,
			    AR_PCU_MISC_MODE2_NO_CRYPTO_FOR_NON_DATA_PKT);
		ah->sw_mgmt_crypto_tx = true;
		ah->sw_mgmt_crypto_rx = true;
	} else {
		ah->sw_mgmt_crypto_tx = true;
		ah->sw_mgmt_crypto_rx = true;
	}
}