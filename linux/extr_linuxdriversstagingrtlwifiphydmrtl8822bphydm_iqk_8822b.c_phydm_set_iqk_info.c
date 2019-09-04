#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  iqk_step; } ;
struct phy_dm_struct {TYPE_1__ rf_calibrate_info; } ;
struct dm_iqk_info {int rxiqk_step; int** rxiqk_fail_code; int /*<<< orphan*/  kcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_CALIBRATION ; 
 size_t ODM_RF_PATH_A ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int) ; 
 int _iqk_rx_iqk_by_path_8822b (struct phy_dm_struct*,size_t) ; 

__attribute__((used)) static inline void phydm_set_iqk_info(struct phy_dm_struct *dm,
				      struct dm_iqk_info *iqk_info, u8 status)
{
	bool KFAIL = true;

	while (1) {
		KFAIL = _iqk_rx_iqk_by_path_8822b(dm, ODM_RF_PATH_A);
		if (status == 0)
			ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION,
				     "[IQK]S0RXK KFail = 0x%x\n", KFAIL);
		else if (status == 1)
			ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION,
				     "[IQK]S1RXK KFail = 0x%x\n", KFAIL);
		if (iqk_info->rxiqk_step == 5) {
			dm->rf_calibrate_info.iqk_step++;
			iqk_info->rxiqk_step = 1;
			if (KFAIL && status == 0)
				ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION,
					     "[IQK]S0RXK fail code: %d!!!\n",
					     iqk_info->rxiqk_fail_code
						     [0][ODM_RF_PATH_A]);
			else if (KFAIL && status == 1)
				ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION,
					     "[IQK]S1RXK fail code: %d!!!\n",
					     iqk_info->rxiqk_fail_code
						     [0][ODM_RF_PATH_A]);
			break;
		}
	}

	iqk_info->kcount++;
}