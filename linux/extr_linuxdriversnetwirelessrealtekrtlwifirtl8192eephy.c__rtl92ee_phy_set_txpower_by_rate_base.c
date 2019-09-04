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
struct rtl_phy {scalar_t__*** txpwr_by_rate_base_24g; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAND_ON_2_4G ; 
#define  CCK 131 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  HT_MCS0_MCS7 130 
#define  HT_MCS8_MCS15 129 
#define  OFDM 128 
 scalar_t__ RF90_PATH_D ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92ee_phy_set_txpower_by_rate_base(struct ieee80211_hw *hw,
						  u8 band, u8 path,
						  u8 rate_section, u8 txnum,
						  u8 value)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;

	if (path > RF90_PATH_D) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "Invalid Rf Path %d\n", path);
		return;
	}

	if (band == BAND_ON_2_4G) {
		switch (rate_section) {
		case CCK:
			rtlphy->txpwr_by_rate_base_24g[path][txnum][0] = value;
			break;
		case OFDM:
			rtlphy->txpwr_by_rate_base_24g[path][txnum][1] = value;
			break;
		case HT_MCS0_MCS7:
			rtlphy->txpwr_by_rate_base_24g[path][txnum][2] = value;
			break;
		case HT_MCS8_MCS15:
			rtlphy->txpwr_by_rate_base_24g[path][txnum][3] = value;
			break;
		default:
			RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
				 "Invalid RateSection %d in 2.4G,Rf %d,%dTx\n",
				  rate_section, path, txnum);
			break;
		}
	} else {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "Invalid Band %d\n", band);
	}
}