#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int btcoexist; int ant_num; void* bt_type; } ;
struct TYPE_4__ {TYPE_1__ btc_info; } ;
struct rtl_priv {TYPE_2__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ANT_X2 ; 
 void* BT_RTL8812A ; 
 size_t EEPROM_RF_BOARD_OPTION ; 
 size_t EEPROM_RF_BT_SETTING ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8812ae_read_bt_coexist_info_from_hwpg(struct ieee80211_hw *hw,
					      bool auto_load_fail, u8 *hwinfo)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 value;

	if (!auto_load_fail) {
		value = *(u8 *)&hwinfo[EEPROM_RF_BOARD_OPTION];
		if (((value & 0xe0) >> 5) == 0x1)
			rtlpriv->btcoexist.btc_info.btcoexist = 1;
		else
			rtlpriv->btcoexist.btc_info.btcoexist = 0;
		rtlpriv->btcoexist.btc_info.bt_type = BT_RTL8812A;

		value = hwinfo[EEPROM_RF_BT_SETTING];
		rtlpriv->btcoexist.btc_info.ant_num = (value & 0x1);
	} else {
		rtlpriv->btcoexist.btc_info.btcoexist = 0;
		rtlpriv->btcoexist.btc_info.bt_type = BT_RTL8812A;
		rtlpriv->btcoexist.btc_info.ant_num = ANT_X2;
	}
	/*move BT_InitHalVars() to init_sw_vars*/
}