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
typedef  scalar_t__ u8 ;
struct phy_dm_struct {int th_l2h_ini; int th_edcca_hl_diff; int edcca_enable; int adaptivity_enable; int th_l2h_ini_mode2; int th_edcca_hl_diff_mode2; int support_ic_type; scalar_t__ adaptivity_igi_upper; scalar_t__ mp_mode; scalar_t__ wifi_test; int /*<<< orphan*/  carrier_sense_enable; } ;
struct adaptivity_statistics {int th_l2h_ini_backup; int th_edcca_hl_diff_backup; int igi_base; int igi_target; int is_check; int is_first_link; int is_stop_edcca; scalar_t__ adajust_igi_level; scalar_t__ backup_l2h; scalar_t__ backup_h2l; scalar_t__ nhm_wait; scalar_t__ l2h_lb; scalar_t__ h2l_lb; } ;
typedef  int s8 ;

/* Variables and functions */
 int BIT (int) ; 
 int MASKDWORD ; 
 int ODM_IC_11AC_GAIN_IDX_EDCCA ; 
 int ODM_IC_11AC_SERIES ; 
 int ODM_IC_11N_GAIN_IDX_EDCCA ; 
 int ODM_IC_11N_SERIES ; 
 int /*<<< orphan*/  ODM_REG_ACBB_EDCCA_ENHANCE ; 
 int /*<<< orphan*/  ODM_REG_DBG_RPT_11AC ; 
 int /*<<< orphan*/  ODM_REG_DBG_RPT_11N ; 
 int /*<<< orphan*/  ODM_REG_EDCCA_DCNF_11N ; 
 int /*<<< orphan*/  ODM_REG_EDCCA_DCNF_97F ; 
 int /*<<< orphan*/  ODM_REG_PAGE_B1_97F ; 
 int ODM_RTL8197F ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  PHYDM_ADAPTIVITY ; 
 int /*<<< orphan*/  PHYDM_COMP_ADAPTIVITY ; 
 int dfir_loss ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  phydm_dont_ignore_edcca ; 
 scalar_t__ phydm_get_structure (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydm_mac_edcca_state (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ phydm_re_search_condition (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  phydm_search_pwdb_lower_bound (struct phy_dm_struct*) ; 
 int pwdb_upper_bound ; 

void phydm_adaptivity_init(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct adaptivity_statistics *adaptivity =
		(struct adaptivity_statistics *)phydm_get_structure(
			dm, PHYDM_ADAPTIVITY);
	s8 igi_target = 0x32;

	if (!dm->carrier_sense_enable) {
		if (dm->th_l2h_ini == 0)
			dm->th_l2h_ini = 0xf5;
	} else {
		dm->th_l2h_ini = 0xa;
	}

	if (dm->th_edcca_hl_diff == 0)
		dm->th_edcca_hl_diff = 7;
	if (dm->wifi_test || dm->mp_mode) {
		/*even no adaptivity, we still enable EDCCA, AP use mib ctrl*/
		dm->edcca_enable = false;
	} else {
		dm->edcca_enable = true;
	}

	dm->adaptivity_igi_upper = 0;
	dm->adaptivity_enable =
		false; /*use this flag to decide enable or disable*/

	dm->th_l2h_ini_mode2 = 20;
	dm->th_edcca_hl_diff_mode2 = 8;
	adaptivity->th_l2h_ini_backup = dm->th_l2h_ini;
	adaptivity->th_edcca_hl_diff_backup = dm->th_edcca_hl_diff;

	adaptivity->igi_base = 0x32;
	adaptivity->igi_target = 0x1c;
	adaptivity->h2l_lb = 0;
	adaptivity->l2h_lb = 0;
	adaptivity->nhm_wait = 0;
	adaptivity->is_check = false;
	adaptivity->is_first_link = true;
	adaptivity->adajust_igi_level = 0;
	adaptivity->is_stop_edcca = false;
	adaptivity->backup_h2l = 0;
	adaptivity->backup_l2h = 0;

	phydm_mac_edcca_state(dm, phydm_dont_ignore_edcca);

	/*Search pwdB lower bound*/
	if (dm->support_ic_type & ODM_IC_11N_SERIES)
		odm_set_bb_reg(dm, ODM_REG_DBG_RPT_11N, MASKDWORD, 0x208);
	else if (dm->support_ic_type & ODM_IC_11AC_SERIES)
		odm_set_bb_reg(dm, ODM_REG_DBG_RPT_11AC, MASKDWORD, 0x209);

	if (dm->support_ic_type & ODM_IC_11N_GAIN_IDX_EDCCA) {
		if (dm->support_ic_type & ODM_RTL8197F) {
			/*set to page B1*/
			odm_set_bb_reg(dm, ODM_REG_PAGE_B1_97F, BIT(30), 0x1);
			/*0:rx_dfir, 1: dcnf_out, 2 :rx_iq, 3: rx_nbi_nf_out*/
			odm_set_bb_reg(dm, ODM_REG_EDCCA_DCNF_97F,
				       BIT(27) | BIT(26), 0x1);
			odm_set_bb_reg(dm, ODM_REG_PAGE_B1_97F, BIT(30), 0x0);
		} else {
			/*0:rx_dfir, 1: dcnf_out, 2 :rx_iq, 3: rx_nbi_nf_out*/
			odm_set_bb_reg(dm, ODM_REG_EDCCA_DCNF_11N,
				       BIT(21) | BIT(20), 0x1);
		}
	}
	/*8814a no need to find pwdB lower bound, maybe*/
	if (dm->support_ic_type & ODM_IC_11AC_GAIN_IDX_EDCCA) {
		/*0:rx_dfir, 1: dcnf_out, 2 :rx_iq, 3: rx_nbi_nf_out*/
		odm_set_bb_reg(dm, ODM_REG_ACBB_EDCCA_ENHANCE,
			       BIT(29) | BIT(28), 0x1);
	}

	if (!(dm->support_ic_type &
	      (ODM_IC_11AC_GAIN_IDX_EDCCA | ODM_IC_11N_GAIN_IDX_EDCCA))) {
		phydm_search_pwdb_lower_bound(dm);
		if (phydm_re_search_condition(dm))
			phydm_search_pwdb_lower_bound(dm);
	}

	/*we need to consider PwdB upper bound for 8814 later IC*/
	adaptivity->adajust_igi_level =
		(u8)((dm->th_l2h_ini + igi_target) - pwdb_upper_bound +
		     dfir_loss); /*IGI = L2H - PwdB - dfir_loss*/

	ODM_RT_TRACE(
		dm, PHYDM_COMP_ADAPTIVITY,
		"th_l2h_ini = 0x%x, th_edcca_hl_diff = 0x%x, adaptivity->adajust_igi_level = 0x%x\n",
		dm->th_l2h_ini, dm->th_edcca_hl_diff,
		adaptivity->adajust_igi_level);

	/*Check this later on Windows*/
	/*phydm_set_edcca_threshold_api(dm, dig_tab->cur_ig_value);*/
}