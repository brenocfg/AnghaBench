#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_6__ {int cnt_all; } ;
struct TYPE_4__ {int num_qry_beacon_pkt; } ;
struct TYPE_5__ {TYPE_1__ dbginfo; scalar_t__ one_entry_only; } ;
struct dig_t {int cur_igvalue; int dig_min_0; int media_connect_0; int rssi_val_min; int rx_gain_max; int large_fa_hit; int forbidden_igi; int rx_gain_min; int recover_cnt; } ;
struct rtl_priv {TYPE_3__ falsealm_cnt; TYPE_2__ dm; struct dig_t dm_digtable; } ;
struct rtl_mac {scalar_t__ link_state; scalar_t__ act_scanning; } ;
struct rtl_hal {scalar_t__ hw_type; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_DIG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int DM_DIG_FA_TH0 ; 
 int DM_DIG_FA_TH1 ; 
 int DM_DIG_FA_TH2 ; 
 int DM_DIG_MAX_AP ; 
 int DM_DIG_MIN ; 
 scalar_t__ HARDWARE_TYPE_RTL8821AE ; 
 scalar_t__ MAC80211_LINKED ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rtl8821ae_dm_write_dig (struct ieee80211_hw*,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8821ae_dm_dig(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *dm_digtable = &rtlpriv->dm_digtable;
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 dig_min_0;
	u8 dig_max_of_min;
	bool first_connect, first_disconnect;
	u8 dm_dig_max, dm_dig_min, offset;
	u8 current_igi = dm_digtable->cur_igvalue;

	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "\n");

	if (mac->act_scanning) {
		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
			 "Return: In Scan Progress\n");
		return;
	}

	/*add by Neil Chen to avoid PSD is processing*/
	dig_min_0 = dm_digtable->dig_min_0;
	first_connect = (mac->link_state >= MAC80211_LINKED) &&
			(!dm_digtable->media_connect_0);
	first_disconnect = (mac->link_state < MAC80211_LINKED) &&
			(dm_digtable->media_connect_0);

	/*1 Boundary Decision*/

	dm_dig_max = 0x5A;

	if (rtlhal->hw_type != HARDWARE_TYPE_RTL8821AE)
		dm_dig_min = DM_DIG_MIN;
	else
		dm_dig_min = 0x1C;

	dig_max_of_min = DM_DIG_MAX_AP;

