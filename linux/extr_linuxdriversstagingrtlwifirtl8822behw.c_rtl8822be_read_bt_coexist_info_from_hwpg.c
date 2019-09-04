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
typedef  int u32 ;
struct TYPE_3__ {int btcoexist; void* ant_num; void* bt_type; } ;
struct TYPE_4__ {TYPE_1__ btc_info; } ;
struct rtl_priv {TYPE_2__ btcoexist; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 void* ANT_TOTAL_X1 ; 
 void* ANT_TOTAL_X2 ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int BIT_BT_FUNC_EN_8822B ; 
 void* BT_RTL8822B ; 
 size_t EEPROM_RF_BT_SETTING_8822B ; 
 int /*<<< orphan*/  REG_WL_BT_PWR_CTRL_8822B ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 

void rtl8822be_read_bt_coexist_info_from_hwpg(struct ieee80211_hw *hw,
					      bool auto_load_fail, u8 *hwinfo)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 value;
	u32 val32;

	val32 = rtl_read_dword(rtlpriv, REG_WL_BT_PWR_CTRL_8822B);
	if (val32 & BIT_BT_FUNC_EN_8822B)
		rtlpriv->btcoexist.btc_info.btcoexist = 1;
	else
		rtlpriv->btcoexist.btc_info.btcoexist = 0;

	if (!auto_load_fail) {
		value = hwinfo[EEPROM_RF_BT_SETTING_8822B];

		rtlpriv->btcoexist.btc_info.bt_type = BT_RTL8822B;
		rtlpriv->btcoexist.btc_info.ant_num =
			(value & BIT(0) ? ANT_TOTAL_X1 : ANT_TOTAL_X2);
	} else {
		rtlpriv->btcoexist.btc_info.bt_type = BT_RTL8822B;
		rtlpriv->btcoexist.btc_info.ant_num = ANT_TOTAL_X2;
	}
}