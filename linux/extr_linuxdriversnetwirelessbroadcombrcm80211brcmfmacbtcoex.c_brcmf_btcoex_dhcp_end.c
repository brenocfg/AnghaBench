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
struct brcmf_btcoex_info {int dhcp_done; int timer_on; scalar_t__ bt_state; int /*<<< orphan*/  work; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 scalar_t__ BRCMF_BT_DHCP_IDLE ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  brcmf_btcoex_restore_part1 (struct brcmf_btcoex_info*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void brcmf_btcoex_dhcp_end(struct brcmf_btcoex_info *btci)
{
	/* Stop any bt timer because DHCP session is done */
	btci->dhcp_done = true;
	if (btci->timer_on) {
		brcmf_dbg(INFO, "disable BT DHCP Timer\n");
		btci->timer_on = false;
		del_timer_sync(&btci->timer);

		/* schedule worker if transition to IDLE is needed */
		if (btci->bt_state != BRCMF_BT_DHCP_IDLE) {
			brcmf_dbg(INFO, "bt_state:%d\n",
				  btci->bt_state);
			schedule_work(&btci->work);
		}
	} else {
		/* Restore original values */
		brcmf_btcoex_restore_part1(btci);
	}
}