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
struct TYPE_2__ {int iqk_step; } ;
struct dm_iqk_info {int kcount; int*** retry_count; int*** gs_retry_count; int /*<<< orphan*/ *** iqk_fail_report; int /*<<< orphan*/ * lok_fail; } ;
struct phy_dm_struct {int* band_width; TYPE_1__ rf_calibrate_info; struct dm_iqk_info IQK_info; } ;

/* Variables and functions */
 size_t GSRXK1 ; 
 size_t GSRXK2 ; 
 int /*<<< orphan*/  ODM_COMP_CALIBRATION ; 
 size_t ODM_RF_PATH_A ; 
 size_t ODM_RF_PATH_B ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,...) ; 
 size_t RXIQK ; 
 size_t RXIQK1 ; 
 size_t RXIQK2 ; 
 size_t TXIQK ; 
 int /*<<< orphan*/  _iqk_lok_setting_8822b (struct phy_dm_struct*,size_t) ; 
 int _iqk_one_shot_8822b (struct phy_dm_struct*,size_t,size_t) ; 
 int /*<<< orphan*/  _iqk_txk_setting_8822b (struct phy_dm_struct*,size_t) ; 
 int /*<<< orphan*/  _lok_one_shot_8822b (struct phy_dm_struct*,size_t) ; 
 int kcount_limit_80m ; 
 int kcount_limit_others ; 
 int /*<<< orphan*/  odm_write_4byte (struct phy_dm_struct*,int,int) ; 
 int /*<<< orphan*/  phydm_set_iqk_info (struct phy_dm_struct*,struct dm_iqk_info*,int) ; 

__attribute__((used)) static void _iqk_iqk_by_path_8822b(void *dm_void, bool segment_iqk)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct dm_iqk_info *iqk_info = &dm->IQK_info;
	bool KFAIL = true;
	u8 i, kcount_limit;

	if (*dm->band_width == 2)
		kcount_limit = kcount_limit_80m;
	else
		kcount_limit = kcount_limit_others;

	while (1) {
		switch (dm->rf_calibrate_info.iqk_step) {
		case 1: /*S0 LOK*/
			_iqk_lok_setting_8822b(dm, ODM_RF_PATH_A);
			_lok_one_shot_8822b(dm, ODM_RF_PATH_A);
			dm->rf_calibrate_info.iqk_step++;
			break;
		case 2: /*S1 LOK*/
			_iqk_lok_setting_8822b(dm, ODM_RF_PATH_B);
			_lok_one_shot_8822b(dm, ODM_RF_PATH_B);
			dm->rf_calibrate_info.iqk_step++;
			break;
		case 3: /*S0 TXIQK*/
			_iqk_txk_setting_8822b(dm, ODM_RF_PATH_A);
			KFAIL = _iqk_one_shot_8822b(dm, ODM_RF_PATH_A, TXIQK);
			iqk_info->kcount++;
			ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION,
				     "[IQK]S0TXK KFail = 0x%x\n", KFAIL);

			if (KFAIL &&
			    (iqk_info->retry_count[0][ODM_RF_PATH_A][TXIQK] <
			     3))
				iqk_info->retry_count[0][ODM_RF_PATH_A]
						     [TXIQK]++;
			else
				dm->rf_calibrate_info.iqk_step++;
			break;
		case 4: /*S1 TXIQK*/
			_iqk_txk_setting_8822b(dm, ODM_RF_PATH_B);
			KFAIL = _iqk_one_shot_8822b(dm, ODM_RF_PATH_B, TXIQK);
			iqk_info->kcount++;
			ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION,
				     "[IQK]S1TXK KFail = 0x%x\n", KFAIL);
			if (KFAIL &&
			    iqk_info->retry_count[0][ODM_RF_PATH_B][TXIQK] < 3)
				iqk_info->retry_count[0][ODM_RF_PATH_B]
						     [TXIQK]++;
			else
				dm->rf_calibrate_info.iqk_step++;
			break;
		case 5: /*S0 RXIQK*/
			phydm_set_iqk_info(dm, iqk_info, 0);
			break;
		case 6: /*S1 RXIQK*/
			phydm_set_iqk_info(dm, iqk_info, 1);
			break;
		}

		if (dm->rf_calibrate_info.iqk_step == 7) {
			ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION,
				     "[IQK]==========LOK summary ==========\n");
			ODM_RT_TRACE(
				dm, ODM_COMP_CALIBRATION,
				"[IQK]PathA_LOK_notready = %d, PathB_LOK1_notready = %d\n",
				iqk_info->lok_fail[ODM_RF_PATH_A],
				iqk_info->lok_fail[ODM_RF_PATH_B]);
			ODM_RT_TRACE(dm, ODM_COMP_CALIBRATION,
				     "[IQK]==========IQK summary ==========\n");
			ODM_RT_TRACE(
				dm, ODM_COMP_CALIBRATION,
				"[IQK]PathA_TXIQK_fail = %d, PathB_TXIQK_fail = %d\n",
				iqk_info->iqk_fail_report[0][ODM_RF_PATH_A]
							 [TXIQK],
				iqk_info->iqk_fail_report[0][ODM_RF_PATH_B]
							 [TXIQK]);
			ODM_RT_TRACE(
				dm, ODM_COMP_CALIBRATION,
				"[IQK]PathA_RXIQK_fail = %d, PathB_RXIQK_fail = %d\n",
				iqk_info->iqk_fail_report[0][ODM_RF_PATH_A]
							 [RXIQK],
				iqk_info->iqk_fail_report[0][ODM_RF_PATH_B]
							 [RXIQK]);
			ODM_RT_TRACE(
				dm, ODM_COMP_CALIBRATION,
				"[IQK]PathA_TXIQK_retry = %d, PathB_TXIQK_retry = %d\n",
				iqk_info->retry_count[0][ODM_RF_PATH_A][TXIQK],
				iqk_info->retry_count[0][ODM_RF_PATH_B][TXIQK]);
			ODM_RT_TRACE(
				dm, ODM_COMP_CALIBRATION,
				"[IQK]PathA_RXK1_retry = %d, PathA_RXK2_retry = %d, PathB_RXK1_retry = %d, PathB_RXK2_retry = %d\n",
				iqk_info->retry_count[0][ODM_RF_PATH_A][RXIQK1],
				iqk_info->retry_count[0][ODM_RF_PATH_A][RXIQK2],
				iqk_info->retry_count[0][ODM_RF_PATH_B][RXIQK1],
				iqk_info->retry_count[0][ODM_RF_PATH_B]
						     [RXIQK2]);
			ODM_RT_TRACE(
				dm, ODM_COMP_CALIBRATION,
				"[IQK]PathA_GS1_retry = %d, PathA_GS2_retry = %d, PathB_GS1_retry = %d, PathB_GS2_retry = %d\n",
				iqk_info->gs_retry_count[0][ODM_RF_PATH_A]
							[GSRXK1],
				iqk_info->gs_retry_count[0][ODM_RF_PATH_A]
							[GSRXK2],
				iqk_info->gs_retry_count[0][ODM_RF_PATH_B]
							[GSRXK1],
				iqk_info->gs_retry_count[0][ODM_RF_PATH_B]
							[GSRXK2]);
			for (i = 0; i < 2; i++) {
				odm_write_4byte(dm, 0x1b00,
						0xf8000008 | i << 1);
				odm_write_4byte(dm, 0x1b2c, 0x7);
				odm_write_4byte(dm, 0x1bcc, 0x0);
			}
			break;
		}

		if (segment_iqk && (iqk_info->kcount == kcount_limit))
			break;
	}
}