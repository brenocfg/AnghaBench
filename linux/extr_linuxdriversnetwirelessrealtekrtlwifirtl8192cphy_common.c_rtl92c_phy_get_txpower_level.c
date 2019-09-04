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
typedef  scalar_t__ u8 ;
struct rtl_phy {scalar_t__ cur_ofdm24g_txpwridx; scalar_t__ cur_cck_txpwridx; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_efuse {scalar_t__ legacy_ht_txpowerdiff; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIRELESS_MODE_B ; 
 int /*<<< orphan*/  WIRELESS_MODE_G ; 
 int /*<<< orphan*/  WIRELESS_MODE_N_24G ; 
 long _rtl92c_phy_txpwr_idx_to_dbm (struct ieee80211_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl92c_phy_get_txpower_level(struct ieee80211_hw *hw, long *powerlevel)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 txpwr_level;
	long txpwr_dbm;

	txpwr_level = rtlphy->cur_cck_txpwridx;
	txpwr_dbm = _rtl92c_phy_txpwr_idx_to_dbm(hw, WIRELESS_MODE_B,
						 txpwr_level);
	txpwr_level = rtlphy->cur_ofdm24g_txpwridx +
	    rtlefuse->legacy_ht_txpowerdiff;
	if (_rtl92c_phy_txpwr_idx_to_dbm(hw, WIRELESS_MODE_G,
					 txpwr_level) > txpwr_dbm)
		txpwr_dbm =
		    _rtl92c_phy_txpwr_idx_to_dbm(hw, WIRELESS_MODE_G,
						 txpwr_level);
	txpwr_level = rtlphy->cur_ofdm24g_txpwridx;
	if (_rtl92c_phy_txpwr_idx_to_dbm(hw, WIRELESS_MODE_N_24G,
					 txpwr_level) > txpwr_dbm)
		txpwr_dbm =
		    _rtl92c_phy_txpwr_idx_to_dbm(hw, WIRELESS_MODE_N_24G,
						 txpwr_level);
	*powerlevel = txpwr_dbm;
}