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
typedef  int u8 ;
struct rtl_priv {int dummy; } ;
struct rtl_efuse {int** txpwrlevel_cck; int** txpwrlevel_ht40_1s; int** txpwr_legacyhtdiff; int** txpwr_ht20diff; int** txpwr_ht40diff; int eeprom_regulatory; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAND_ON_2_4G ; 
 int /*<<< orphan*/  COMP_POWER_TRACKING ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int DESC92C_RATE54M ; 
 int DESC92C_RATE6M ; 
 int DESC92C_RATEMCS0 ; 
 int DESC92C_RATEMCS15 ; 
 int DESC92C_RATEMCS8 ; 
 int HT_CHANNEL_WIDTH_20 ; 
 int HT_CHANNEL_WIDTH_20_40 ; 
 int MAX_POWER_INDEX ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RX_HAL_IS_CCK_RATE (int) ; 
 size_t TX_1S ; 
 size_t TX_2S ; 
 int _rtl8723be_get_txpower_by_rate (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static u8 _rtl8723be_get_txpower_index(struct ieee80211_hw *hw, u8 path,
				       u8 rate, u8 bandwidth, u8 channel)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 index = (channel - 1);
	u8 txpower = 0;
	u8 power_diff_byrate = 0;

	if (channel > 14 || channel < 1) {
		index = 0;
		RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			 "Illegal channel!\n");
	}
	if (RX_HAL_IS_CCK_RATE(rate))
		txpower = rtlefuse->txpwrlevel_cck[path][index];
	else if (DESC92C_RATE6M <= rate)
		txpower = rtlefuse->txpwrlevel_ht40_1s[path][index];
	else
		RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			 "invalid rate\n");

	if (DESC92C_RATE6M <= rate && rate <= DESC92C_RATE54M &&
	    !RX_HAL_IS_CCK_RATE(rate))
		txpower += rtlefuse->txpwr_legacyhtdiff[0][TX_1S];

	if (bandwidth == HT_CHANNEL_WIDTH_20) {
		if (DESC92C_RATEMCS0 <= rate && rate <= DESC92C_RATEMCS15)
			txpower += rtlefuse->txpwr_ht20diff[0][TX_1S];
		if (DESC92C_RATEMCS8 <= rate && rate <= DESC92C_RATEMCS15)
			txpower += rtlefuse->txpwr_ht20diff[0][TX_2S];
	} else if (bandwidth == HT_CHANNEL_WIDTH_20_40) {
		if (DESC92C_RATEMCS0 <= rate && rate <= DESC92C_RATEMCS15)
			txpower += rtlefuse->txpwr_ht40diff[0][TX_1S];
		if (DESC92C_RATEMCS8 <= rate && rate <= DESC92C_RATEMCS15)
			txpower += rtlefuse->txpwr_ht40diff[0][TX_2S];
	}

	if (rtlefuse->eeprom_regulatory != 2)
		power_diff_byrate = _rtl8723be_get_txpower_by_rate(hw,
								   BAND_ON_2_4G,
								   path, rate);

	txpower += power_diff_byrate;

	if (txpower > MAX_POWER_INDEX)
		txpower = MAX_POWER_INDEX;

	return txpower;
}