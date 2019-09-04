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
typedef  void* u8 ;
typedef  int u32 ;
struct phy_dm_struct {int support_ic_type; void* nhm_cnt_1; void* nhm_cnt_0; } ;

/* Variables and functions */
 int MASKBYTE0 ; 
 int MASKBYTE1 ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int ODM_IC_11AC_SERIES ; 
 int ODM_IC_11N_SERIES ; 
 int /*<<< orphan*/  ODM_REG_NHM_CNT_11AC ; 
 int /*<<< orphan*/  ODM_REG_NHM_CNT_11N ; 
 int odm_get_bb_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void phydm_get_nhm_counter_statistics(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 value32 = 0;

	if (dm->support_ic_type & ODM_IC_11AC_SERIES)
		value32 = odm_get_bb_reg(dm, ODM_REG_NHM_CNT_11AC, MASKDWORD);
	else if (dm->support_ic_type & ODM_IC_11N_SERIES)
		value32 = odm_get_bb_reg(dm, ODM_REG_NHM_CNT_11N, MASKDWORD);

	dm->nhm_cnt_0 = (u8)(value32 & MASKBYTE0);
	dm->nhm_cnt_1 = (u8)((value32 & MASKBYTE1) >> 8);
}