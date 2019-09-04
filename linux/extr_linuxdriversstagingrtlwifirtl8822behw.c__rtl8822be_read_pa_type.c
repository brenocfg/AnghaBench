#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* u8 ;
struct rtl_priv {int dummy; } ;
struct rtl_hal {int pa_type_2g; int lna_type_2g; int external_pa_2g; int external_lna_2g; int pa_type_5g; int lna_type_5g; int external_pa_5g; int external_lna_5g; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 size_t EEPROM_2G_5G_PA_TYPE_8822B ; 
 size_t EEPROM_2G_LNA_TYPE_GAIN_SEL_AB_8822B ; 
 size_t EEPROM_5G_LNA_TYPE_GAIN_SEL_AB_8822B ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8822be_read_pa_type(struct ieee80211_hw *hw, u8 *hwinfo,
				    bool autoload_fail)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);

	if (!autoload_fail) {
		rtlhal->pa_type_2g = hwinfo[EEPROM_2G_5G_PA_TYPE_8822B];
		rtlhal->lna_type_2g =
			hwinfo[EEPROM_2G_LNA_TYPE_GAIN_SEL_AB_8822B];
		if (rtlhal->pa_type_2g == 0xFF)
			rtlhal->pa_type_2g = 0;
		if (rtlhal->lna_type_2g == 0xFF)
			rtlhal->lna_type_2g = 0;

		rtlhal->external_pa_2g = (rtlhal->pa_type_2g & BIT(4)) ? 1 : 0;
		rtlhal->external_lna_2g =
			(rtlhal->lna_type_2g & BIT(3)) ? 1 : 0;

		rtlhal->pa_type_5g = hwinfo[EEPROM_2G_5G_PA_TYPE_8822B];
		rtlhal->lna_type_5g =
			hwinfo[EEPROM_5G_LNA_TYPE_GAIN_SEL_AB_8822B];
		if (rtlhal->pa_type_5g == 0xFF)
			rtlhal->pa_type_5g = 0;
		if (rtlhal->lna_type_5g == 0xFF)
			rtlhal->lna_type_5g = 0;

		rtlhal->external_pa_5g = (rtlhal->pa_type_5g & BIT(0)) ? 1 : 0;
		rtlhal->external_lna_5g =
			(rtlhal->lna_type_5g & BIT(3)) ? 1 : 0;
	} else {
		rtlhal->external_pa_2g = 0;
		rtlhal->external_lna_2g = 0;
		rtlhal->external_pa_5g = 0;
		rtlhal->external_lna_5g = 0;
	}
}