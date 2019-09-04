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
typedef  size_t u8 ;
struct rtl_phy {int /*<<< orphan*/ ***** txpwr_limit_5g; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 size_t CHANNEL_MAX_NUMBER_5G ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 size_t MAX_5G_BANDWIDTH_NUM ; 
 int /*<<< orphan*/  MAX_POWER_INDEX ; 
 size_t MAX_RATE_SECTION_NUM ; 
 size_t MAX_REGULATION_NUM ; 
 size_t RF90_PATH_A ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8812ae_phy_cross_reference_ht_and_vht_txpower_limit(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	u8 regulation, bw, channel, rate_section;
	s8 temp_pwrlmt = 0;

	for (regulation = 0; regulation < MAX_REGULATION_NUM; ++regulation) {
		for (bw = 0; bw < MAX_5G_BANDWIDTH_NUM; ++bw) {
			for (channel = 0; channel < CHANNEL_MAX_NUMBER_5G; ++channel) {
				for (rate_section = 0; rate_section < MAX_RATE_SECTION_NUM; ++rate_section) {
					temp_pwrlmt = rtlphy->txpwr_limit_5g[regulation]
						[bw][rate_section][channel][RF90_PATH_A];
					if (temp_pwrlmt == MAX_POWER_INDEX) {
						if (bw == 0 || bw == 1) { /*5G 20M 40M VHT and HT can cross reference*/
							RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
								"No power limit table of the specified band %d, bandwidth %d, ratesection %d, channel %d, rf path %d\n",
								1, bw, rate_section, channel, RF90_PATH_A);
							if (rate_section == 2) {
								rtlphy->txpwr_limit_5g[regulation][bw][2][channel][RF90_PATH_A] =
									rtlphy->txpwr_limit_5g[regulation][bw][4][channel][RF90_PATH_A];
							} else if (rate_section == 4) {
								rtlphy->txpwr_limit_5g[regulation][bw][4][channel][RF90_PATH_A] =
									rtlphy->txpwr_limit_5g[regulation][bw][2][channel][RF90_PATH_A];
							} else if (rate_section == 3) {
								rtlphy->txpwr_limit_5g[regulation][bw][3][channel][RF90_PATH_A] =
									rtlphy->txpwr_limit_5g[regulation][bw][5][channel][RF90_PATH_A];
							} else if (rate_section == 5) {
								rtlphy->txpwr_limit_5g[regulation][bw][5][channel][RF90_PATH_A] =
									rtlphy->txpwr_limit_5g[regulation][bw][3][channel][RF90_PATH_A];
							}

							RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE, "use other value %d\n", temp_pwrlmt);
						}
					}
				}
			}
		}
	}
}