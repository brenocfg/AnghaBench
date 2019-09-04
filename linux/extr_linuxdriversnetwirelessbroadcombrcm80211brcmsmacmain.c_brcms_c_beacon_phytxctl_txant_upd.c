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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct brcms_c_info {int /*<<< orphan*/  hw; int /*<<< orphan*/  band; TYPE_1__* stf; } ;
struct TYPE_2__ {int phytxant; } ;

/* Variables and functions */
 scalar_t__ BRCMS_PHY_11N_CAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_BCN_PCTLWD ; 
 int PHY_TXC_ANT_MASK ; 
 int brcms_b_read_shm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_write_shm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int brcms_c_stf_phytxchain_sel (struct brcms_c_info*,int /*<<< orphan*/ ) ; 

void brcms_c_beacon_phytxctl_txant_upd(struct brcms_c_info *wlc,
				       u32 bcn_rspec)
{
	u16 phyctl;
	u16 phytxant = wlc->stf->phytxant;
	u16 mask = PHY_TXC_ANT_MASK;

	/* for non-siso rates or default setting, use the available chains */
	if (BRCMS_PHY_11N_CAP(wlc->band))
		phytxant = brcms_c_stf_phytxchain_sel(wlc, bcn_rspec);

	phyctl = brcms_b_read_shm(wlc->hw, M_BCN_PCTLWD);
	phyctl = (phyctl & ~mask) | phytxant;
	brcms_b_write_shm(wlc->hw, M_BCN_PCTLWD, phyctl);
}