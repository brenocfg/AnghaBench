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
typedef  int u32 ;
struct TYPE_2__ {int cnt_all; } ;
struct dig_t {int large_fa_hit; int forbidden_igi; int cur_igvalue; int rx_gain_max; int rx_gain_min; int recover_cnt; int fa_lowthresh; int back_val; int back_range_min; int back_range_max; int pre_igvalue; } ;
struct rtl_priv {TYPE_1__ falsealm_cnt; struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int DM_DIG_BACKOFF_DEFAULT ; 
 int DM_DIG_MIN ; 
 int /*<<< orphan*/  rtl92c_dm_write_dig (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int) ; 

__attribute__((used)) static void rtl92c_dm_ctrl_initgain_by_rssi(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *digtable = &rtlpriv->dm_digtable;
	u32 isbt;

	/* modify DIG lower bound, deal with abnormally large false alarm */
	if (rtlpriv->falsealm_cnt.cnt_all > 10000) {
		digtable->large_fa_hit++;
		if (digtable->forbidden_igi < digtable->cur_igvalue) {
			digtable->forbidden_igi = digtable->cur_igvalue;
			digtable->large_fa_hit = 1;
		}

		if (digtable->large_fa_hit >= 3) {
			if ((digtable->forbidden_igi + 1) >
			    digtable->rx_gain_max)
				digtable->rx_gain_min = digtable->rx_gain_max;
			else
				digtable->rx_gain_min = (digtable->forbidden_igi + 1);
			digtable->recover_cnt = 3600; /* 3600=2hr */
		}
	} else {
		/* Recovery mechanism for IGI lower bound */
		if (digtable->recover_cnt != 0) {
			digtable->recover_cnt--;
		} else {
			if (digtable->large_fa_hit == 0) {
				if ((digtable->forbidden_igi-1) < DM_DIG_MIN) {
					digtable->forbidden_igi = DM_DIG_MIN;
					digtable->rx_gain_min = DM_DIG_MIN;
				} else {
					digtable->forbidden_igi--;
					digtable->rx_gain_min = digtable->forbidden_igi + 1;
				}
			} else if (digtable->large_fa_hit == 3) {
				digtable->large_fa_hit = 0;
			}
		}
	}
	if (rtlpriv->falsealm_cnt.cnt_all < 250) {
		isbt = rtl_read_byte(rtlpriv, 0x4fd) & 0x01;

		if (!isbt) {
			if (rtlpriv->falsealm_cnt.cnt_all >
			    digtable->fa_lowthresh) {
				if ((digtable->back_val - 2) <
				   digtable->back_range_min)
					digtable->back_val = digtable->back_range_min;
				else
					digtable->back_val -= 2;
			} else if (rtlpriv->falsealm_cnt.cnt_all <
				   digtable->fa_lowthresh) {
				if ((digtable->back_val + 2) >
				    digtable->back_range_max)
					digtable->back_val = digtable->back_range_max;
				else
					digtable->back_val += 2;
			}
		} else {
			digtable->back_val = DM_DIG_BACKOFF_DEFAULT;
		}
	} else {
		/* Adjust initial gain by false alarm */
		if (rtlpriv->falsealm_cnt.cnt_all > 1000)
			digtable->cur_igvalue = digtable->pre_igvalue + 2;
		else if (rtlpriv->falsealm_cnt.cnt_all > 750)
			digtable->cur_igvalue = digtable->pre_igvalue + 1;
		else if (rtlpriv->falsealm_cnt.cnt_all < 500)
			digtable->cur_igvalue = digtable->pre_igvalue - 1;
	}

	/* Check initial gain by upper/lower bound */
	if (digtable->cur_igvalue > digtable->rx_gain_max)
		digtable->cur_igvalue = digtable->rx_gain_max;

	if (digtable->cur_igvalue < digtable->rx_gain_min)
		digtable->cur_igvalue = digtable->rx_gain_min;

	rtl92c_dm_write_dig(hw);
}