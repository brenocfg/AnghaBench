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
struct phy_dm_struct {int support_ability; int support_ic_type; int th_l2h_ini; int th_edcca_hl_diff; scalar_t__ adaptivity_igi_upper; } ;
struct adaptivity_statistics {scalar_t__ adajust_igi_level; int h2l_lb; int l2h_lb; } ;
typedef  int s8 ;

/* Variables and functions */
 int ODM_BB_ADAPTIVITY ; 
 int ODM_IC_11AC_GAIN_IDX_EDCCA ; 
 int ODM_IC_11N_GAIN_IDX_EDCCA ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  PHYDM_ADAPTIVITY ; 
 int /*<<< orphan*/  PHYDM_COMP_ADAPTIVITY ; 
 scalar_t__ phydm_get_structure (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydm_set_edcca_threshold (struct phy_dm_struct*,int,int) ; 

void phydm_set_edcca_threshold_api(void *dm_void, u8 IGI)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct adaptivity_statistics *adaptivity =
		(struct adaptivity_statistics *)phydm_get_structure(
			dm, PHYDM_ADAPTIVITY);
	s8 th_l2h_dmc, th_h2l_dmc;
	s8 diff = 0, igi_target = 0x32;

	if (dm->support_ability & ODM_BB_ADAPTIVITY) {
		if (dm->support_ic_type &
		    (ODM_IC_11AC_GAIN_IDX_EDCCA | ODM_IC_11N_GAIN_IDX_EDCCA)) {
			if (adaptivity->adajust_igi_level > IGI)
				diff = adaptivity->adajust_igi_level - IGI;

			th_l2h_dmc = dm->th_l2h_ini - diff + igi_target;
			th_h2l_dmc = th_l2h_dmc - dm->th_edcca_hl_diff;
		} else {
			diff = igi_target - (s8)IGI;
			th_l2h_dmc = dm->th_l2h_ini + diff;
			if (th_l2h_dmc > 10)
				th_l2h_dmc = 10;

			th_h2l_dmc = th_l2h_dmc - dm->th_edcca_hl_diff;

			/*replace lower bound to prevent EDCCA always equal 1*/
			if (th_h2l_dmc < adaptivity->h2l_lb)
				th_h2l_dmc = adaptivity->h2l_lb;
			if (th_l2h_dmc < adaptivity->l2h_lb)
				th_l2h_dmc = adaptivity->l2h_lb;
		}
		ODM_RT_TRACE(
			dm, PHYDM_COMP_ADAPTIVITY,
			"API :IGI=0x%x, th_l2h_dmc = %d, th_h2l_dmc = %d\n",
			IGI, th_l2h_dmc, th_h2l_dmc);
		ODM_RT_TRACE(
			dm, PHYDM_COMP_ADAPTIVITY,
			"API :adaptivity_igi_upper=0x%x, h2l_lb = 0x%x, l2h_lb = 0x%x\n",
			dm->adaptivity_igi_upper, adaptivity->h2l_lb,
			adaptivity->l2h_lb);

		phydm_set_edcca_threshold(dm, th_h2l_dmc, th_l2h_dmc);
	}
}