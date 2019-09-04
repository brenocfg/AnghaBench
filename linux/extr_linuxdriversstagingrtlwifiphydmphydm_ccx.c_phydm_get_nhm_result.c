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
typedef  void* u16 ;
struct ccx_info {void* NHM_duration; void** NHM_result; } ;
struct phy_dm_struct {int support_ic_type; struct ccx_info dm_ccx_info; } ;

/* Variables and functions */
 int MASKBYTE0 ; 
 int MASKBYTE1 ; 
 int MASKBYTE2 ; 
 int MASKBYTE3 ; 
 int MASKLWORD ; 
 int ODM_IC_11AC_SERIES ; 
 int ODM_IC_11N_SERIES ; 
 int /*<<< orphan*/  ODM_REG_NHM_CNT10_TO_CNT11_11N ; 
 int /*<<< orphan*/  ODM_REG_NHM_CNT11_TO_CNT8_11AC ; 
 int /*<<< orphan*/  ODM_REG_NHM_CNT7_TO_CNT4_11AC ; 
 int /*<<< orphan*/  ODM_REG_NHM_CNT7_TO_CNT4_11N ; 
 int /*<<< orphan*/  ODM_REG_NHM_CNT9_TO_CNT8_11N ; 
 int /*<<< orphan*/  ODM_REG_NHM_CNT_11AC ; 
 int /*<<< orphan*/  ODM_REG_NHM_CNT_11N ; 
 int /*<<< orphan*/  ODM_REG_NHM_DUR_READY_11AC ; 
 int odm_read_4byte (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 

void phydm_get_nhm_result(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u32 value32;
	struct ccx_info *ccx_info = &dm->dm_ccx_info;

	if (dm->support_ic_type & ODM_IC_11AC_SERIES) {
		value32 = odm_read_4byte(dm, ODM_REG_NHM_CNT_11AC);
		ccx_info->NHM_result[0] = (u8)(value32 & MASKBYTE0);
		ccx_info->NHM_result[1] = (u8)((value32 & MASKBYTE1) >> 8);
		ccx_info->NHM_result[2] = (u8)((value32 & MASKBYTE2) >> 16);
		ccx_info->NHM_result[3] = (u8)((value32 & MASKBYTE3) >> 24);

		value32 = odm_read_4byte(dm, ODM_REG_NHM_CNT7_TO_CNT4_11AC);
		ccx_info->NHM_result[4] = (u8)(value32 & MASKBYTE0);
		ccx_info->NHM_result[5] = (u8)((value32 & MASKBYTE1) >> 8);
		ccx_info->NHM_result[6] = (u8)((value32 & MASKBYTE2) >> 16);
		ccx_info->NHM_result[7] = (u8)((value32 & MASKBYTE3) >> 24);

		value32 = odm_read_4byte(dm, ODM_REG_NHM_CNT11_TO_CNT8_11AC);
		ccx_info->NHM_result[8] = (u8)(value32 & MASKBYTE0);
		ccx_info->NHM_result[9] = (u8)((value32 & MASKBYTE1) >> 8);
		ccx_info->NHM_result[10] = (u8)((value32 & MASKBYTE2) >> 16);
		ccx_info->NHM_result[11] = (u8)((value32 & MASKBYTE3) >> 24);

		/*Get NHM duration*/
		value32 = odm_read_4byte(dm, ODM_REG_NHM_DUR_READY_11AC);
		ccx_info->NHM_duration = (u16)(value32 & MASKLWORD);
	}

	else if (dm->support_ic_type & ODM_IC_11N_SERIES) {
		value32 = odm_read_4byte(dm, ODM_REG_NHM_CNT_11N);
		ccx_info->NHM_result[0] = (u8)(value32 & MASKBYTE0);
		ccx_info->NHM_result[1] = (u8)((value32 & MASKBYTE1) >> 8);
		ccx_info->NHM_result[2] = (u8)((value32 & MASKBYTE2) >> 16);
		ccx_info->NHM_result[3] = (u8)((value32 & MASKBYTE3) >> 24);

		value32 = odm_read_4byte(dm, ODM_REG_NHM_CNT7_TO_CNT4_11N);
		ccx_info->NHM_result[4] = (u8)(value32 & MASKBYTE0);
		ccx_info->NHM_result[5] = (u8)((value32 & MASKBYTE1) >> 8);
		ccx_info->NHM_result[6] = (u8)((value32 & MASKBYTE2) >> 16);
		ccx_info->NHM_result[7] = (u8)((value32 & MASKBYTE3) >> 24);

		value32 = odm_read_4byte(dm, ODM_REG_NHM_CNT9_TO_CNT8_11N);
		ccx_info->NHM_result[8] = (u8)((value32 & MASKBYTE2) >> 16);
		ccx_info->NHM_result[9] = (u8)((value32 & MASKBYTE3) >> 24);

		value32 = odm_read_4byte(dm, ODM_REG_NHM_CNT10_TO_CNT11_11N);
		ccx_info->NHM_result[10] = (u8)((value32 & MASKBYTE2) >> 16);
		ccx_info->NHM_result[11] = (u8)((value32 & MASKBYTE3) >> 24);

		/*Get NHM duration*/
		value32 = odm_read_4byte(dm, ODM_REG_NHM_CNT10_TO_CNT11_11N);
		ccx_info->NHM_duration = (u16)(value32 & MASKLWORD);
	}
}