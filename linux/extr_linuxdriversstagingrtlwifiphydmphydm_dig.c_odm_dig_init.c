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
typedef  int u32 ;
struct dig_thres {int is_stop_dig; int is_ignore_dig; int is_psd_in_progress; int cur_ig_value; int pre_cck_cca_thres; int cur_cck_cca_thres; int is_media_connect_0; int is_media_connect_1; int bt30_cur_igi; int enable_adjust_big_jump; int big_jump_step1; int big_jump_step2; int big_jump_step3; int* big_jump_lmt; void* rx_gain_range_min; void* rx_gain_range_max; scalar_t__ pause_cckpd_level; int /*<<< orphan*/  pause_cckpd_value; scalar_t__ pause_dig_level; int /*<<< orphan*/  pause_dig_value; void* dig_dynamic_min_1; void* dig_dynamic_min_0; scalar_t__ recover_cnt; scalar_t__ large_fa_timeout; scalar_t__ large_fa_hit; void* forbidden_igi; int /*<<< orphan*/  backoff_val_range_min; int /*<<< orphan*/  backoff_val_range_max; int /*<<< orphan*/  backoff_val; int /*<<< orphan*/  fa_high_thresh; int /*<<< orphan*/  fa_low_thresh; int /*<<< orphan*/  rssi_high_thresh; int /*<<< orphan*/  rssi_low_thresh; scalar_t__ pre_ig_value; } ;
struct phy_dm_struct {int is_dm_initial_gain_enable; int board_type; int support_ic_type; struct dig_thres dm_dig_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_DIG_BACKOFF_DEFAULT ; 
 int /*<<< orphan*/  DM_DIG_BACKOFF_MAX ; 
 int /*<<< orphan*/  DM_DIG_BACKOFF_MIN ; 
 void* DM_DIG_MAX_NIC ; 
 scalar_t__ DM_DIG_MAX_PAUSE_TYPE ; 
 void* DM_DIG_MIN_NIC ; 
 int /*<<< orphan*/  DM_DIG_THRESH_HIGH ; 
 int /*<<< orphan*/  DM_DIG_THRESH_LOW ; 
 int /*<<< orphan*/  DM_FALSEALARM_THRESH_HIGH ; 
 int /*<<< orphan*/  DM_FALSEALARM_THRESH_LOW ; 
 int /*<<< orphan*/  IGI ; 
 int /*<<< orphan*/  IGI_A ; 
 int /*<<< orphan*/  MASKLWORD ; 
 int /*<<< orphan*/  ODM_BIT (int /*<<< orphan*/ ,struct phy_dm_struct*) ; 
 int ODM_BOARD_EXT_LNA ; 
 int ODM_BOARD_EXT_PA ; 
 int ODM_REG (int /*<<< orphan*/ ,struct phy_dm_struct*) ; 
 int ODM_REG_BB_AGC_SET_2_11N ; 
 int ODM_RTL8197F ; 
 int ODM_RTL8822B ; 
 int odm_get_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_memory_set (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void odm_dig_init(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct dig_thres *dig_tab = &dm->dm_dig_table;
	u32 ret_value;
	u8 i;

	dig_tab->is_stop_dig = false;
	dig_tab->is_ignore_dig = false;
	dig_tab->is_psd_in_progress = false;
	dig_tab->cur_ig_value =
		(u8)odm_get_bb_reg(dm, ODM_REG(IGI_A, dm), ODM_BIT(IGI, dm));
	dig_tab->pre_ig_value = 0;
	dig_tab->rssi_low_thresh = DM_DIG_THRESH_LOW;
	dig_tab->rssi_high_thresh = DM_DIG_THRESH_HIGH;
	dig_tab->fa_low_thresh = DM_FALSEALARM_THRESH_LOW;
	dig_tab->fa_high_thresh = DM_FALSEALARM_THRESH_HIGH;
	dig_tab->backoff_val = DM_DIG_BACKOFF_DEFAULT;
	dig_tab->backoff_val_range_max = DM_DIG_BACKOFF_MAX;
	dig_tab->backoff_val_range_min = DM_DIG_BACKOFF_MIN;
	dig_tab->pre_cck_cca_thres = 0xFF;
	dig_tab->cur_cck_cca_thres = 0x83;
	dig_tab->forbidden_igi = DM_DIG_MIN_NIC;
	dig_tab->large_fa_hit = 0;
	dig_tab->large_fa_timeout = 0;
	dig_tab->recover_cnt = 0;
	dig_tab->is_media_connect_0 = false;
	dig_tab->is_media_connect_1 = false;

	/*To initialize dm->is_dm_initial_gain_enable==false to avoid DIG err*/
	dm->is_dm_initial_gain_enable = true;

	dig_tab->dig_dynamic_min_0 = DM_DIG_MIN_NIC;
	dig_tab->dig_dynamic_min_1 = DM_DIG_MIN_NIC;

	/* To Initi BT30 IGI */
	dig_tab->bt30_cur_igi = 0x32;

	odm_memory_set(dm, dig_tab->pause_dig_value, 0,
		       (DM_DIG_MAX_PAUSE_TYPE + 1));
	dig_tab->pause_dig_level = 0;
	odm_memory_set(dm, dig_tab->pause_cckpd_value, 0,
		       (DM_DIG_MAX_PAUSE_TYPE + 1));
	dig_tab->pause_cckpd_level = 0;

	if (dm->board_type & (ODM_BOARD_EXT_PA | ODM_BOARD_EXT_LNA)) {
		dig_tab->rx_gain_range_max = DM_DIG_MAX_NIC;
		dig_tab->rx_gain_range_min = DM_DIG_MIN_NIC;
	} else {
		dig_tab->rx_gain_range_max = DM_DIG_MAX_NIC;
		dig_tab->rx_gain_range_min = DM_DIG_MIN_NIC;
	}

	dig_tab->enable_adjust_big_jump = 1;
	if (dm->support_ic_type & ODM_RTL8822B) {
		ret_value = odm_get_bb_reg(dm, 0x8c8, MASKLWORD);
		dig_tab->big_jump_step1 = (u8)(ret_value & 0xe) >> 1;
		dig_tab->big_jump_step2 = (u8)(ret_value & 0x30) >> 4;
		dig_tab->big_jump_step3 = (u8)(ret_value & 0xc0) >> 6;

	} else if (dm->support_ic_type & ODM_RTL8197F) {
		ret_value =
			odm_get_bb_reg(dm, ODM_REG_BB_AGC_SET_2_11N, MASKLWORD);
		dig_tab->big_jump_step1 = (u8)(ret_value & 0xe) >> 1;
		dig_tab->big_jump_step2 = (u8)(ret_value & 0x30) >> 4;
		dig_tab->big_jump_step3 = (u8)(ret_value & 0xc0) >> 6;
	}
	if (dm->support_ic_type & (ODM_RTL8822B | ODM_RTL8197F)) {
		for (i = 0; i < sizeof(dig_tab->big_jump_lmt); i++) {
			if (dig_tab->big_jump_lmt[i] == 0)
				dig_tab->big_jump_lmt[i] =
					0x64; /* Set -10dBm as default value */
		}
	}
}