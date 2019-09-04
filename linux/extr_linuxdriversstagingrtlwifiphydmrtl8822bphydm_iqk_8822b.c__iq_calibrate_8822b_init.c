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
struct dm_iqk_info {scalar_t__ iqk_times; int* lok_fail; int** iqk_fail; int** iqc_matrix; } ;
struct phy_dm_struct {struct dm_iqk_info IQK_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_CALIBRATION ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*) ; 
 int SS_8822B ; 
 int /*<<< orphan*/  phydm_init_iqk_information (struct dm_iqk_info*) ; 

__attribute__((used)) static void _iq_calibrate_8822b_init(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct dm_iqk_info *iqk_info = &dm->IQK_info;
	u8 i, j;

	if (iqk_info->iqk_times == 0) {
		ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION,
			     "[IQK]=====>PHY_IQCalibrate_8822B_Init\n");

		for (i = 0; i < SS_8822B; i++) {
			for (j = 0; j < 2; j++) {
				iqk_info->lok_fail[i] = true;
				iqk_info->iqk_fail[j][i] = true;
				iqk_info->iqc_matrix[j][i] = 0x20000000;
			}
		}

		phydm_init_iqk_information(iqk_info);
	}
}