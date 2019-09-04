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
struct rtl_phy {int num_total_rfpath; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct rtl_hal {int /*<<< orphan*/  hw_type; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  HARDWARE_TYPE_RTL8812AE ; 
#define  RF90_PATH_A 131 
#define  RF90_PATH_B 130 
#define  RF90_PATH_C 129 
#define  RF90_PATH_D 128 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int rtl8812ae_phy_config_rf_with_headerfile (struct ieee80211_hw*,int) ; 
 int rtl8821ae_phy_config_rf_with_headerfile (struct ieee80211_hw*,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static bool _rtl8821ae_phy_rf6052_config_parafile(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 rfpath;
	bool rtstatus = true;

	for (rfpath = 0; rfpath < rtlphy->num_total_rfpath; rfpath++) {
		switch (rfpath) {
		case RF90_PATH_A: {
			if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
				rtstatus =
				  rtl8812ae_phy_config_rf_with_headerfile(hw,
							(enum radio_path)rfpath);
			else
				rtstatus =
				  rtl8821ae_phy_config_rf_with_headerfile(hw,
							(enum radio_path)rfpath);
			break;
			}
		case RF90_PATH_B:
			if (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
				rtstatus =
				  rtl8812ae_phy_config_rf_with_headerfile(hw,
							(enum radio_path)rfpath);
			else
				rtstatus =
				  rtl8821ae_phy_config_rf_with_headerfile(hw,
							(enum radio_path)rfpath);
			break;
		case RF90_PATH_C:
			break;
		case RF90_PATH_D:
			break;
		}

		if (!rtstatus) {
			RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
				 "Radio[%d] Fail!!\n", rfpath);
			return false;
		}
	}

	/*put arrays in dm.c*/
	RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE, "\n");
	return rtstatus;
}