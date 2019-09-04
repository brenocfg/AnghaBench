#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct nphy_txgains {int dummy; } ;
struct brcms_phy_pub {int dummy; } ;
struct TYPE_15__ {size_t phy_corenum; int radiorev; int /*<<< orphan*/  phy_rev; } ;
struct TYPE_12__ {int extpagain; } ;
struct TYPE_11__ {int extpagain; } ;
struct brcms_phy {int measure_hold; int use_int_tx_iqlo_cal_nphy; int internal_tx_iqlo_cal_tapoff_intpa_nphy; int nphy_crsminpwr_adjusted; int nphy_noisevars_adjusted; int* nphy_papd_epsilon_offset; int nphy_gmval; scalar_t__ nphy_rssical_chanspec_2G; scalar_t__ nphy_rssical_chanspec_5G; scalar_t__ nphy_iqcal_chanspec_2G; scalar_t__ nphy_iqcal_chanspec_5G; scalar_t__ antsel_type; scalar_t__ nphy_perical; scalar_t__ mphase_cal_phase_id; TYPE_6__ pubpi; TYPE_5__* sh; TYPE_4__* nphy_txpwrindex; int /*<<< orphan*/ * nphy_cal_orig_pwr_idx; int /*<<< orphan*/  do_initcal; int /*<<< orphan*/  radio_chanspec; TYPE_3__ srom_fem2g; TYPE_2__ srom_fem5g; int /*<<< orphan*/  nphy_txpwrctrl; int /*<<< orphan*/  n_preamble_override; scalar_t__ nphy_deaf_count; TYPE_7__* d11core; scalar_t__ nphy_gband_spurwar2_en; } ;
typedef  int s32 ;
typedef  size_t s16 ;
struct TYPE_16__ {TYPE_1__* bus; } ;
struct TYPE_14__ {scalar_t__ chippkg; int boardflags; scalar_t__ chip; int boardflags2; int phyrxchain; int /*<<< orphan*/  _rifs_phy; int /*<<< orphan*/  physhim; } ;
struct TYPE_13__ {int /*<<< orphan*/  index_internal; } ;
struct TYPE_10__ {int /*<<< orphan*/  drv_cc; } ;

