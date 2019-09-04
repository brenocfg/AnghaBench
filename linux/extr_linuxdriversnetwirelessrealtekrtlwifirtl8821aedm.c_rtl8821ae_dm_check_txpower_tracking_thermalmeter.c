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
struct TYPE_2__ {int tm_trigger; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_POWER_TRACKING ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RF90_PATH_A ; 
 int /*<<< orphan*/  RF_T_METER_88E ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtl8821ae_dm_txpower_tracking_callback_thermalmeter (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_rfreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void rtl8821ae_dm_check_txpower_tracking_thermalmeter(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	if (!rtlpriv->dm.tm_trigger) {
		rtl_set_rfreg(hw, RF90_PATH_A, RF_T_METER_88E, BIT(17)|BIT(16),
			      0x03);
		RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			 "Trigger 8821ae Thermal Meter!!\n");
		rtlpriv->dm.tm_trigger = 1;
		return;
	} else {
		RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			 "Schedule TxPowerTracking !!\n");

		rtl8821ae_dm_txpower_tracking_callback_thermalmeter(hw);
		rtlpriv->dm.tm_trigger = 0;
	}
}