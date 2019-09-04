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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_DIG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int DM_DIG_FA_TH0 ; 
 int DM_DIG_FA_TH1 ; 
 int DM_DIG_FA_TH2 ; 
 int DM_DIG_MAX_AP ; 
 int DM_DIG_MIN ; 
 scalar_t__ MAC80211_LINKED ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtl92ee_dm_write_dig (struct ieee80211_hw*,int) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl92ee_dm_dig(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct dig_t *dm_dig = &rtlpriv->dm_digtable;
	u8 dig_min_0, dig_maxofmin;
	bool bfirstconnect , bfirstdisconnect;
	u8 dm_dig_max, dm_dig_min;
	u8 current_igi = dm_dig->cur_igvalue;
	u8 offset;

	/* AP,BT */
	if (mac->act_scanning)
		return;

	dig_min_0 = dm_dig->dig_min_0;
	bfirstconnect = (mac->link_state >= MAC80211_LINKED) &&
			!dm_dig->media_connect_0;
	bfirstdisconnect = (mac->link_state < MAC80211_LINKED) &&
			   dm_dig->media_connect_0;

	dm_dig_max = 0x5a;
	dm_dig_min = DM_DIG_MIN;
	dig_maxofmin = DM_DIG_MAX_AP;

	if (mac->link_state >= MAC80211_LINKED) {
		if ((dm_dig->rssi_val_min + 10) > dm_dig_max)
			dm_dig->rx_gain_max = dm_dig_max;
		else if ((dm_dig->rssi_val_min + 10) < dm_dig_min)
			dm_dig->rx_gain_max = dm_dig_min;
		else
			dm_dig->rx_gain_max = dm_dig->rssi_val_min + 10;

		if (rtlpriv->dm.one_entry_only) {
			offset = 0;
			if (dm_dig->rssi_val_min - offset < dm_dig_min)
				dig_min_0 = dm_dig_min;
			else if (dm_dig->rssi_val_min - offset >
				 dig_maxofmin)
				dig_min_0 = dig_maxofmin;
			else
				dig_min_0 = dm_dig->rssi_val_min - offset;
		} else {
			dig_min_0 = dm_dig_min;
		}

	} else {
		dm_dig->rx_gain_max = dm_dig_max;
		dig_min_0 = dm_dig_min;
		RT_TRACE(rtlpriv, COMP_DIG, DBG_LOUD, "no link\n");
	}

	if (rtlpriv->falsealm_cnt.cnt_all > 10000) {
		if (dm_dig->large_fa_hit != 3)
			dm_dig->large_fa_hit++;
		if (dm_dig->forbidden_igi < current_igi) {
			dm_dig->forbidden_igi = current_igi;
			dm_dig->large_fa_hit = 1;
		}

		if (dm_dig->large_fa_hit >= 3) {
			if (dm_dig->forbidden_igi + 1 > dm_dig->rx_gain_max)
				dm_dig->rx_gain_min =
						dm_dig->rx_gain_max;
			else
				dm_dig->rx_gain_min =
						dm_dig->forbidden_igi + 1;
			dm_dig->recover_cnt = 3600;
		}
	} else {
		if (dm_dig->recover_cnt != 0) {
			dm_dig->recover_cnt--;
		} else {
			if (dm_dig->large_fa_hit < 3) {
				if ((dm_dig->forbidden_igi - 1) <
				    dig_min_0) {
					dm_dig->forbidden_igi = dig_min_0;
					dm_dig->rx_gain_min =
								dig_min_0;
				} else {
					dm_dig->forbidden_igi--;
					dm_dig->rx_gain_min =
						dm_dig->forbidden_igi + 1;
				}
			} else {
				dm_dig->large_fa_hit = 0;
			}
		}
	}

	if (rtlpriv->dm.dbginfo.num_qry_beacon_pkt < 5)
		dm_dig->rx_gain_min = dm_dig_min;

	if (dm_dig->rx_gain_min > dm_dig->rx_gain_max)
		dm_dig->rx_gain_min = dm_dig->rx_gain_max;

	if (mac->link_state >= MAC80211_LINKED) {
		if (bfirstconnect) {
			if (dm_dig->rssi_val_min <= dig_maxofmin)
				current_igi = dm_dig->rssi_val_min;
			else
				current_igi = dig_maxofmin;

			dm_dig->large_fa_hit = 0;
		} else {
			if (rtlpriv->falsealm_cnt.cnt_all > DM_DIG_FA_TH2)
				current_igi += 4;
			else if (rtlpriv->falsealm_cnt.cnt_all > DM_DIG_FA_TH1)
				current_igi += 2;
			else if (rtlpriv->falsealm_cnt.cnt_all < DM_DIG_FA_TH0)
				current_igi -= 2;

			if (rtlpriv->dm.dbginfo.num_qry_beacon_pkt < 5 &&
			    rtlpriv->falsealm_cnt.cnt_all < DM_DIG_FA_TH1)
				current_igi = dm_dig->rx_gain_min;
		}
	} else {
		if (bfirstdisconnect) {
			current_igi = dm_dig->rx_gain_min;
		} else {
			if (rtlpriv->falsealm_cnt.cnt_all > 10000)
				current_igi += 4;
			else if (rtlpriv->falsealm_cnt.cnt_all > 8000)
				current_igi += 2;
			else if (rtlpriv->falsealm_cnt.cnt_all < 500)
				current_igi -= 2;
		}
	}

	if (current_igi > dm_dig->rx_gain_max)
		current_igi = dm_dig->rx_gain_max;
	if (current_igi < dm_dig->rx_gain_min)
		current_igi = dm_dig->rx_gain_min;

	rtl92ee_dm_write_dig(hw , current_igi);
	dm_dig->media_connect_0 = ((mac->link_state >= MAC80211_LINKED) ?
				   true : false);
	dm_dig->dig_min_0 = dig_min_0;
}