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
typedef  int u8 ;
typedef  int u32 ;
struct phy_dm_struct {int th_l2h_ini; int th_edcca_hl_diff; int support_ic_type; int adaptivity_igi_upper; int dc_backoff; } ;
struct adaptivity_statistics {int igi_base; int h2l_lb; int l2h_lb; } ;
typedef  int s8 ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int NONE ; 
 int ODM_IC_11AC_SERIES ; 
 int ODM_IC_11N_SERIES ; 
 int /*<<< orphan*/  ODM_REG_DBG_RPT_11AC ; 
 int /*<<< orphan*/  ODM_REG_DBG_RPT_11N ; 
 int /*<<< orphan*/  ODM_REG_RPT_11AC ; 
 int /*<<< orphan*/  ODM_REG_RPT_11N ; 
 int ODM_RTL8188E ; 
 int ODM_RTL8192E ; 
 int ODM_RTL8723B ; 
 int ODM_RTL8812 ; 
 int ODM_RTL8821 ; 
 int ODM_RTL8881A ; 
 int /*<<< orphan*/  ODM_delay_ms (int) ; 
 int /*<<< orphan*/  PHYDM_ADAPTIVITY ; 
 int /*<<< orphan*/  PHYDM_PAUSE ; 
 int /*<<< orphan*/  PHYDM_PAUSE_LEVEL_0 ; 
 int /*<<< orphan*/  PHYDM_RESUME ; 
 int odm_get_bb_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_pause_dig (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phydm_disable_lna ; 
 int /*<<< orphan*/  phydm_enable_lna ; 
 scalar_t__ phydm_get_structure (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydm_rx_mode ; 
 int /*<<< orphan*/  phydm_set_edcca_threshold (struct phy_dm_struct*,int,int) ; 
 int /*<<< orphan*/  phydm_set_lna (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydm_set_trx_mux (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydm_standby_mode ; 
 int /*<<< orphan*/  phydm_tx_mode ; 

void phydm_search_pwdb_lower_bound(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct adaptivity_statistics *adaptivity =
		(struct adaptivity_statistics *)phydm_get_structure(
			dm, PHYDM_ADAPTIVITY);
	u32 value32 = 0, reg_value32 = 0;
	u8 cnt, try_count = 0;
	u8 tx_edcca1 = 0, tx_edcca0 = 0;
	bool is_adjust = true;
	s8 th_l2h_dmc, th_h2l_dmc, igi_target = 0x32;
	s8 diff;
	u8 IGI = adaptivity->igi_base + 30 + (u8)dm->th_l2h_ini -
		 (u8)dm->th_edcca_hl_diff;

	if (dm->support_ic_type & (ODM_RTL8723B | ODM_RTL8188E | ODM_RTL8192E |
				   ODM_RTL8812 | ODM_RTL8821 | ODM_RTL8881A)) {
		phydm_set_lna(dm, phydm_disable_lna);
	} else {
		phydm_set_trx_mux(dm, phydm_standby_mode, phydm_standby_mode);
		odm_pause_dig(dm, PHYDM_PAUSE, PHYDM_PAUSE_LEVEL_0, 0x7e);
	}

	diff = igi_target - (s8)IGI;
	th_l2h_dmc = dm->th_l2h_ini + diff;
	if (th_l2h_dmc > 10)
		th_l2h_dmc = 10;
	th_h2l_dmc = th_l2h_dmc - dm->th_edcca_hl_diff;

	phydm_set_edcca_threshold(dm, th_h2l_dmc, th_l2h_dmc);
	ODM_delay_ms(30);

	while (is_adjust) {
		if (dm->support_ic_type & ODM_IC_11N_SERIES) {
			odm_set_bb_reg(dm, ODM_REG_DBG_RPT_11N, MASKDWORD, 0x0);
			reg_value32 =
				odm_get_bb_reg(dm, ODM_REG_RPT_11N, MASKDWORD);
		} else if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
			odm_set_bb_reg(dm, ODM_REG_DBG_RPT_11AC, MASKDWORD,
				       0x0);
			reg_value32 =
				odm_get_bb_reg(dm, ODM_REG_RPT_11AC, MASKDWORD);
		}
		while (reg_value32 & BIT(3) && try_count < 3) {
			ODM_delay_ms(3);
			try_count = try_count + 1;
			if (dm->support_ic_type & ODM_IC_11N_SERIES)
				reg_value32 = odm_get_bb_reg(
					dm, ODM_REG_RPT_11N, MASKDWORD);
			else if (dm->support_ic_type & ODM_IC_11AC_SERIES)
				reg_value32 = odm_get_bb_reg(
					dm, ODM_REG_RPT_11AC, MASKDWORD);
		}
		try_count = 0;

		for (cnt = 0; cnt < 20; cnt++) {
			if (dm->support_ic_type & ODM_IC_11N_SERIES) {
				odm_set_bb_reg(dm, ODM_REG_DBG_RPT_11N,
					       MASKDWORD, 0x208);
				value32 = odm_get_bb_reg(dm, ODM_REG_RPT_11N,
							 MASKDWORD);
			} else if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
				odm_set_bb_reg(dm, ODM_REG_DBG_RPT_11AC,
					       MASKDWORD, 0x209);
				value32 = odm_get_bb_reg(dm, ODM_REG_RPT_11AC,
							 MASKDWORD);
			}
			if (value32 & BIT(30) &&
			    (dm->support_ic_type &
			     (ODM_RTL8723B | ODM_RTL8188E)))
				tx_edcca1 = tx_edcca1 + 1;
			else if (value32 & BIT(29))
				tx_edcca1 = tx_edcca1 + 1;
			else
				tx_edcca0 = tx_edcca0 + 1;
		}

		if (tx_edcca1 > 1) {
			IGI = IGI - 1;
			th_l2h_dmc = th_l2h_dmc + 1;
			if (th_l2h_dmc > 10)
				th_l2h_dmc = 10;
			th_h2l_dmc = th_l2h_dmc - dm->th_edcca_hl_diff;

			phydm_set_edcca_threshold(dm, th_h2l_dmc, th_l2h_dmc);
			if (th_l2h_dmc == 10) {
				is_adjust = false;
				adaptivity->h2l_lb = th_h2l_dmc;
				adaptivity->l2h_lb = th_l2h_dmc;
				dm->adaptivity_igi_upper = IGI;
			}

			tx_edcca1 = 0;
			tx_edcca0 = 0;

		} else {
			is_adjust = false;
			adaptivity->h2l_lb = th_h2l_dmc;
			adaptivity->l2h_lb = th_l2h_dmc;
			dm->adaptivity_igi_upper = IGI;
			tx_edcca1 = 0;
			tx_edcca0 = 0;
		}
	}

	dm->adaptivity_igi_upper = dm->adaptivity_igi_upper - dm->dc_backoff;
	adaptivity->h2l_lb = adaptivity->h2l_lb + dm->dc_backoff;
	adaptivity->l2h_lb = adaptivity->l2h_lb + dm->dc_backoff;

	if (dm->support_ic_type & (ODM_RTL8723B | ODM_RTL8188E | ODM_RTL8192E |
				   ODM_RTL8812 | ODM_RTL8821 | ODM_RTL8881A)) {
		phydm_set_lna(dm, phydm_enable_lna);
	} else {
		phydm_set_trx_mux(dm, phydm_tx_mode, phydm_rx_mode);
		odm_pause_dig(dm, PHYDM_RESUME, PHYDM_PAUSE_LEVEL_0, NONE);
	}

	phydm_set_edcca_threshold(dm, 0x7f, 0x7f); /*resume to no link state*/
}