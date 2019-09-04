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
typedef  int /*<<< orphan*/  u16 ;
struct brcms_hardware {int shortslot; TYPE_1__* band; int /*<<< orphan*/  unit; int /*<<< orphan*/  d11core; } ;
struct brcms_c_info {struct brcms_hardware* hw; } ;
struct TYPE_2__ {scalar_t__ bandtype; scalar_t__ phyrev; scalar_t__ phytype; int /*<<< orphan*/  CWmax; int /*<<< orphan*/  CWmin; int /*<<< orphan*/  pi; int /*<<< orphan*/  bandunit; } ;

/* Variables and functions */
 scalar_t__ BRCM_BAND_5G ; 
 int /*<<< orphan*/  M_PHYTYPE ; 
 int /*<<< orphan*/  M_PHYVER ; 
 int /*<<< orphan*/  brcms_b_set_cwmax (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_set_cwmin (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_upd_synthpu (struct brcms_hardware*) ; 
 int /*<<< orphan*/  brcms_b_update_slot_timing (struct brcms_hardware*,int) ; 
 int /*<<< orphan*/  brcms_b_write_shm (struct brcms_hardware*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_ucode_bsinit (struct brcms_hardware*) ; 
 int /*<<< orphan*/  brcms_c_ucode_txant_set (struct brcms_hardware*) ; 
 int /*<<< orphan*/  brcms_dbg_mac80211 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_upd_ofdm_pctl1_table (struct brcms_hardware*) ; 
 int /*<<< orphan*/  wlc_phy_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcms_b_bsinit(struct brcms_c_info *wlc, u16 chanspec)
{
	struct brcms_hardware *wlc_hw = wlc->hw;

	brcms_dbg_mac80211(wlc_hw->d11core, "wl%d: bandunit %d\n", wlc_hw->unit,
			   wlc_hw->band->bandunit);

	brcms_c_ucode_bsinit(wlc_hw);

	wlc_phy_init(wlc_hw->band->pi, chanspec);

	brcms_c_ucode_txant_set(wlc_hw);

	/*
	 * cwmin is band-specific, update hardware
	 * with value for current band
	 */
	brcms_b_set_cwmin(wlc_hw, wlc_hw->band->CWmin);
	brcms_b_set_cwmax(wlc_hw, wlc_hw->band->CWmax);

	brcms_b_update_slot_timing(wlc_hw,
				   wlc_hw->band->bandtype == BRCM_BAND_5G ?
				   true : wlc_hw->shortslot);

	/* write phytype and phyvers */
	brcms_b_write_shm(wlc_hw, M_PHYTYPE, (u16) wlc_hw->band->phytype);
	brcms_b_write_shm(wlc_hw, M_PHYVER, (u16) wlc_hw->band->phyrev);

	/*
	 * initialize the txphyctl1 rate table since
	 * shmem is shared between bands
	 */
	brcms_upd_ofdm_pctl1_table(wlc_hw);

	brcms_b_upd_synthpu(wlc_hw);
}