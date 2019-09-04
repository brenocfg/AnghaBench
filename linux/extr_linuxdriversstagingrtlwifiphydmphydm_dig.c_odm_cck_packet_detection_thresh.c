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
struct dig_thres {int cur_cck_cca_thres; int cck_fa_ma; } ;
struct phy_dm_struct {int support_ability; int rssi_min; scalar_t__ is_linked; scalar_t__ ext_lna; struct dig_thres dm_dig_table; } ;
struct false_alarm_stat {int cnt_cck_fail; } ;

/* Variables and functions */
 int DM_DIG_FA_TH0 ; 
 int DM_DIG_FA_TH1 ; 
 int ODM_BB_CCK_PD ; 
 int ODM_BB_FA_CNT ; 
 int /*<<< orphan*/  ODM_COMP_DIG ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  PHYDM_FALSEALMCNT ; 
 int /*<<< orphan*/  odm_write_cck_cca_thres (struct phy_dm_struct*,int) ; 
 scalar_t__ phydm_get_structure (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 

void odm_cck_packet_detection_thresh(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct dig_thres *dig_tab = &dm->dm_dig_table;
	struct false_alarm_stat *false_alm_cnt =
		(struct false_alarm_stat *)phydm_get_structure(
			dm, PHYDM_FALSEALMCNT);
	u8 cur_cck_cca_thres = dig_tab->cur_cck_cca_thres, rssi_thd = 35;

	if ((!(dm->support_ability & ODM_BB_CCK_PD)) ||
	    (!(dm->support_ability & ODM_BB_FA_CNT))) {
		ODM_RT_TRACE(dm, ODM_COMP_DIG, "CCK_PD: return==========\n");
		return;
	}

	if (dm->ext_lna)
		return;

	ODM_RT_TRACE(dm, ODM_COMP_DIG, "CCK_PD: ==========>\n");

	if (dig_tab->cck_fa_ma == 0xffffffff)
		dig_tab->cck_fa_ma = false_alm_cnt->cnt_cck_fail;
	else
		dig_tab->cck_fa_ma =
			((dig_tab->cck_fa_ma << 1) + dig_tab->cck_fa_ma +
			 false_alm_cnt->cnt_cck_fail) >>
			2;

	ODM_RT_TRACE(dm, ODM_COMP_DIG, "CCK_PD: CCK FA moving average = %d\n",
		     dig_tab->cck_fa_ma);

	if (dm->is_linked) {
		if (dm->rssi_min > rssi_thd) {
			cur_cck_cca_thres = 0xcd;
		} else if (dm->rssi_min > 20) {
			if (dig_tab->cck_fa_ma >
			    ((DM_DIG_FA_TH1 >> 1) + (DM_DIG_FA_TH1 >> 3)))
				cur_cck_cca_thres = 0xcd;
			else if (dig_tab->cck_fa_ma < (DM_DIG_FA_TH0 >> 1))
				cur_cck_cca_thres = 0x83;
		} else if (dm->rssi_min > 7) {
			cur_cck_cca_thres = 0x83;
		} else {
			cur_cck_cca_thres = 0x40;
		}

	} else {
		if (dig_tab->cck_fa_ma > 0x400)
			cur_cck_cca_thres = 0x83;
		else if (dig_tab->cck_fa_ma < 0x200)
			cur_cck_cca_thres = 0x40;
	}

	{
		odm_write_cck_cca_thres(dm, cur_cck_cca_thres);
	}

	ODM_RT_TRACE(dm, ODM_COMP_DIG, "CCK_PD: cck_cca_th=((0x%x))\n\n",
		     cur_cck_cca_thres);
}