/* Variables and functions */
 scalar_t__ ANTSEL_2x3 ; 
 int BBCFG_RESETCCA ; 
 int /*<<< orphan*/  BCMA_CC_CHIPCTL ; 
 scalar_t__ BCMA_CHIP_ID_BCM5357 ; 
 scalar_t__ BCMA_PKG_ID_BCM4717 ; 
 scalar_t__ BCMA_PKG_ID_BCM4718 ; 
 int BFL2_INTERNDET_TXIQCAL ; 
 int BFL2_SKWRKFEM_BRD ; 
 int BFL_EXTLNA ; 
 int CCS_FORCEHT ; 
 int CCS_HTAREQ ; 
 int /*<<< orphan*/  CCTRL5357_EXTPA ; 
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS40 (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 scalar_t__ ISNPHY (struct brcms_phy*) ; 
 scalar_t__ MPHASE_CAL_STATE_IDLE ; 
 int /*<<< orphan*/  NPHY_RFSEQ_RESET2RX ; 
 int /*<<< orphan*/  NPHY_RFSEQ_RX2TX ; 
 int /*<<< orphan*/  NPHY_TBL_ID_CORE1TXPWRCTL ; 
 int /*<<< orphan*/  NPHY_TBL_ID_CORE2TXPWRCTL ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_IS (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_LE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_LT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  ON ; 
 size_t PHY_CORE_0 ; 
 size_t PHY_CORE_1 ; 
 int PHY_HOLD_FOR_NOT_ASSOC ; 
 int PHY_HOLD_FOR_SCAN ; 
 scalar_t__ PHY_IPA (struct brcms_phy*) ; 
 scalar_t__ PHY_PERICAL_MPHASE ; 
 scalar_t__ PHY_PERICAL_MPHASE_PENDING (struct brcms_phy*) ; 
 int /*<<< orphan*/  PHY_PERICAL_PHYINIT ; 
 int /*<<< orphan*/  PHY_TPC_HW_OFF ; 
 int /*<<< orphan*/  SCAN_RM_IN_PROGRESS (struct brcms_phy*) ; 
 int /*<<< orphan*/  and_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  bcma_cc_set32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcma_chipco_chipctl_maskset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_mask32 (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int bcma_read32 (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_write32 (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_ctl_st ; 
 int get_rf_pwr_offset (struct brcms_phy*,size_t,size_t) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 scalar_t__* nphy_papd_pga_gain_delta_ipa_2g ; 
 scalar_t__* nphy_papd_pga_gain_delta_ipa_5g ; 
 int* nphy_tpc_5GHz_txgain_HiPwrEPA ; 
 int* nphy_tpc_5GHz_txgain_rev3 ; 
 int* nphy_tpc_5GHz_txgain_rev4 ; 
 int* nphy_tpc_5GHz_txgain_rev5 ; 
 int* nphy_tpc_txgain ; 
 int* nphy_tpc_txgain_HiPwrEPA ; 
 int* nphy_tpc_txgain_epa_2057rev3 ; 
 int* nphy_tpc_txgain_epa_2057rev5 ; 
 int* nphy_tpc_txgain_rev3 ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlapi_bmac_macphyclk_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlapi_bmac_phyclk_fgc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_antsel_init (struct brcms_phy_pub*,int) ; 
 int /*<<< orphan*/  wlc_phy_bphy_init_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_cal_perical (struct brcms_phy_pub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_cal_perical_mphase_restart (struct brcms_phy*) ; 
 scalar_t__ wlc_phy_cal_rxiq_nphy (struct brcms_phy*,struct nphy_txgains,int,int) ; 
 scalar_t__ wlc_phy_cal_txiqlo_nphy (struct brcms_phy*,struct nphy_txgains,int,int) ; 
 int /*<<< orphan*/  wlc_phy_classifier_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_clip_det_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  wlc_phy_extpa_set_tx_digi_filts_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_force_rfseq_nphy (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int* wlc_phy_get_ipa_gaintbl_nphy (struct brcms_phy*) ; 
 struct nphy_txgains wlc_phy_get_tx_gain_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_ipa_set_tx_digi_filts_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_nphy_tkip_rifs_war (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_pa_override_nphy (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_precal_txgain_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_restore_rssical_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_restorecal_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_rssi_cal_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_rxcore_setstate_nphy (struct brcms_phy_pub*,int) ; 
 int /*<<< orphan*/  wlc_phy_savecal_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_spurwar_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_stf_chain_upd_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int,int*) ; 
 int /*<<< orphan*/  wlc_phy_tbl_init_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_txlpfbw_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_txpwr_fixpower_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_txpwrctrl_coeff_setup_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_txpwrctrl_enable_nphy (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_txpwrctrl_idle_tssi_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_txpwrctrl_pwr_setup_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_update_mimoconfig_nphy (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_workarounds_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

void wlc_phy_init_nphy(struct brcms_phy *pi)
{
	u16 val;
	u16 clip1_ths[2];
	struct nphy_txgains target_gain;
	u8 tx_pwr_ctrl_state;
	bool do_nphy_cal = false;
	uint core;
	u32 d11_clk_ctl_st;
	bool do_rssi_cal = false;

	core = 0;

	if (!(pi->measure_hold & PHY_HOLD_FOR_SCAN))
		pi->measure_hold |= PHY_HOLD_FOR_NOT_ASSOC;

	if ((ISNPHY(pi)) && (NREV_GE(pi->pubpi.phy_rev, 5)) &&
	    ((pi->sh->chippkg == BCMA_PKG_ID_BCM4717) ||
	     (pi->sh->chippkg == BCMA_PKG_ID_BCM4718))) {
		if ((pi->sh->boardflags & BFL_EXTLNA) &&
		    (CHSPEC_IS2G(pi->radio_chanspec)))
			bcma_cc_set32(&pi->d11core->bus->drv_cc,
				      BCMA_CC_CHIPCTL, 0x40);
	}

	if ((!PHY_IPA(pi)) && (pi->sh->chip == BCMA_CHIP_ID_BCM5357))
		bcma_chipco_chipctl_maskset(&pi->d11core->bus->drv_cc, 1,
					    ~CCTRL5357_EXTPA, CCTRL5357_EXTPA);

	if ((pi->nphy_gband_spurwar2_en) && CHSPEC_IS2G(pi->radio_chanspec) &&
	    CHSPEC_IS40(pi->radio_chanspec)) {

		d11_clk_ctl_st = bcma_read32(pi->d11core,
					     D11REGOFFS(clk_ctl_st));
		bcma_mask32(pi->d11core, D11REGOFFS(clk_ctl_st),
			    ~(CCS_FORCEHT | CCS_HTAREQ));

		bcma_write32(pi->d11core, D11REGOFFS(clk_ctl_st),
			     d11_clk_ctl_st);
	}

	pi->use_int_tx_iqlo_cal_nphy =
		(PHY_IPA(pi) ||
		 (NREV_GE(pi->pubpi.phy_rev, 7) ||
		  (NREV_GE(pi->pubpi.phy_rev, 5)
		   && pi->sh->boardflags2 & BFL2_INTERNDET_TXIQCAL)));

	pi->internal_tx_iqlo_cal_tapoff_intpa_nphy = false;

	pi->nphy_deaf_count = 0;

	wlc_phy_tbl_init_nphy(pi);

	pi->nphy_crsminpwr_adjusted = false;
	pi->nphy_noisevars_adjusted = false;

	if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		write_phy_reg(pi, 0xe7, 0);
		write_phy_reg(pi, 0xec, 0);
		if (NREV_GE(pi->pubpi.phy_rev, 7)) {
			write_phy_reg(pi, 0x342, 0);
			write_phy_reg(pi, 0x343, 0);
			write_phy_reg(pi, 0x346, 0);
			write_phy_reg(pi, 0x347, 0);
		}
		write_phy_reg(pi, 0xe5, 0);
		write_phy_reg(pi, 0xe6, 0);
	} else {
		write_phy_reg(pi, 0xec, 0);
	}

	write_phy_reg(pi, 0x91, 0);
	write_phy_reg(pi, 0x92, 0);
	if (NREV_LT(pi->pubpi.phy_rev, 6)) {
		write_phy_reg(pi, 0x93, 0);
		write_phy_reg(pi, 0x94, 0);
	}

	and_phy_reg(pi, 0xa1, ~3);

	if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		write_phy_reg(pi, 0x8f, 0);
		write_phy_reg(pi, 0xa5, 0);
	} else {
		write_phy_reg(pi, 0xa5, 0);
	}

	if (NREV_IS(pi->pubpi.phy_rev, 2))
		mod_phy_reg(pi, 0xdc, 0x00ff, 0x3b);
	else if (NREV_LT(pi->pubpi.phy_rev, 2))
		mod_phy_reg(pi, 0xdc, 0x00ff, 0x40);

	write_phy_reg(pi, 0x203, 32);
	write_phy_reg(pi, 0x201, 32);

	if (pi->sh->boardflags2 & BFL2_SKWRKFEM_BRD)
		write_phy_reg(pi, 0x20d, 160);
	else
		write_phy_reg(pi, 0x20d, 184);

	write_phy_reg(pi, 0x13a, 200);

	write_phy_reg(pi, 0x70, 80);

	write_phy_reg(pi, 0x1ff, 48);

	if (NREV_LT(pi->pubpi.phy_rev, 8))
		wlc_phy_update_mimoconfig_nphy(pi, pi->n_preamble_override);

	wlc_phy_stf_chain_upd_nphy(pi);

	if (NREV_LT(pi->pubpi.phy_rev, 2)) {
		write_phy_reg(pi, 0x180, 0xaa8);
		write_phy_reg(pi, 0x181, 0x9a4);
	}

	if (PHY_IPA(pi)) {
		for (core = 0; core < pi->pubpi.phy_corenum; core++) {

			mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x297 :
				    0x29b, (0x1 << 0), (1) << 0);

			mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x298 :
				    0x29c, (0x1ff << 7),
				    (pi->nphy_papd_epsilon_offset[core]) << 7);

		}

		wlc_phy_ipa_set_tx_digi_filts_nphy(pi);
	} else if (NREV_GE(pi->pubpi.phy_rev, 5)) {
		wlc_phy_extpa_set_tx_digi_filts_nphy(pi);
	}

	wlc_phy_workarounds_nphy(pi);

	wlapi_bmac_phyclk_fgc(pi->sh->physhim, ON);

	val = read_phy_reg(pi, 0x01);
	write_phy_reg(pi, 0x01, val | BBCFG_RESETCCA);
	write_phy_reg(pi, 0x01, val & (~BBCFG_RESETCCA));
	wlapi_bmac_phyclk_fgc(pi->sh->physhim, OFF);

	wlapi_bmac_macphyclk_set(pi->sh->physhim, ON);

	wlc_phy_pa_override_nphy(pi, OFF);
	wlc_phy_force_rfseq_nphy(pi, NPHY_RFSEQ_RX2TX);
	wlc_phy_force_rfseq_nphy(pi, NPHY_RFSEQ_RESET2RX);
	wlc_phy_pa_override_nphy(pi, ON);

	wlc_phy_classifier_nphy(pi, 0, 0);
	wlc_phy_clip_det_nphy(pi, 0, clip1_ths);

	if (CHSPEC_IS2G(pi->radio_chanspec))
		wlc_phy_bphy_init_nphy(pi);

	tx_pwr_ctrl_state = pi->nphy_txpwrctrl;
	wlc_phy_txpwrctrl_enable_nphy(pi, PHY_TPC_HW_OFF);

	wlc_phy_txpwr_fixpower_nphy(pi);

	wlc_phy_txpwrctrl_idle_tssi_nphy(pi);

	wlc_phy_txpwrctrl_pwr_setup_nphy(pi);

	if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		u32 *tx_pwrctrl_tbl = NULL;
		u16 idx;
		s16 pga_gn = 0;
		s16 pad_gn = 0;
		s32 rfpwr_offset;

		if (PHY_IPA(pi)) {
			tx_pwrctrl_tbl = wlc_phy_get_ipa_gaintbl_nphy(pi);
		} else {
			if (CHSPEC_IS5G(pi->radio_chanspec)) {
				if (NREV_IS(pi->pubpi.phy_rev, 3))
					tx_pwrctrl_tbl =
						nphy_tpc_5GHz_txgain_rev3;
				else if (NREV_IS(pi->pubpi.phy_rev, 4))
					tx_pwrctrl_tbl =
						(pi->srom_fem5g.extpagain ==
						 3) ?
						nphy_tpc_5GHz_txgain_HiPwrEPA :
						nphy_tpc_5GHz_txgain_rev4;
				else
					tx_pwrctrl_tbl =
						nphy_tpc_5GHz_txgain_rev5;
			} else {
				if (NREV_GE(pi->pubpi.phy_rev, 7)) {
					if (pi->pubpi.radiorev == 5)
						tx_pwrctrl_tbl =
						   nphy_tpc_txgain_epa_2057rev5;
					else if (pi->pubpi.radiorev == 3)
						tx_pwrctrl_tbl =
						   nphy_tpc_txgain_epa_2057rev3;
				} else {
					if (NREV_GE(pi->pubpi.phy_rev, 5) &&
					    (pi->srom_fem2g.extpagain == 3))
						tx_pwrctrl_tbl =
						       nphy_tpc_txgain_HiPwrEPA;
					else
						tx_pwrctrl_tbl =
							nphy_tpc_txgain_rev3;
				}
			}
		}

		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_CORE1TXPWRCTL, 128,
					 192, 32, tx_pwrctrl_tbl);
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_CORE2TXPWRCTL, 128,
					 192, 32, tx_pwrctrl_tbl);

		pi->nphy_gmval = (u16) ((*tx_pwrctrl_tbl >> 16) & 0x7000);

		if (NREV_GE(pi->pubpi.phy_rev, 7)) {

			for (idx = 0; idx < 128; idx++) {
				pga_gn = (tx_pwrctrl_tbl[idx] >> 24) & 0xf;
				pad_gn = (tx_pwrctrl_tbl[idx] >> 19) & 0x1f;
				rfpwr_offset = get_rf_pwr_offset(pi, pga_gn,
								 pad_gn);
				wlc_phy_table_write_nphy(
					pi,
					NPHY_TBL_ID_CORE1TXPWRCTL,
					1, 576 + idx, 32,
					&rfpwr_offset);
				wlc_phy_table_write_nphy(
					pi,
					NPHY_TBL_ID_CORE2TXPWRCTL,
					1, 576 + idx, 32,
					&rfpwr_offset);
			}
		} else {

			for (idx = 0; idx < 128; idx++) {
				pga_gn = (tx_pwrctrl_tbl[idx] >> 24) & 0xf;
				if (CHSPEC_IS2G(pi->radio_chanspec))
					rfpwr_offset = (s16)
						 nphy_papd_pga_gain_delta_ipa_2g
								       [pga_gn];
				else
					rfpwr_offset = (s16)
						 nphy_papd_pga_gain_delta_ipa_5g
								       [pga_gn];

				wlc_phy_table_write_nphy(
					pi,
					NPHY_TBL_ID_CORE1TXPWRCTL,
					1, 576 + idx, 32,
					&rfpwr_offset);
				wlc_phy_table_write_nphy(
					pi,
					NPHY_TBL_ID_CORE2TXPWRCTL,
					1, 576 + idx, 32,
					&rfpwr_offset);
			}

		}
	} else {

		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_CORE1TXPWRCTL, 128,
					 192, 32, nphy_tpc_txgain);
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_CORE2TXPWRCTL, 128,
					 192, 32, nphy_tpc_txgain);
	}

	if (pi->sh->phyrxchain != 0x3)
		wlc_phy_rxcore_setstate_nphy((struct brcms_phy_pub *) pi,
					     pi->sh->phyrxchain);

	if (PHY_PERICAL_MPHASE_PENDING(pi))
		wlc_phy_cal_perical_mphase_restart(pi);

	if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		do_rssi_cal = (CHSPEC_IS2G(pi->radio_chanspec)) ?
			      (pi->nphy_rssical_chanspec_2G == 0) :
			      (pi->nphy_rssical_chanspec_5G == 0);

		if (do_rssi_cal)
			wlc_phy_rssi_cal_nphy(pi);
		else
			wlc_phy_restore_rssical_nphy(pi);
	} else {
		wlc_phy_rssi_cal_nphy(pi);
	}

	if (!SCAN_RM_IN_PROGRESS(pi))
		do_nphy_cal = (CHSPEC_IS2G(pi->radio_chanspec)) ?
			      (pi->nphy_iqcal_chanspec_2G == 0) :
			      (pi->nphy_iqcal_chanspec_5G == 0);

	if (!pi->do_initcal)
		do_nphy_cal = false;

	if (do_nphy_cal) {

		target_gain = wlc_phy_get_tx_gain_nphy(pi);

		if (pi->antsel_type == ANTSEL_2x3)
			wlc_phy_antsel_init((struct brcms_phy_pub *) pi,
					    true);

		if (pi->nphy_perical != PHY_PERICAL_MPHASE) {
			wlc_phy_rssi_cal_nphy(pi);

			if (NREV_GE(pi->pubpi.phy_rev, 3)) {
				pi->nphy_cal_orig_pwr_idx[0] =
					pi->nphy_txpwrindex[PHY_CORE_0]
					.
					index_internal;
				pi->nphy_cal_orig_pwr_idx[1] =
					pi->nphy_txpwrindex[PHY_CORE_1]
					.
					index_internal;

				wlc_phy_precal_txgain_nphy(pi);
				target_gain =
					wlc_phy_get_tx_gain_nphy(pi);
			}

			if (wlc_phy_cal_txiqlo_nphy
				    (pi, target_gain, true,
				    false) == 0) {
				if (wlc_phy_cal_rxiq_nphy
					    (pi, target_gain, 2,
					    false) == 0)
					wlc_phy_savecal_nphy(pi);

			}
		} else if (pi->mphase_cal_phase_id ==
			   MPHASE_CAL_STATE_IDLE) {
			wlc_phy_cal_perical((struct brcms_phy_pub *) pi,
					    PHY_PERICAL_PHYINIT);
		}
	} else {
		wlc_phy_restorecal_nphy(pi);
	}

	wlc_phy_txpwrctrl_coeff_setup_nphy(pi);

	wlc_phy_txpwrctrl_enable_nphy(pi, tx_pwr_ctrl_state);

	wlc_phy_nphy_tkip_rifs_war(pi, pi->sh->_rifs_phy);

	if (NREV_GE(pi->pubpi.phy_rev, 3) && NREV_LE(pi->pubpi.phy_rev, 6))

		write_phy_reg(pi, 0x70, 50);

	wlc_phy_txlpfbw_nphy(pi);

	wlc_phy_spurwar_nphy(pi);

}