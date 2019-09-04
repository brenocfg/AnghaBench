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
struct brcmf_if {int dummy; } ;
struct brcmf_btcoex_info {int dhcp_done; int /*<<< orphan*/  work; int /*<<< orphan*/  bt_state; TYPE_1__* vif; } ;
struct TYPE_2__ {struct brcmf_if* ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_BT_DHCP_REG41 ; 
 int /*<<< orphan*/  BRCMF_BT_DHCP_REG66 ; 
 int /*<<< orphan*/  BRCMF_BT_DHCP_REG68 ; 
 int /*<<< orphan*/  BRCMF_BT_DHCP_START ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_btcoex_params_write (struct brcmf_if*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  btcmf_btcoex_save_part1 (struct brcmf_btcoex_info*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void brcmf_btcoex_dhcp_start(struct brcmf_btcoex_info *btci)
{
	struct brcmf_if *ifp = btci->vif->ifp;

	btcmf_btcoex_save_part1(btci);
	/* set new regs values */
	brcmf_btcoex_params_write(ifp, 66, BRCMF_BT_DHCP_REG66);
	brcmf_btcoex_params_write(ifp, 41, BRCMF_BT_DHCP_REG41);
	brcmf_btcoex_params_write(ifp, 68, BRCMF_BT_DHCP_REG68);
	btci->dhcp_done = false;
	btci->bt_state = BRCMF_BT_DHCP_START;
	schedule_work(&btci->work);
	brcmf_dbg(TRACE, "enable BT DHCP Timer\n");
}