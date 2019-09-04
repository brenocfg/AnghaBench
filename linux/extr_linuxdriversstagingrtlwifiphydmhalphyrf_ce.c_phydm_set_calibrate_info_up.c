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
typedef  size_t u8 ;
struct txpwrtrack_cfg {size_t rf_path_count; } ;
struct phy_dm_struct {int dummy; } ;
struct dm_rf_calibration_struct {size_t* delta_power_index_last; size_t* delta_power_index; size_t* absolute_ofdm_swing_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_TX_PWR_TRACK ; 
 size_t ODM_RF_PATH_A ; 
#define  ODM_RF_PATH_B 130 
#define  ODM_RF_PATH_C 129 
#define  ODM_RF_PATH_D 128 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,size_t,...) ; 

__attribute__((used)) static inline void phydm_set_calibrate_info_up(
	struct phy_dm_struct *dm, struct txpwrtrack_cfg *c, u8 delta,
	struct dm_rf_calibration_struct *cali_info,
	u8 *delta_swing_table_idx_tup_a, u8 *delta_swing_table_idx_tup_b,
	u8 *delta_swing_table_idx_tup_c, u8 *delta_swing_table_idx_tup_d)
{
	u8 p = 0;

	for (p = ODM_RF_PATH_A; p < c->rf_path_count; p++) {
		cali_info->delta_power_index_last[p] =
			cali_info->delta_power_index
				[p]; /*recording poer index offset*/
		switch (p) {
		case ODM_RF_PATH_B:
			ODM_RT_TRACE(dm, ODM_COMP_TX_PWR_TRACK,
				     "delta_swing_table_idx_tup_b[%d] = %d\n",
				     delta, delta_swing_table_idx_tup_b[delta]);

			cali_info->delta_power_index[p] =
				delta_swing_table_idx_tup_b[delta];
			/*Record delta swing for mix mode pwr tracking*/
			cali_info->absolute_ofdm_swing_idx[p] =
				delta_swing_table_idx_tup_b[delta];
			ODM_RT_TRACE(
				dm, ODM_COMP_TX_PWR_TRACK,
				"******Temp is higher and cali_info->absolute_ofdm_swing_idx[ODM_RF_PATH_B] = %d\n",
				cali_info->absolute_ofdm_swing_idx[p]);
			break;

		case ODM_RF_PATH_C:
			ODM_RT_TRACE(dm, ODM_COMP_TX_PWR_TRACK,
				     "delta_swing_table_idx_tup_c[%d] = %d\n",
				     delta, delta_swing_table_idx_tup_c[delta]);

			cali_info->delta_power_index[p] =
				delta_swing_table_idx_tup_c[delta];
			/*Record delta swing for mix mode pwr tracking*/
			cali_info->absolute_ofdm_swing_idx[p] =
				delta_swing_table_idx_tup_c[delta];
			ODM_RT_TRACE(
				dm, ODM_COMP_TX_PWR_TRACK,
				"******Temp is higher and cali_info->absolute_ofdm_swing_idx[ODM_RF_PATH_C] = %d\n",
				cali_info->absolute_ofdm_swing_idx[p]);
			break;

		case ODM_RF_PATH_D:
			ODM_RT_TRACE(dm, ODM_COMP_TX_PWR_TRACK,
				     "delta_swing_table_idx_tup_d[%d] = %d\n",
				     delta, delta_swing_table_idx_tup_d[delta]);

			cali_info->delta_power_index[p] =
				delta_swing_table_idx_tup_d[delta];
			/*Record delta swing for mix mode pwr tracking*/
			cali_info->absolute_ofdm_swing_idx[p] =
				delta_swing_table_idx_tup_d[delta];
			ODM_RT_TRACE(
				dm, ODM_COMP_TX_PWR_TRACK,
				"******Temp is higher and cali_info->absolute_ofdm_swing_idx[ODM_RF_PATH_D] = %d\n",
				cali_info->absolute_ofdm_swing_idx[p]);
			break;

		default:
			ODM_RT_TRACE(dm, ODM_COMP_TX_PWR_TRACK,
				     "delta_swing_table_idx_tup_a[%d] = %d\n",
				     delta, delta_swing_table_idx_tup_a[delta]);

			cali_info->delta_power_index[p] =
				delta_swing_table_idx_tup_a[delta];
			/*Record delta swing for mix mode pwr tracking*/
			cali_info->absolute_ofdm_swing_idx[p] =
				delta_swing_table_idx_tup_a[delta];
			ODM_RT_TRACE(
				dm, ODM_COMP_TX_PWR_TRACK,
				"******Temp is higher and cali_info->absolute_ofdm_swing_idx[ODM_RF_PATH_A] = %d\n",
				cali_info->absolute_ofdm_swing_idx[p]);
			break;
		}
	}
}