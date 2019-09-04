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
struct rtl_phy {int current_channel; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct dm_rf_calibration_struct {int* delta_swing_table_idx_2ga_p; int* delta_swing_table_idx_2ga_n; int* delta_swing_table_idx_2gb_p; int* delta_swing_table_idx_2gb_n; int** delta_swing_table_idx_5ga_p; int** delta_swing_table_idx_5ga_n; int** delta_swing_table_idx_5gb_p; int** delta_swing_table_idx_5gb_n; } ;
struct phy_dm_struct {scalar_t__ adapter; struct dm_rf_calibration_struct rf_calibrate_info; } ;

/* Variables and functions */

void get_delta_swing_table_8822b(void *dm_void, u8 **temperature_up_a,
				 u8 **temperature_down_a, u8 **temperature_up_b,
				 u8 **temperature_down_b)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct dm_rf_calibration_struct *cali_info = &dm->rf_calibrate_info;

	struct rtl_priv *rtlpriv = (struct rtl_priv *)dm->adapter;
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 channel = rtlphy->current_channel;

	*temperature_up_a = cali_info->delta_swing_table_idx_2ga_p;
	*temperature_down_a = cali_info->delta_swing_table_idx_2ga_n;
	*temperature_up_b = cali_info->delta_swing_table_idx_2gb_p;
	*temperature_down_b = cali_info->delta_swing_table_idx_2gb_n;

	if (channel >= 36 && channel <= 64) {
		*temperature_up_a = cali_info->delta_swing_table_idx_5ga_p[0];
		*temperature_down_a = cali_info->delta_swing_table_idx_5ga_n[0];
		*temperature_up_b = cali_info->delta_swing_table_idx_5gb_p[0];
		*temperature_down_b = cali_info->delta_swing_table_idx_5gb_n[0];
	} else if (channel >= 100 && channel <= 144) {
		*temperature_up_a = cali_info->delta_swing_table_idx_5ga_p[1];
		*temperature_down_a = cali_info->delta_swing_table_idx_5ga_n[1];
		*temperature_up_b = cali_info->delta_swing_table_idx_5gb_p[1];
		*temperature_down_b = cali_info->delta_swing_table_idx_5gb_n[1];
	} else if (channel >= 149 && channel <= 177) {
		*temperature_up_a = cali_info->delta_swing_table_idx_5ga_p[2];
		*temperature_down_a = cali_info->delta_swing_table_idx_5ga_n[2];
		*temperature_up_b = cali_info->delta_swing_table_idx_5gb_p[2];
		*temperature_down_b = cali_info->delta_swing_table_idx_5gb_n[2];
	}
}