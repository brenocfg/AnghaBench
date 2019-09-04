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
struct phy_dm_struct {int support_ic_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ODM_IC_11AC_SERIES ; 
 int ODM_IC_11N_SERIES ; 
 int /*<<< orphan*/  ODM_REG_CLM_11AC ; 
 int /*<<< orphan*/  ODM_REG_CLM_11N ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void phydm_clm_trigger(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
		odm_set_bb_reg(dm, ODM_REG_CLM_11AC, BIT(0),
			       0x0); /*Trigger CLM*/
		odm_set_bb_reg(dm, ODM_REG_CLM_11AC, BIT(0), 0x1);
	} else if (dm->support_ic_type & ODM_IC_11N_SERIES) {
		odm_set_bb_reg(dm, ODM_REG_CLM_11N, BIT(0),
			       0x0); /*Trigger CLM*/
		odm_set_bb_reg(dm, ODM_REG_CLM_11N, BIT(0), 0x1);
	}
}