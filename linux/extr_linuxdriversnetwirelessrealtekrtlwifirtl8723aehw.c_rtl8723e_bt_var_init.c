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
struct TYPE_2__ {scalar_t__ bt_ant_num; scalar_t__ eeprom_bt_ant_num; int bt_coexist_type; int eeprom_bt_type; int bt_busy_traffic; int bt_traffic_mode_set; int bt_non_traffic_mode_set; int cur_bt_disabled; int pre_bt_disabled; scalar_t__ bt_active_zero_cnt; scalar_t__ bt_radio_shared_type; scalar_t__ bt_ant_isolation; scalar_t__ previous_state; scalar_t__ cstate; scalar_t__ bt_coexistence; scalar_t__ eeprom_bt_radio_shared; scalar_t__ eeprom_bt_ant_isol; scalar_t__ eeprom_bt_coexist; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ ANT_X1 ; 
 scalar_t__ ANT_X2 ; 
#define  BT_2WIRE 133 
#define  BT_ACCEL 132 
#define  BT_CSR_BC4 131 
#define  BT_CSR_BC8 130 
#define  BT_ISSC_3WIRE 129 
#define  BT_RTL8756 128 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8723e_bt_var_init(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->btcoexist.bt_coexistence =
		rtlpriv->btcoexist.eeprom_bt_coexist;
	rtlpriv->btcoexist.bt_ant_num =
		rtlpriv->btcoexist.eeprom_bt_ant_num;
	rtlpriv->btcoexist.bt_coexist_type =
		rtlpriv->btcoexist.eeprom_bt_type;

	rtlpriv->btcoexist.bt_ant_isolation =
		rtlpriv->btcoexist.eeprom_bt_ant_isol;

	rtlpriv->btcoexist.bt_radio_shared_type =
		rtlpriv->btcoexist.eeprom_bt_radio_shared;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		 "BT Coexistence = 0x%x\n",
		 rtlpriv->btcoexist.bt_coexistence);

	if (rtlpriv->btcoexist.bt_coexistence) {
		rtlpriv->btcoexist.bt_busy_traffic = false;
		rtlpriv->btcoexist.bt_traffic_mode_set = false;
		rtlpriv->btcoexist.bt_non_traffic_mode_set = false;

		rtlpriv->btcoexist.cstate = 0;
		rtlpriv->btcoexist.previous_state = 0;

		if (rtlpriv->btcoexist.bt_ant_num == ANT_X2) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				 "BlueTooth BT_Ant_Num = Antx2\n");
		} else if (rtlpriv->btcoexist.bt_ant_num == ANT_X1) {
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				 "BlueTooth BT_Ant_Num = Antx1\n");
		}
		switch (rtlpriv->btcoexist.bt_coexist_type) {
		case BT_2WIRE:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				 "BlueTooth BT_CoexistType = BT_2Wire\n");
			break;
		case BT_ISSC_3WIRE:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				 "BlueTooth BT_CoexistType = BT_ISSC_3Wire\n");
			break;
		case BT_ACCEL:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				 "BlueTooth BT_CoexistType = BT_ACCEL\n");
			break;
		case BT_CSR_BC4:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				 "BlueTooth BT_CoexistType = BT_CSR_BC4\n");
			break;
		case BT_CSR_BC8:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				 "BlueTooth BT_CoexistType = BT_CSR_BC8\n");
			break;
		case BT_RTL8756:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				 "BlueTooth BT_CoexistType = BT_RTL8756\n");
			break;
		default:
			RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				 "BlueTooth BT_CoexistType = Unknown\n");
			break;
		}
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			 "BlueTooth BT_Ant_isolation = %d\n",
			 rtlpriv->btcoexist.bt_ant_isolation);
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			 "BT_RadioSharedType = 0x%x\n",
			 rtlpriv->btcoexist.bt_radio_shared_type);
		rtlpriv->btcoexist.bt_active_zero_cnt = 0;
		rtlpriv->btcoexist.cur_bt_disabled = false;
		rtlpriv->btcoexist.pre_bt_disabled = false;
	}
}