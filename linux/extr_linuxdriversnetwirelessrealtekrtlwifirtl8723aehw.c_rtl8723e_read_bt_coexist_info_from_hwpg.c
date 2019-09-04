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
typedef  int u32 ;
struct TYPE_2__ {int eeprom_bt_coexist; int eeprom_bt_ant_num; int eeprom_bt_ant_isol; int eeprom_bt_radio_shared; void* eeprom_bt_type; } ;
struct rtl_priv {TYPE_1__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ANT_X2 ; 
 int BIT (int) ; 
 int BT_RADIO_SHARED ; 
 void* BT_RTL8723A ; 
 int /*<<< orphan*/  REG_MULTI_FUNC_CTRL ; 
 size_t RF_OPTION4 ; 
 int /*<<< orphan*/  rtl8723e_bt_var_init (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 

void rtl8723e_read_bt_coexist_info_from_hwpg(struct ieee80211_hw *hw,
					     bool auto_load_fail, u8 *hwinfo)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 value;
	u32 tmpu_32;

	if (!auto_load_fail) {
		tmpu_32 = rtl_read_dword(rtlpriv, REG_MULTI_FUNC_CTRL);
		if (tmpu_32 & BIT(18))
			rtlpriv->btcoexist.eeprom_bt_coexist = 1;
		else
			rtlpriv->btcoexist.eeprom_bt_coexist = 0;
		value = hwinfo[RF_OPTION4];
		rtlpriv->btcoexist.eeprom_bt_type = BT_RTL8723A;
		rtlpriv->btcoexist.eeprom_bt_ant_num = (value & 0x1);
		rtlpriv->btcoexist.eeprom_bt_ant_isol = ((value & 0x10) >> 4);
		rtlpriv->btcoexist.eeprom_bt_radio_shared =
		  ((value & 0x20) >> 5);
	} else {
		rtlpriv->btcoexist.eeprom_bt_coexist = 0;
		rtlpriv->btcoexist.eeprom_bt_type = BT_RTL8723A;
		rtlpriv->btcoexist.eeprom_bt_ant_num = ANT_X2;
		rtlpriv->btcoexist.eeprom_bt_ant_isol = 0;
		rtlpriv->btcoexist.eeprom_bt_radio_shared = BT_RADIO_SHARED;
	}

	rtl8723e_bt_var_init(hw);
}