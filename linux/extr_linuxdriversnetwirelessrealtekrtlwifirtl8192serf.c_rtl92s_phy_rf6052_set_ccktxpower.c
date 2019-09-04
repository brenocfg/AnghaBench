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
struct TYPE_2__ {scalar_t__ dynamic_txhighpower_lvl; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct rtl_mac {scalar_t__ act_scanning; } ;
struct rtl_efuse {int eeprom_version; int txpwr_safetyflag; scalar_t__ eeprom_regulatory; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTX_AGCRATECCK ; 
 int RF6052_MAX_TX_PWR ; 
 int /*<<< orphan*/  RTXAGC_CCK_MCS32 ; 
 scalar_t__ TX_HIGH_PWR_LEVEL_LEVEL1 ; 
 scalar_t__ TX_HIGH_PWR_LEVEL_LEVEL2 ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void rtl92s_phy_rf6052_set_ccktxpower(struct ieee80211_hw *hw, u8 pwrlevel)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u32 txagc = 0;
	bool dont_inc_cck_or_turboscanoff = false;

	if (((rtlefuse->eeprom_version >= 2) &&
	      (rtlefuse->txpwr_safetyflag == 1)) ||
	      ((rtlefuse->eeprom_version >= 2) &&
	      (rtlefuse->eeprom_regulatory != 0)))
		dont_inc_cck_or_turboscanoff = true;

	if (mac->act_scanning) {
		txagc = 0x3f;
		if (dont_inc_cck_or_turboscanoff)
			txagc = pwrlevel;
	} else {
		txagc = pwrlevel;

		if (rtlpriv->dm.dynamic_txhighpower_lvl ==
		    TX_HIGH_PWR_LEVEL_LEVEL1)
			txagc = 0x10;
		else if (rtlpriv->dm.dynamic_txhighpower_lvl ==
			TX_HIGH_PWR_LEVEL_LEVEL2)
			txagc = 0x0;
	}

	if (txagc > RF6052_MAX_TX_PWR)
		txagc = RF6052_MAX_TX_PWR;

	rtl_set_bbreg(hw, RTXAGC_CCK_MCS32, BTX_AGCRATECCK, txagc);

}