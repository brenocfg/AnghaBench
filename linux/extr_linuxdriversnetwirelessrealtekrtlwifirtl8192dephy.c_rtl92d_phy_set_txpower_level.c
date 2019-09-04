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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ current_bandtype; } ;
struct rtl_priv {TYPE_1__ rtlhal; } ;
struct rtl_efuse {int /*<<< orphan*/  txpwr_fromeprom; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAND_ON_2_4G ; 
 int /*<<< orphan*/  _rtl92c_phy_get_rightchnlplace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl92d_ccxpower_index_check (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtl92d_get_txpower_index (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl92d_phy_rf6052_set_cck_txpower (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl92d_phy_rf6052_set_ofdm_txpower (struct ieee80211_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl92d_phy_set_txpower_level(struct ieee80211_hw *hw, u8 channel)
{
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 cckpowerlevel[2], ofdmpowerlevel[2];

	if (!rtlefuse->txpwr_fromeprom)
		return;
	channel = _rtl92c_phy_get_rightchnlplace(channel);
	_rtl92d_get_txpower_index(hw, channel, &cckpowerlevel[0],
		&ofdmpowerlevel[0]);
	if (rtlpriv->rtlhal.current_bandtype == BAND_ON_2_4G)
		_rtl92d_ccxpower_index_check(hw, channel, &cckpowerlevel[0],
				&ofdmpowerlevel[0]);
	if (rtlpriv->rtlhal.current_bandtype == BAND_ON_2_4G)
		rtl92d_phy_rf6052_set_cck_txpower(hw, &cckpowerlevel[0]);
	rtl92d_phy_rf6052_set_ofdm_txpower(hw, &ofdmpowerlevel[0], channel);
}