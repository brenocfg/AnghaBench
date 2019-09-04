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
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_STA_ID1 ; 
 int /*<<< orphan*/  AR_STA_ID1_PWR_SAV ; 
 scalar_t__ MCI_PS_DISABLE ; 
 int /*<<< orphan*/  MCI_STATE_GET_WLAN_PS_STATE ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ar9003_mci_state (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_mci_is_enabled (struct ath_hw*) ; 

__attribute__((used)) static void ath9k_hw_set_sta_powersave(struct ath_hw *ah)
{
	if (!ath9k_hw_mci_is_enabled(ah))
		goto set;
	/*
	 * If MCI is being used, set PWR_SAV only when MCI's
	 * PS state is disabled.
	 */
	if (ar9003_mci_state(ah, MCI_STATE_GET_WLAN_PS_STATE) != MCI_PS_DISABLE)
		return;
set:
	REG_SET_BIT(ah, AR_STA_ID1, AR_STA_ID1_PWR_SAV);
}