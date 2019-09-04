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
typedef  scalar_t__ u32 ;
struct phy_dm_struct {int support_ic_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int ODM_IC_11AC_SERIES ; 
 int ODM_IC_11N_SERIES ; 
 int /*<<< orphan*/  ODM_REG_CLM_READY_11N ; 
 int /*<<< orphan*/  ODM_REG_CLM_RESULT_11AC ; 
 int /*<<< orphan*/  ODM_REG_NHM_DUR_READY_11AC ; 
 int /*<<< orphan*/  ODM_delay_ms (int) ; 
 scalar_t__ odm_get_bb_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool phydm_check_nhm_ready(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 value32 = 0;
	u8 i;
	bool ret = false;

	if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
		value32 =
			odm_get_bb_reg(dm, ODM_REG_CLM_RESULT_11AC, MASKDWORD);

		for (i = 0; i < 200; i++) {
			ODM_delay_ms(1);
			if (odm_get_bb_reg(dm, ODM_REG_NHM_DUR_READY_11AC,
					   BIT(17))) {
				ret = 1;
				break;
			}
		}
	}

	else if (dm->support_ic_type & ODM_IC_11N_SERIES) {
		value32 = odm_get_bb_reg(dm, ODM_REG_CLM_READY_11N, MASKDWORD);

		for (i = 0; i < 200; i++) {
			ODM_delay_ms(1);
			if (odm_get_bb_reg(dm, ODM_REG_NHM_DUR_READY_11AC,
					   BIT(17))) {
				ret = 1;
				break;
			}
		}
	}
	return ret;
}