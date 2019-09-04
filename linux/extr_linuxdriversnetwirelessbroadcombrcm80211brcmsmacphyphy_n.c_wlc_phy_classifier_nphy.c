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
typedef  int u16 ;
struct brcms_phy {TYPE_1__* sh; int /*<<< orphan*/  d11core; } ;
struct TYPE_2__ {int /*<<< orphan*/  physhim; int /*<<< orphan*/  corerev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 scalar_t__ D11REV_IS (int /*<<< orphan*/ ,int) ; 
 int MCTL_EN_MAC ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlapi_enable_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlapi_suspend_mac_and_wait (int /*<<< orphan*/ ) ; 

u16 wlc_phy_classifier_nphy(struct brcms_phy *pi, u16 mask, u16 val)
{
	u16 curr_ctl, new_ctl;
	bool suspended = false;

	if (D11REV_IS(pi->sh->corerev, 16)) {
		suspended = (bcma_read32(pi->d11core, D11REGOFFS(maccontrol)) &
			     MCTL_EN_MAC) ? false : true;
		if (!suspended)
			wlapi_suspend_mac_and_wait(pi->sh->physhim);
	}

	curr_ctl = read_phy_reg(pi, 0xb0) & (0x7 << 0);

	new_ctl = (curr_ctl & (~mask)) | (val & mask);

	mod_phy_reg(pi, 0xb0, (0x7 << 0), new_ctl);

	if (D11REV_IS(pi->sh->corerev, 16) && !suspended)
		wlapi_enable_mac(pi->sh->physhim);

	return new_ctl;
}