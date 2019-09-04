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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int num_qry_beacon_pkt; } ;
struct dig_thres {int cur_ig_value; int dig_dynamic_min_0; int is_media_connect_0; int rx_gain_range_max; int ant_div_rssi_max; int rx_gain_range_min; int forbidden_igi; int bt30_cur_igi; scalar_t__ large_fa_hit; } ;
struct phy_dm_struct {int is_linked; int support_ic_type; int* channel; scalar_t__* band_width; int* pu1_forced_igi_lb; int is_bt_limited_dig; int rssi_min; int support_ability; scalar_t__ ant_div_type; scalar_t__ is_bt_connect_process; scalar_t__ is_link_in_process; scalar_t__ is_bt_hs_operation; TYPE_1__ phy_dbg_info; scalar_t__ bsta_state; int /*<<< orphan*/  is_one_entry_only; struct dig_thres dm_dig_table; } ;
struct false_alarm_stat {int /*<<< orphan*/  cnt_all; } ;

/* Variables and functions */
 scalar_t__ CG_TRX_HW_ANTDIV ; 
 scalar_t__ CG_TRX_SMART_ANTDIV ; 
 int /*<<< orphan*/  DM_DIG_FA_TH1 ; 
 int DM_DIG_MAX_AP ; 
 int DM_DIG_MAX_NIC ; 
 int DM_DIG_MAX_OF_MIN ; 
 int DM_DIG_MIN_AP_DFS ; 
 int DM_DIG_MIN_NIC ; 
 int ODM_ANTDIV_SUPPORT ; 
 int ODM_BB_ANT_DIV ; 
 scalar_t__ ODM_BW20M ; 
 int /*<<< orphan*/  ODM_COMP_DIG ; 
 int ODM_RTL8188E ; 
 int ODM_RTL8192E ; 
 int ODM_RTL8723B ; 
 int ODM_RTL8812 ; 
 int ODM_RTL8821 ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  PHYDM_FALSEALMCNT ; 
 scalar_t__ odm_dig_abort (struct phy_dm_struct*) ; 
 int /*<<< orphan*/  odm_fa_threshold_check (struct phy_dm_struct*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int odm_forbidden_igi_check (struct phy_dm_struct*,int,int) ; 
 int /*<<< orphan*/  odm_write_dig (struct phy_dm_struct*,int) ; 
 scalar_t__ phydm_dfs_master_enabled (struct phy_dm_struct*) ; 
 int phydm_get_current_igi (int,int,int) ; 
 scalar_t__ phydm_get_structure (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 

void odm_DIG(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	/* Common parameters */
	struct dig_thres *dig_tab = &dm->dm_dig_table;
	struct false_alarm_stat *fa_cnt =
		(struct false_alarm_stat *)phydm_get_structure(
			dm, PHYDM_FALSEALMCNT);
	bool first_connect, first_dis_connect;
	u8 dig_max_of_min, dig_dynamic_min;
	u8 dm_dig_max, dm_dig_min;
	u8 current_igi = dig_tab->cur_ig_value;
	u8 offset;
	u32 dm_FA_thres[3];
	u32 tx_tp = 0, rx_tp = 0;
	bool is_dfs_band = false;
	bool is_performance = true, is_first_tp_target = false,
	     is_first_coverage = false;

	if (odm_dig_abort(dm))
		return;

	ODM_RT_TRACE(dm, ODM_COMP_DIG, "DIG Start===>\n");

	/* 1 Update status */
	{
		dig_dynamic_min = dig_tab->dig_dynamic_min_0;
		first_connect = (dm->is_linked) && !dig_tab->is_media_connect_0;
		first_dis_connect =
			(!dm->is_linked) && dig_tab->is_media_connect_0;
	}

	/* 1 Boundary Decision */
	{
		/* 2 For WIN\CE */
		if (dm->support_ic_type >= ODM_RTL8188E)
			dm_dig_max = 0x5A;
		else
			dm_dig_max = DM_DIG_MAX_NIC;

		if (dm->support_ic_type != ODM_RTL8821)
			dm_dig_min = DM_DIG_MIN_NIC;
		else
			dm_dig_min = 0x1C;

		dig_max_of_min = DM_DIG_MAX_AP;

		/* Modify lower bound for DFS band */
		if ((((*dm->channel >= 52) && (*dm->channel <= 64)) ||
		     ((*dm->channel >= 100) && (*dm->channel <= 140))) &&
		    phydm_dfs_master_enabled(dm)) {
			is_dfs_band = true;
			if (*dm->band_width == ODM_BW20M)
				dm_dig_min = DM_DIG_MIN_AP_DFS + 2;
			else
				dm_dig_min = DM_DIG_MIN_AP_DFS;
			ODM_RT_TRACE(dm, ODM_COMP_DIG,
				     "DIG: ====== In DFS band ======\n");
		}
	}
	ODM_RT_TRACE(dm, ODM_COMP_DIG,
		     "DIG: Absolutly upper bound = 0x%x, lower bound = 0x%x\n",
		     dm_dig_max, dm_dig_min);

	if (dm->pu1_forced_igi_lb && (*dm->pu1_forced_igi_lb > 0)) {
		ODM_RT_TRACE(dm, ODM_COMP_DIG, "DIG: Force IGI lb to: 0x%02x\n",
			     *dm->pu1_forced_igi_lb);
		dm_dig_min = *dm->pu1_forced_igi_lb;
		dm_dig_max = (dm_dig_min <= dm_dig_max) ? (dm_dig_max) :
							  (dm_dig_min + 1);
	}

	/* 1 Adjust boundary by RSSI */
	if (dm->is_linked && is_performance) {
		/* 2 Modify DIG upper bound */
		/* 4 Modify DIG upper bound for 92E, 8723A\B, 8821 & 8812 BT */
		if ((dm->support_ic_type & (ODM_RTL8192E | ODM_RTL8723B |
					    ODM_RTL8812 | ODM_RTL8821)) &&
		    dm->is_bt_limited_dig == 1) {
			offset = 10;
			ODM_RT_TRACE(
				dm, ODM_COMP_DIG,
				"DIG: Coex. case: Force upper bound to RSSI + %d\n",
				offset);
		} else {
			offset = 15;
		}

		if ((dm->rssi_min + offset) > dm_dig_max)
			dig_tab->rx_gain_range_max = dm_dig_max;
		else if ((dm->rssi_min + offset) < dm_dig_min)
			dig_tab->rx_gain_range_max = dm_dig_min;
		else
			dig_tab->rx_gain_range_max = dm->rssi_min + offset;

		/* 2 Modify DIG lower bound */
		/* if(dm->is_one_entry_only) */
		{
			if (dm->rssi_min < dm_dig_min)
				dig_dynamic_min = dm_dig_min;
			else if (dm->rssi_min > dig_max_of_min)
				dig_dynamic_min = dig_max_of_min;
			else
				dig_dynamic_min = dm->rssi_min;

			if (is_dfs_band) {
				dig_dynamic_min = dm_dig_min;
				ODM_RT_TRACE(
					dm, ODM_COMP_DIG,
					"DIG: DFS band: Force lower bound to 0x%x after link\n",
					dm_dig_min);
			}
		}
	} else {
		if (is_performance && is_dfs_band) {
			dig_tab->rx_gain_range_max = 0x28;
			ODM_RT_TRACE(
				dm, ODM_COMP_DIG,
				"DIG: DFS band: Force upper bound to 0x%x before link\n",
				dig_tab->rx_gain_range_max);
		} else {
			if (is_performance)
				dig_tab->rx_gain_range_max = DM_DIG_MAX_OF_MIN;
			else
				dig_tab->rx_gain_range_max = dm_dig_max;
		}
		dig_dynamic_min = dm_dig_min;
	}

	/* 1 Force Lower Bound for AntDiv */
	if (dm->is_linked && !dm->is_one_entry_only &&
	    (dm->support_ic_type & ODM_ANTDIV_SUPPORT) &&
	    (dm->support_ability & ODM_BB_ANT_DIV)) {
		if (dm->ant_div_type == CG_TRX_HW_ANTDIV ||
		    dm->ant_div_type == CG_TRX_SMART_ANTDIV) {
			if (dig_tab->ant_div_rssi_max > dig_max_of_min)
				dig_dynamic_min = dig_max_of_min;
			else
				dig_dynamic_min = (u8)dig_tab->ant_div_rssi_max;
			ODM_RT_TRACE(
				dm, ODM_COMP_DIG,
				"DIG: AntDiv case: Force lower bound to 0x%x\n",
				dig_dynamic_min);
			ODM_RT_TRACE(dm, ODM_COMP_DIG,
				     "DIG: AntDiv case: rssi_max = 0x%x\n",
				     dig_tab->ant_div_rssi_max);
		}
	}
	ODM_RT_TRACE(
		dm, ODM_COMP_DIG,
		"DIG: Adjust boundary by RSSI Upper bound = 0x%x, Lower bound = 0x%x\n",
		dig_tab->rx_gain_range_max, dig_dynamic_min);
	ODM_RT_TRACE(
		dm, ODM_COMP_DIG,
		"DIG: Link status: is_linked = %d, RSSI = %d, bFirstConnect = %d, bFirsrDisConnect = %d\n",
		dm->is_linked, dm->rssi_min, first_connect, first_dis_connect);

	/* 1 Modify DIG lower bound, deal with abnormal case */
	/* 2 Abnormal false alarm case */
	if (is_dfs_band) {
		dig_tab->rx_gain_range_min = dig_dynamic_min;
	} else {
		if (!dm->is_linked) {
			dig_tab->rx_gain_range_min = dig_dynamic_min;

			if (first_dis_connect)
				dig_tab->forbidden_igi = dig_dynamic_min;
		} else {
			dig_tab->rx_gain_range_min = odm_forbidden_igi_check(
				dm, dig_dynamic_min, current_igi);
		}
	}

	/* 2 Abnormal # beacon case */
	if (dm->is_linked && !first_connect) {
		ODM_RT_TRACE(dm, ODM_COMP_DIG, "Beacon Num (%d)\n",
			     dm->phy_dbg_info.num_qry_beacon_pkt);
		if (dm->phy_dbg_info.num_qry_beacon_pkt < 5 &&
		    dm->bsta_state) {
			dig_tab->rx_gain_range_min = 0x1c;
			ODM_RT_TRACE(
				dm, ODM_COMP_DIG,
				"DIG: Abnrormal #beacon (%d) case in STA mode: Force lower bound to 0x%x\n",
				dm->phy_dbg_info.num_qry_beacon_pkt,
				dig_tab->rx_gain_range_min);
		}
	}

	/* 2 Abnormal lower bound case */
	if (dig_tab->rx_gain_range_min > dig_tab->rx_gain_range_max) {
		dig_tab->rx_gain_range_min = dig_tab->rx_gain_range_max;
		ODM_RT_TRACE(
			dm, ODM_COMP_DIG,
			"DIG: Abnrormal lower bound case: Force lower bound to 0x%x\n",
			dig_tab->rx_gain_range_min);
	}

	/* 1 False alarm threshold decision */
	odm_fa_threshold_check(dm, is_dfs_band, is_performance, rx_tp, tx_tp,
			       dm_FA_thres);
	ODM_RT_TRACE(dm, ODM_COMP_DIG,
		     "DIG: False alarm threshold = %d, %d, %d\n",
		     dm_FA_thres[0], dm_FA_thres[1], dm_FA_thres[2]);

	/* 1 Adjust initial gain by false alarm */
	if (dm->is_linked && is_performance) {
		/* 2 After link */
		ODM_RT_TRACE(dm, ODM_COMP_DIG, "DIG: Adjust IGI after link\n");

		if (is_first_tp_target || (first_connect && is_performance)) {
			dig_tab->large_fa_hit = 0;

			if (is_dfs_band) {
				u8 rssi = dm->rssi_min;

				current_igi =
					(dm->rssi_min > 0x28) ? 0x28 : rssi;
				ODM_RT_TRACE(
					dm, ODM_COMP_DIG,
					"DIG: DFS band: One-shot to 0x28 upmost\n");
			} else {
				current_igi = phydm_get_current_igi(
					dig_max_of_min, dm->rssi_min,
					current_igi);
			}

			ODM_RT_TRACE(
				dm, ODM_COMP_DIG,
				"DIG: First connect case: IGI does on-shot to 0x%x\n",
				current_igi);

		} else {
			if (fa_cnt->cnt_all > dm_FA_thres[2])
				current_igi = current_igi + 4;
			else if (fa_cnt->cnt_all > dm_FA_thres[1])
				current_igi = current_igi + 2;
			else if (fa_cnt->cnt_all < dm_FA_thres[0])
				current_igi = current_igi - 2;

			/* 4 Abnormal # beacon case */
			if (dm->phy_dbg_info.num_qry_beacon_pkt < 5 &&
			    fa_cnt->cnt_all < DM_DIG_FA_TH1 &&
			    dm->bsta_state) {
				current_igi = dig_tab->rx_gain_range_min;
				ODM_RT_TRACE(
					dm, ODM_COMP_DIG,
					"DIG: Abnormal #beacon (%d) case: IGI does one-shot to 0x%x\n",
					dm->phy_dbg_info.num_qry_beacon_pkt,
					current_igi);
			}
		}
	} else {
		/* 2 Before link */
		ODM_RT_TRACE(dm, ODM_COMP_DIG, "DIG: Adjust IGI before link\n");

		if (first_dis_connect || is_first_coverage) {
			current_igi = dm_dig_min;
			ODM_RT_TRACE(
				dm, ODM_COMP_DIG,
				"DIG: First disconnect case: IGI does on-shot to lower bound\n");
		} else {
			if (fa_cnt->cnt_all > dm_FA_thres[2])
				current_igi = current_igi + 4;
			else if (fa_cnt->cnt_all > dm_FA_thres[1])
				current_igi = current_igi + 2;
			else if (fa_cnt->cnt_all < dm_FA_thres[0])
				current_igi = current_igi - 2;
		}
	}

	/* 1 Check initial gain by upper/lower bound */
	if (current_igi < dig_tab->rx_gain_range_min)
		current_igi = dig_tab->rx_gain_range_min;

	if (current_igi > dig_tab->rx_gain_range_max)
		current_igi = dig_tab->rx_gain_range_max;

	ODM_RT_TRACE(dm, ODM_COMP_DIG, "DIG: cur_ig_value=0x%x, TotalFA = %d\n",
		     current_igi, fa_cnt->cnt_all);

	/* 1 Update status */
	if (dm->is_bt_hs_operation) {
		if (dm->is_linked) {
			if (dig_tab->bt30_cur_igi > (current_igi))
				odm_write_dig(dm, current_igi);
			else
				odm_write_dig(dm, dig_tab->bt30_cur_igi);

			dig_tab->is_media_connect_0 = dm->is_linked;
			dig_tab->dig_dynamic_min_0 = dig_dynamic_min;
		} else {
			if (dm->is_link_in_process)
				odm_write_dig(dm, 0x1c);
			else if (dm->is_bt_connect_process)
				odm_write_dig(dm, 0x28);
			else
				odm_write_dig(dm, dig_tab->bt30_cur_igi);
		}
	} else { /* BT is not using */
		odm_write_dig(dm, current_igi);
		dig_tab->is_media_connect_0 = dm->is_linked;
		dig_tab->dig_dynamic_min_0 = dig_dynamic_min;
	}
	ODM_RT_TRACE(dm, ODM_COMP_DIG, "DIG end\n");
}