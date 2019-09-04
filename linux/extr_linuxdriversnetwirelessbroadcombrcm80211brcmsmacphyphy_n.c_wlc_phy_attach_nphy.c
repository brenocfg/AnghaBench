#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint ;
struct TYPE_8__ {int /*<<< orphan*/  txpwrrecalc; int /*<<< orphan*/  chanset; int /*<<< orphan*/  calinit; int /*<<< orphan*/  init; } ;
struct TYPE_6__ {size_t phy_corenum; int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int phyhang_avoid; int nphy_gband_spurwar_en; int nphy_aband_spurwar_en; int nphy_gband_spurwar2_en; int nphy_rxcalparams; int nphy_gain_boost; int nphy_elna_gain_config; int radio_is_on; scalar_t__ nphy_txpwrctrl; int hwpwrctrl_capable; TYPE_4__ pi_fptr; TYPE_3__* nphy_txpwrindex; TYPE_2__ pubpi; int /*<<< orphan*/  mphase_txcal_numcmds; int /*<<< orphan*/  mphase_cal_phase_id; int /*<<< orphan*/  nphy_perical; void* phy_scraminit; void* nphy_txrx_chain; void* n_preamble_override; TYPE_1__* sh; } ;
struct TYPE_7__ {void* index; } ;
struct TYPE_5__ {int boardflags2; } ;

/* Variables and functions */
 void* AUTO ; 
 int BFL2_2G_SPUR_WAR ; 
 int BFL2_SPUR_WAR ; 
 void* BRCMS_N_PREAMBLE_MIXEDMODE ; 
 int /*<<< orphan*/  MPHASE_CAL_STATE_IDLE ; 
 int /*<<< orphan*/  MPHASE_TXCAL_NUMCMDS ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_IS (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_LT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PHY_PERICAL_MPHASE ; 
 scalar_t__ PHY_TPC_HW_ON ; 
 int /*<<< orphan*/  wlc_phy_cal_init_nphy ; 
 int /*<<< orphan*/  wlc_phy_chanspec_set_nphy ; 
 int /*<<< orphan*/  wlc_phy_init_nphy ; 
 int /*<<< orphan*/  wlc_phy_txpower_recalc_target_nphy ; 
 int /*<<< orphan*/  wlc_phy_txpwr_srom_read_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_txpwrctrl_config_nphy (struct brcms_phy*) ; 

bool wlc_phy_attach_nphy(struct brcms_phy *pi)
{
	uint i;

	if (NREV_GE(pi->pubpi.phy_rev, 3) && NREV_LT(pi->pubpi.phy_rev, 6))
		pi->phyhang_avoid = true;

	if (NREV_GE(pi->pubpi.phy_rev, 3) && NREV_LT(pi->pubpi.phy_rev, 7)) {
		pi->nphy_gband_spurwar_en = true;
		if (pi->sh->boardflags2 & BFL2_SPUR_WAR)
			pi->nphy_aband_spurwar_en = true;
	}
	if (NREV_GE(pi->pubpi.phy_rev, 6) && NREV_LT(pi->pubpi.phy_rev, 7)) {
		if (pi->sh->boardflags2 & BFL2_2G_SPUR_WAR)
			pi->nphy_gband_spurwar2_en = true;
	}

	pi->n_preamble_override = AUTO;
	if (NREV_IS(pi->pubpi.phy_rev, 3) || NREV_IS(pi->pubpi.phy_rev, 4))
		pi->n_preamble_override = BRCMS_N_PREAMBLE_MIXEDMODE;

	pi->nphy_txrx_chain = AUTO;
	pi->phy_scraminit = AUTO;

	pi->nphy_rxcalparams = 0x010100B5;

	pi->nphy_perical = PHY_PERICAL_MPHASE;
	pi->mphase_cal_phase_id = MPHASE_CAL_STATE_IDLE;
	pi->mphase_txcal_numcmds = MPHASE_TXCAL_NUMCMDS;

	pi->nphy_gain_boost = true;
	pi->nphy_elna_gain_config = false;
	pi->radio_is_on = false;

	for (i = 0; i < pi->pubpi.phy_corenum; i++)
		pi->nphy_txpwrindex[i].index = AUTO;

	wlc_phy_txpwrctrl_config_nphy(pi);
	if (pi->nphy_txpwrctrl == PHY_TPC_HW_ON)
		pi->hwpwrctrl_capable = true;

	pi->pi_fptr.init = wlc_phy_init_nphy;
	pi->pi_fptr.calinit = wlc_phy_cal_init_nphy;
	pi->pi_fptr.chanset = wlc_phy_chanspec_set_nphy;
	pi->pi_fptr.txpwrrecalc = wlc_phy_txpower_recalc_target_nphy;

	if (!wlc_phy_txpwr_srom_read_nphy(pi))
		return false;

	return true;
}