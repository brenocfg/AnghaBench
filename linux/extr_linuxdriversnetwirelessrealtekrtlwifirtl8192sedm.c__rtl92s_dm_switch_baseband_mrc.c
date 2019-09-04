#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_6__ {int* rx_rssi_percentage; } ;
struct TYPE_5__ {long undec_sm_pwdb; } ;
struct rtl_phy {scalar_t__ rf_type; } ;
struct rtl_priv {TYPE_4__* cfg; TYPE_2__ stats; TYPE_1__ dm; struct rtl_phy phy; } ;
struct rtl_mac {scalar_t__ link_state; scalar_t__ mode; } ;
struct rtl_hal {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_8__ {TYPE_3__* ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* get_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_MRC ; 
 scalar_t__ MAC80211_LINKED ; 
 size_t RF90_PATH_A ; 
 size_t RF90_PATH_B ; 
 scalar_t__ RF_1T1R ; 
 scalar_t__ RF_2T2R ; 
 scalar_t__ WIRELESS_MODE_B ; 
 scalar_t__ is_hal_stop (struct rtl_hal*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void _rtl92s_dm_switch_baseband_mrc(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	bool current_mrc;
	bool enable_mrc = true;
	long tmpentry_maxpwdb = 0;
	u8 rssi_a = 0;
	u8 rssi_b = 0;

	if (is_hal_stop(rtlhal))
		return;

	if ((rtlphy->rf_type == RF_1T1R) || (rtlphy->rf_type == RF_2T2R))
		return;

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_MRC, (u8 *)(&current_mrc));

	if (mac->link_state >= MAC80211_LINKED) {
		if (rtlpriv->dm.undec_sm_pwdb > tmpentry_maxpwdb) {
			rssi_a = rtlpriv->stats.rx_rssi_percentage[RF90_PATH_A];
			rssi_b = rtlpriv->stats.rx_rssi_percentage[RF90_PATH_B];
		}
	}

	/* MRC settings would NOT affect TP on Wireless B mode. */
	if (mac->mode != WIRELESS_MODE_B) {
		if ((rssi_a == 0) && (rssi_b == 0)) {
			enable_mrc = true;
		} else if (rssi_b > 30) {
			/* Turn on B-Path */
			enable_mrc = true;
		} else if (rssi_b < 5) {
			/* Turn off B-path  */
			enable_mrc = false;
		/* Take care of RSSI differentiation. */
		} else if (rssi_a > 15 && (rssi_a >= rssi_b)) {
			if ((rssi_a - rssi_b) > 15)
				/* Turn off B-path  */
				enable_mrc = false;
			else if ((rssi_a - rssi_b) < 10)
				/* Turn on B-Path */
				enable_mrc = true;
			else
				enable_mrc = current_mrc;
		} else {
			/* Turn on B-Path */
			enable_mrc = true;
		}
	}

	/* Update MRC settings if needed. */
	if (enable_mrc != current_mrc)
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_MRC,
					      (u8 *)&enable_mrc);

}