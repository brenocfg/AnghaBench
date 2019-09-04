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
struct TYPE_2__ {scalar_t__ bt_coexist_type; scalar_t__ bt_coexistence; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BT_CSR_BC4 ; 
 int rtl92c_bt_rssi_state_change (struct ieee80211_hw*) ; 
 int rtl92c_bt_state_change (struct ieee80211_hw*) ; 
 int rtl92c_bt_wifi_connect_change (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl92c_check_bt_change (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl92c_dm_bt_coexist(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	bool wifi_connect_change;
	bool bt_state_change;
	bool rssi_state_change;

	if ((rtlpriv->btcoexist.bt_coexistence) &&
	    (rtlpriv->btcoexist.bt_coexist_type == BT_CSR_BC4)) {
		wifi_connect_change = rtl92c_bt_wifi_connect_change(hw);
		bt_state_change = rtl92c_bt_state_change(hw);
		rssi_state_change = rtl92c_bt_rssi_state_change(hw);

		if (wifi_connect_change || bt_state_change || rssi_state_change)
			rtl92c_check_bt_change(hw);
	}
}