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
struct dm_rf_calibration_struct {int /*<<< orphan*/  delta_swing_table_idx_5gb_n; int /*<<< orphan*/  delta_swing_table_idx_5gb_p; int /*<<< orphan*/  delta_swing_table_idx_5ga_n; int /*<<< orphan*/  delta_swing_table_idx_5ga_p; int /*<<< orphan*/  delta_swing_table_idx_2g_cck_b_n; int /*<<< orphan*/  delta_swing_table_idx_2g_cck_b_p; int /*<<< orphan*/  delta_swing_table_idx_2g_cck_a_n; int /*<<< orphan*/  delta_swing_table_idx_2g_cck_a_p; int /*<<< orphan*/  delta_swing_table_idx_2gb_n; int /*<<< orphan*/  delta_swing_table_idx_2gb_p; int /*<<< orphan*/  delta_swing_table_idx_2ga_n; int /*<<< orphan*/  delta_swing_table_idx_2ga_p; } ;
struct phy_dm_struct {struct dm_rf_calibration_struct rf_calibrate_info; } ;

/* Variables and functions */
 int DELTA_SWINGIDX_SIZE ; 
 int /*<<< orphan*/  ODM_COMP_INIT ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  delta_swing_index_mp_2g_cck_a_n_txpwrtrack_type6_8822b ; 
 int /*<<< orphan*/  delta_swing_index_mp_2g_cck_a_p_txpwrtrack_type6_8822b ; 
 int /*<<< orphan*/  delta_swing_index_mp_2g_cck_b_n_txpwrtrack_type6_8822b ; 
 int /*<<< orphan*/  delta_swing_index_mp_2g_cck_b_p_txpwrtrack_type6_8822b ; 
 int /*<<< orphan*/  delta_swing_index_mp_2ga_n_txpwrtrack_type6_8822b ; 
 int /*<<< orphan*/  delta_swing_index_mp_2ga_p_txpwrtrack_type6_8822b ; 
 int /*<<< orphan*/  delta_swing_index_mp_2gb_n_txpwrtrack_type6_8822b ; 
 int /*<<< orphan*/  delta_swing_index_mp_2gb_p_txpwrtrack_type6_8822b ; 
 int /*<<< orphan*/  delta_swing_index_mp_5ga_n_txpwrtrack_type6_8822b ; 
 int /*<<< orphan*/  delta_swing_index_mp_5ga_p_txpwrtrack_type6_8822b ; 
 int /*<<< orphan*/  delta_swing_index_mp_5gb_n_txpwrtrack_type6_8822b ; 
 int /*<<< orphan*/  delta_swing_index_mp_5gb_p_txpwrtrack_type6_8822b ; 
 int /*<<< orphan*/  odm_move_memory (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void odm_read_and_config_mp_8822b_txpowertrack_type6(struct phy_dm_struct *dm)
{
	struct dm_rf_calibration_struct *cali_info = &dm->rf_calibrate_info;

	ODM_RT_TRACE(dm, ODM_COMP_INIT, "===> ODM_ReadAndConfig_MP_mp_8822b\n");

	odm_move_memory(dm, cali_info->delta_swing_table_idx_2ga_p,
			delta_swing_index_mp_2ga_p_txpwrtrack_type6_8822b,
			DELTA_SWINGIDX_SIZE);
	odm_move_memory(dm, cali_info->delta_swing_table_idx_2ga_n,
			delta_swing_index_mp_2ga_n_txpwrtrack_type6_8822b,
			DELTA_SWINGIDX_SIZE);
	odm_move_memory(dm, cali_info->delta_swing_table_idx_2gb_p,
			delta_swing_index_mp_2gb_p_txpwrtrack_type6_8822b,
			DELTA_SWINGIDX_SIZE);
	odm_move_memory(dm, cali_info->delta_swing_table_idx_2gb_n,
			delta_swing_index_mp_2gb_n_txpwrtrack_type6_8822b,
			DELTA_SWINGIDX_SIZE);

	odm_move_memory(dm, cali_info->delta_swing_table_idx_2g_cck_a_p,
			delta_swing_index_mp_2g_cck_a_p_txpwrtrack_type6_8822b,
			DELTA_SWINGIDX_SIZE);
	odm_move_memory(dm, cali_info->delta_swing_table_idx_2g_cck_a_n,
			delta_swing_index_mp_2g_cck_a_n_txpwrtrack_type6_8822b,
			DELTA_SWINGIDX_SIZE);
	odm_move_memory(dm, cali_info->delta_swing_table_idx_2g_cck_b_p,
			delta_swing_index_mp_2g_cck_b_p_txpwrtrack_type6_8822b,
			DELTA_SWINGIDX_SIZE);
	odm_move_memory(dm, cali_info->delta_swing_table_idx_2g_cck_b_n,
			delta_swing_index_mp_2g_cck_b_n_txpwrtrack_type6_8822b,
			DELTA_SWINGIDX_SIZE);

	odm_move_memory(dm, cali_info->delta_swing_table_idx_5ga_p,
			delta_swing_index_mp_5ga_p_txpwrtrack_type6_8822b,
			DELTA_SWINGIDX_SIZE * 3);
	odm_move_memory(dm, cali_info->delta_swing_table_idx_5ga_n,
			delta_swing_index_mp_5ga_n_txpwrtrack_type6_8822b,
			DELTA_SWINGIDX_SIZE * 3);
	odm_move_memory(dm, cali_info->delta_swing_table_idx_5gb_p,
			delta_swing_index_mp_5gb_p_txpwrtrack_type6_8822b,
			DELTA_SWINGIDX_SIZE * 3);
	odm_move_memory(dm, cali_info->delta_swing_table_idx_5gb_n,
			delta_swing_index_mp_5gb_n_txpwrtrack_type6_8822b,
			DELTA_SWINGIDX_SIZE * 3);
}