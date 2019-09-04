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
typedef  int u32 ;
struct TYPE_5__ {int btcoexist; int ant_num; void* single_ant_path; void* bt_type; } ;
struct TYPE_6__ {TYPE_2__ btc_info; } ;
struct rtl_priv {TYPE_3__ btcoexist; TYPE_1__* cfg; } ;
struct rtl_mod_params {int ant_sel; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {struct rtl_mod_params* mod_params; } ;

/* Variables and functions */
 void* ANT_AUX ; 
 void* ANT_MAIN ; 
 void* ANT_X1 ; 
 void* ANT_X2 ; 
 int BIT (int) ; 
 void* BT_RTL8723B ; 
 size_t EEPROM_RF_BT_SETTING_8723B ; 
 int /*<<< orphan*/  REG_MULTI_FUNC_CTRL ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 

void rtl8723be_read_bt_coexist_info_from_hwpg(struct ieee80211_hw *hw,
					      bool auto_load_fail, u8 *hwinfo)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mod_params *mod_params = rtlpriv->cfg->mod_params;
	u8 value;
	u32 tmpu_32;

	if (!auto_load_fail) {
		tmpu_32 = rtl_read_dword(rtlpriv, REG_MULTI_FUNC_CTRL);
		if (tmpu_32 & BIT(18))
			rtlpriv->btcoexist.btc_info.btcoexist = 1;
		else
			rtlpriv->btcoexist.btc_info.btcoexist = 0;
		value = hwinfo[EEPROM_RF_BT_SETTING_8723B];
		rtlpriv->btcoexist.btc_info.bt_type = BT_RTL8723B;
		rtlpriv->btcoexist.btc_info.ant_num = (value & 0x1);
		rtlpriv->btcoexist.btc_info.single_ant_path =
			 (value & 0x40 ? ANT_AUX : ANT_MAIN);	/*0xc3[6]*/
	} else {
		rtlpriv->btcoexist.btc_info.btcoexist = 0;
		rtlpriv->btcoexist.btc_info.bt_type = BT_RTL8723B;
		rtlpriv->btcoexist.btc_info.ant_num = ANT_X2;
		rtlpriv->btcoexist.btc_info.single_ant_path = ANT_MAIN;
	}

	/* override ant_num / ant_path */
	if (mod_params->ant_sel) {
		rtlpriv->btcoexist.btc_info.ant_num =
			(mod_params->ant_sel == 1 ? ANT_X1 : ANT_X2);

		rtlpriv->btcoexist.btc_info.single_ant_path =
			(mod_params->ant_sel == 1 ? ANT_AUX : ANT_MAIN);
	}
}