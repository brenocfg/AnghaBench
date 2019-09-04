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
struct rtl_phy {scalar_t__*** txpwr_by_rate_base_24g; scalar_t__*** txpwr_by_rate_base_5g; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAND_ON_2_4G ; 
 scalar_t__ BAND_ON_5G ; 
 scalar_t__ CCK ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ MAX_RATE_SECTION ; 
 scalar_t__ RF90_PATH_D ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static u8 _rtl8822be_phy_get_txpower_by_rate_base(struct ieee80211_hw *hw,
						  u8 band, u8 path, u8 txnum,
						  u8 rate_section)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 value;

	if (path > RF90_PATH_D) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "Invalid Rf Path %d in phy_GetTxPowerByRatBase()\n",
			 path);
		return 0;
	}

	if (band != BAND_ON_2_4G && band != BAND_ON_5G) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "Invalid band %d in phy_GetTxPowerByRatBase()\n",
			 band);
		return 0;
	}

	if (rate_section >= MAX_RATE_SECTION ||
	    (band == BAND_ON_5G && rate_section == CCK)) {
		RT_TRACE(
			rtlpriv, COMP_INIT, DBG_LOUD,
			"Invalid rate_section %d in phy_GetTxPowerByRatBase()\n",
			rate_section);
		return 0;
	}

	if (band == BAND_ON_2_4G)
		value = rtlphy->txpwr_by_rate_base_24g[path][txnum]
						      [rate_section];
	else /* BAND_ON_5G */
		value = rtlphy->txpwr_by_rate_base_5g[path][txnum]
						     [rate_section - 1];

	return value;
}