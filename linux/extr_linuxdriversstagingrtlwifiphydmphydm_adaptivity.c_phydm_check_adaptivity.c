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
struct phy_dm_struct {int support_ability; int adaptivity_enable; int support_ic_type; int adaptivity_flag; scalar_t__ is_linked; } ;
struct adaptivity_statistics {int is_check; scalar_t__ acs_for_adaptivity; scalar_t__ dynamic_link_adaptivity; } ;

/* Variables and functions */
 int ODM_BB_ADAPTIVITY ; 
 int ODM_IC_11AC_GAIN_IDX_EDCCA ; 
 int ODM_IC_11N_GAIN_IDX_EDCCA ; 
 int /*<<< orphan*/  PHYDM_ADAPTIVITY ; 
 int /*<<< orphan*/  phydm_check_environment (struct phy_dm_struct*) ; 
 scalar_t__ phydm_get_structure (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydm_nhm_counter_statistics (struct phy_dm_struct*) ; 

void phydm_check_adaptivity(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct adaptivity_statistics *adaptivity =
		(struct adaptivity_statistics *)phydm_get_structure(
			dm, PHYDM_ADAPTIVITY);

	if (dm->support_ability & ODM_BB_ADAPTIVITY) {
		if (adaptivity->dynamic_link_adaptivity ||
		    adaptivity->acs_for_adaptivity) {
			if (dm->is_linked && !adaptivity->is_check) {
				phydm_nhm_counter_statistics(dm);
				phydm_check_environment(dm);
			} else if (!dm->is_linked) {
				adaptivity->is_check = false;
			}
		} else {
			dm->adaptivity_enable = true;

			if (dm->support_ic_type & (ODM_IC_11AC_GAIN_IDX_EDCCA |
						   ODM_IC_11N_GAIN_IDX_EDCCA))
				dm->adaptivity_flag = false;
			else
				dm->adaptivity_flag = true;
		}
	} else {
		dm->adaptivity_enable = false;
		dm->adaptivity_flag = false;
	}
}