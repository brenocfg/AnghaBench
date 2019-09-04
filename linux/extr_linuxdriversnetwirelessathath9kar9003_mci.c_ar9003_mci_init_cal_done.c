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
typedef  scalar_t__ u32 ;
struct ath9k_hw_mci {scalar_t__ bt_state; int config; int /*<<< orphan*/  wlan_cal_done; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;

/* Variables and functions */
 int ATH_MCI_CONFIG_DISABLE_MCI_CAL ; 
 scalar_t__ MCI_BT_AWAKE ; 
 int /*<<< orphan*/  MCI_GPM ; 
 int /*<<< orphan*/  MCI_GPM_SET_CAL_TYPE (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCI_GPM_WLAN_CAL_DONE ; 
 size_t MCI_GPM_WLAN_CAL_W_SEQUENCE ; 
 int /*<<< orphan*/  ar9003_mci_send_message (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int,int) ; 

void ar9003_mci_init_cal_done(struct ath_hw *ah)
{
	struct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u32 pld[4] = {0, 0, 0, 0};

	if ((mci_hw->bt_state != MCI_BT_AWAKE) ||
	    (mci_hw->config & ATH_MCI_CONFIG_DISABLE_MCI_CAL))
		return;

	MCI_GPM_SET_CAL_TYPE(pld, MCI_GPM_WLAN_CAL_DONE);
	pld[MCI_GPM_WLAN_CAL_W_SEQUENCE] = mci_hw->wlan_cal_done++;
	ar9003_mci_send_message(ah, MCI_GPM, 0, pld, 16, true, false);
}