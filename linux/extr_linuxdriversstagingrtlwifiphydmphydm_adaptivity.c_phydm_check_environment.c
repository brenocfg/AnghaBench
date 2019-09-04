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
struct phy_dm_struct {int support_ic_type; int adaptivity_flag; int adaptivity_enable; int /*<<< orphan*/  th_edcca_hl_diff_mode2; int /*<<< orphan*/  th_edcca_hl_diff; int /*<<< orphan*/  th_l2h_ini_mode2; int /*<<< orphan*/  th_l2h_ini; } ;
struct adaptivity_statistics {int is_first_link; int nhm_wait; int is_check; int /*<<< orphan*/  acs_for_adaptivity; int /*<<< orphan*/  th_edcca_hl_diff_backup; int /*<<< orphan*/  th_l2h_ini_backup; } ;

/* Variables and functions */
 int ODM_IC_11AC_GAIN_IDX_EDCCA ; 
 int ODM_IC_11N_GAIN_IDX_EDCCA ; 
 int /*<<< orphan*/  PHYDM_ADAPTIVITY ; 
 int phydm_cal_nhm_cnt (struct phy_dm_struct*) ; 
 scalar_t__ phydm_get_structure (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydm_nhm_counter_statistics (struct phy_dm_struct*) ; 

void phydm_check_environment(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct adaptivity_statistics *adaptivity =
		(struct adaptivity_statistics *)phydm_get_structure(
			dm, PHYDM_ADAPTIVITY);
	bool is_clean_environment = false;

	if (adaptivity->is_first_link) {
		if (dm->support_ic_type &
		    (ODM_IC_11AC_GAIN_IDX_EDCCA | ODM_IC_11N_GAIN_IDX_EDCCA))
			dm->adaptivity_flag = false;
		else
			dm->adaptivity_flag = true;

		adaptivity->is_first_link = false;
		return;
	}

	if (adaptivity->nhm_wait < 3) { /*Start enter NHM after 4 nhm_wait*/
		adaptivity->nhm_wait++;
		phydm_nhm_counter_statistics(dm);
		return;
	}

	phydm_nhm_counter_statistics(dm);
	is_clean_environment = phydm_cal_nhm_cnt(dm);

	if (is_clean_environment) {
		dm->th_l2h_ini =
			adaptivity->th_l2h_ini_backup; /*adaptivity mode*/
		dm->th_edcca_hl_diff = adaptivity->th_edcca_hl_diff_backup;

		dm->adaptivity_enable = true;

		if (dm->support_ic_type &
		    (ODM_IC_11AC_GAIN_IDX_EDCCA | ODM_IC_11N_GAIN_IDX_EDCCA))
			dm->adaptivity_flag = false;
		else
			dm->adaptivity_flag = true;
	} else {
		if (!adaptivity->acs_for_adaptivity) {
			dm->th_l2h_ini = dm->th_l2h_ini_mode2; /*mode2*/
			dm->th_edcca_hl_diff = dm->th_edcca_hl_diff_mode2;

			dm->adaptivity_flag = false;
			dm->adaptivity_enable = false;
		}
	}

	adaptivity->nhm_wait = 0;
	adaptivity->is_first_link = true;
	adaptivity->is_check = true;
}