	if (mac->link_state >= MAC80211_LINKED) {
		if (rtlhal->hw_type != HARDWARE_TYPE_RTL8821AE)
			offset = 20;
		else
			offset = 10;

		if ((dm_digtable->rssi_val_min + offset) > dm_dig_max)
			dm_digtable->rx_gain_max = dm_dig_max;
		else if ((dm_digtable->rssi_val_min + offset) < dm_dig_min)
			dm_digtable->rx_gain_max = dm_dig_min;
		else
			dm_digtable->rx_gain_max =
				dm_digtable->rssi_val_min + offset;

		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
			 "dm_digtable->rssi_val_min=0x%x,dm_digtable->rx_gain_max = 0x%x\n",
			 dm_digtable->rssi_val_min,
			 dm_digtable->rx_gain_max);
		if (rtlpriv->dm.one_entry_only) {
			offset = 0;

			if (dm_digtable->rssi_val_min - offset < dm_dig_min)
				dig_min_0 = dm_dig_min;
			else if (dm_digtable->rssi_val_min -
				offset > dig_max_of_min)
				dig_min_0 = dig_max_of_min;
			else
				dig_min_0 =
					dm_digtable->rssi_val_min - offset;

			RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
				 "bOneEntryOnly=TRUE, dig_min_0=0x%x\n",
				 dig_min_0);
		} else {
			dig_min_0 = dm_dig_min;
		}
	} else {
		dm_digtable->rx_gain_max = dm_dig_max;
		dig_min_0 = dm_dig_min;
		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
			 "No Link\n");
	}

	if (rtlpriv->falsealm_cnt.cnt_all > 10000) {
		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
			 "Abnormally false alarm case.\n");

		if (dm_digtable->large_fa_hit != 3)
			dm_digtable->large_fa_hit++;
		if (dm_digtable->forbidden_igi < current_igi) {
			dm_digtable->forbidden_igi = current_igi;
			dm_digtable->large_fa_hit = 1;
		}

		if (dm_digtable->large_fa_hit >= 3) {
			if ((dm_digtable->forbidden_igi + 1) >
				dm_digtable->rx_gain_max)
				dm_digtable->rx_gain_min =
					dm_digtable->rx_gain_max;
			else
				dm_digtable->rx_gain_min =
					(dm_digtable->forbidden_igi + 1);
			dm_digtable->recover_cnt = 3600;
		}
	} else {
		/*Recovery mechanism for IGI lower bound*/
		if (dm_digtable->recover_cnt != 0) {
			dm_digtable->recover_cnt--;
		} else {
			if (dm_digtable->large_fa_hit < 3) {
				if ((dm_digtable->forbidden_igi - 1) <
				    dig_min_0) {
					dm_digtable->forbidden_igi =
						dig_min_0;
					dm_digtable->rx_gain_min =
						dig_min_0;
					RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
						 "Normal Case: At Lower Bound\n");
				} else {
					dm_digtable->forbidden_igi--;
					dm_digtable->rx_gain_min =
					  (dm_digtable->forbidden_igi + 1);
					RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
						 "Normal Case: Approach Lower Bound\n");
				}
			} else {
				dm_digtable->large_fa_hit = 0;
			}
		}
	}
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
		 "pDM_DigTable->LargeFAHit=%d\n",
		 dm_digtable->large_fa_hit);

	if (rtlpriv->dm.dbginfo.num_qry_beacon_pkt < 10)
		dm_digtable->rx_gain_min = dm_dig_min;

	if (dm_digtable->rx_gain_min > dm_digtable->rx_gain_max)
		dm_digtable->rx_gain_min = dm_digtable->rx_gain_max;

	/*Adjust initial gain by false alarm*/
	if (mac->link_state >= MAC80211_LINKED) {
		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
			 "DIG AfterLink\n");
		if (first_connect) {
			if (dm_digtable->rssi_val_min <= dig_max_of_min)
				current_igi = dm_digtable->rssi_val_min;
			else
				current_igi = dig_max_of_min;
			RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
				 "First Connect\n");
		} else {
			if (rtlpriv->falsealm_cnt.cnt_all > DM_DIG_FA_TH2)
				current_igi = current_igi + 4;
			else if (rtlpriv->falsealm_cnt.cnt_all > DM_DIG_FA_TH1)
				current_igi = current_igi + 2;
			else if (rtlpriv->falsealm_cnt.cnt_all < DM_DIG_FA_TH0)
				current_igi = current_igi - 2;

			if ((rtlpriv->dm.dbginfo.num_qry_beacon_pkt < 10) &&
			    (rtlpriv->falsealm_cnt.cnt_all < DM_DIG_FA_TH1)) {
				current_igi = dm_digtable->rx_gain_min;
				RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
					 "Beacon is less than 10 and FA is less than 768, IGI GOES TO 0x1E!!!!!!!!!!!!\n");
			}
		}
	} else {
		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
			 "DIG BeforeLink\n");
		if (first_disconnect) {
			current_igi = dm_digtable->rx_gain_min;
			RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
				 "First DisConnect\n");
		} else {
			/* 2012.03.30 LukeLee: enable DIG before
			 * link but with very high thresholds
			 */
			if (rtlpriv->falsealm_cnt.cnt_all > 2000)
				current_igi = current_igi + 4;
			else if (rtlpriv->falsealm_cnt.cnt_all > 600)
				current_igi = current_igi + 2;
			else if (rtlpriv->falsealm_cnt.cnt_all < 300)
				current_igi = current_igi - 2;

			if (current_igi >= 0x3e)
				current_igi = 0x3e;

			RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "England DIG\n");
		}
	}
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
		 "DIG End Adjust IGI\n");
	/* Check initial gain by upper/lower bound*/

	if (current_igi > dm_digtable->rx_gain_max)
		current_igi = dm_digtable->rx_gain_max;
	if (current_igi < dm_digtable->rx_gain_min)
		current_igi = dm_digtable->rx_gain_min;

	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
		 "rx_gain_max=0x%x, rx_gain_min=0x%x\n",
		dm_digtable->rx_gain_max, dm_digtable->rx_gain_min);
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
		 "TotalFA=%d\n", rtlpriv->falsealm_cnt.cnt_all);
	RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD,
		 "CurIGValue=0x%x\n", current_igi);

	rtl8821ae_dm_write_dig(hw, current_igi);
	dm_digtable->media_connect_0 =
		((mac->link_state >= MAC80211_LINKED) ? true : false);
	dm_digtable->dig_min_0 = dig_min_0;
}