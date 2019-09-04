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
typedef  int /*<<< orphan*/  u32 ;
struct ath9k_hw_mci {scalar_t__ bt_state; int need_flush_btinfo; int query_bt; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;

/* Variables and functions */
 scalar_t__ MCI_BT_SLEEP ; 
 int /*<<< orphan*/  MCI_GPM ; 
 int /*<<< orphan*/  MCI_GPM_COEX_AGENT ; 
 int MCI_GPM_COEX_B_BT_BITMAP ; 
 int MCI_GPM_COEX_QUERY_BT_ALL_INFO ; 
 int MCI_GPM_COEX_QUERY_BT_TOPOLOGY ; 
 int /*<<< orphan*/  MCI_GPM_COEX_STATUS_QUERY ; 
 int /*<<< orphan*/  MCI_GPM_SET_TYPE_OPCODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9003_mci_send_message (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void ar9003_mci_send_coex_bt_status_query(struct ath_hw *ah,
						bool wait_done, u8 query_type)
{
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 payload[4] = {0, 0, 0, 0};
	bool query_btinfo;

	if (mci->bt_state == MCI_BT_SLEEP)
		return;

	query_btinfo = !!(query_type & (MCI_GPM_COEX_QUERY_BT_ALL_INFO |
					MCI_GPM_COEX_QUERY_BT_TOPOLOGY));
	MCI_GPM_SET_TYPE_OPCODE(payload, MCI_GPM_COEX_AGENT,
				MCI_GPM_COEX_STATUS_QUERY);

	*(((u8 *)payload) + MCI_GPM_COEX_B_BT_BITMAP) = query_type;

	/*
	 * If bt_status_query message is  not sent successfully,
	 * then need_flush_btinfo should be set again.
	 */
	if (!ar9003_mci_send_message(ah, MCI_GPM, 0, payload, 16,
				wait_done, true)) {
		if (query_btinfo)
			mci->need_flush_btinfo = true;
	}

	if (query_btinfo)
		mci->query_bt = false;
}