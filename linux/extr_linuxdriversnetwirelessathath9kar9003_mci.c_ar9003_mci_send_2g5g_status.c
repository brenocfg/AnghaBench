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
struct ath9k_hw_mci {scalar_t__ bt_state; scalar_t__ is_2g; int /*<<< orphan*/  update_2g5g; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;

/* Variables and functions */
 scalar_t__ MCI_2G_FLAGS ; 
 scalar_t__ MCI_2G_FLAGS_CLEAR_MASK ; 
 scalar_t__ MCI_2G_FLAGS_SET_MASK ; 
 scalar_t__ MCI_5G_FLAGS ; 
 scalar_t__ MCI_5G_FLAGS_CLEAR_MASK ; 
 scalar_t__ MCI_5G_FLAGS_SET_MASK ; 
 scalar_t__ MCI_BT_SLEEP ; 
 int /*<<< orphan*/  MCI_GPM_COEX_BT_FLAGS_CLEAR ; 
 int /*<<< orphan*/  MCI_GPM_COEX_BT_FLAGS_SET ; 
 int /*<<< orphan*/  ar9003_mci_send_coex_bt_flags (struct ath_hw*,int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ar9003_mci_send_2g5g_status(struct ath_hw *ah, bool wait_done)
{
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 new_flags, to_set, to_clear;

	if (!mci->update_2g5g || (mci->bt_state == MCI_BT_SLEEP))
		return;

	if (mci->is_2g) {
		new_flags = MCI_2G_FLAGS;
		to_clear = MCI_2G_FLAGS_CLEAR_MASK;
		to_set = MCI_2G_FLAGS_SET_MASK;
	} else {
		new_flags = MCI_5G_FLAGS;
		to_clear = MCI_5G_FLAGS_CLEAR_MASK;
		to_set = MCI_5G_FLAGS_SET_MASK;
	}

	if (to_clear)
		ar9003_mci_send_coex_bt_flags(ah, wait_done,
					      MCI_GPM_COEX_BT_FLAGS_CLEAR,
					      to_clear);
	if (to_set)
		ar9003_mci_send_coex_bt_flags(ah, wait_done,
					      MCI_GPM_COEX_BT_FLAGS_SET,
					      to_set);
}