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
 int /*<<< orphan*/  MASKDWORD ; 
 int ODM_IC_11AC_SERIES ; 
 int ODM_IC_11N_SERIES ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phydm_clean_all_csi_mask(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	if (dm->support_ic_type & ODM_IC_11N_SERIES) {
		odm_set_bb_reg(dm, 0xD40, MASKDWORD, 0);
		odm_set_bb_reg(dm, 0xD44, MASKDWORD, 0);
		odm_set_bb_reg(dm, 0xD48, MASKDWORD, 0);
		odm_set_bb_reg(dm, 0xD4c, MASKDWORD, 0);

	} else if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
		odm_set_bb_reg(dm, 0x880, MASKDWORD, 0);
		odm_set_bb_reg(dm, 0x884, MASKDWORD, 0);
		odm_set_bb_reg(dm, 0x888, MASKDWORD, 0);
		odm_set_bb_reg(dm, 0x88c, MASKDWORD, 0);
		odm_set_bb_reg(dm, 0x890, MASKDWORD, 0);
		odm_set_bb_reg(dm, 0x894, MASKDWORD, 0);
		odm_set_bb_reg(dm, 0x898, MASKDWORD, 0);
		odm_set_bb_reg(dm, 0x89c, MASKDWORD, 0);
	}
}