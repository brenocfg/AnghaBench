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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  RF90_PATH_A 131 
#define  RF90_PATH_B 130 
#define  RF90_PATH_C 129 
#define  RF90_PATH_D 128 
 int RTL8812AE_RADIOA_1TARRAYLEN ; 
 int /*<<< orphan*/ * RTL8812AE_RADIOA_ARRAY ; 
 int RTL8812AE_RADIOB_1TARRAYLEN ; 
 int /*<<< orphan*/ * RTL8812AE_RADIOB_ARRAY ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int __rtl8821ae_phy_config_with_headerfile (struct ieee80211_hw*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl8821ae_config_rf_radio_a ; 
 int /*<<< orphan*/  _rtl8821ae_config_rf_radio_b ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

bool rtl8812ae_phy_config_rf_with_headerfile(struct ieee80211_hw *hw,
					     enum radio_path rfpath)
{
	bool rtstatus = true;
	u32 *radioa_array_table_a, *radioa_array_table_b;
	u16 radioa_arraylen_a, radioa_arraylen_b;
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	radioa_arraylen_a = RTL8812AE_RADIOA_1TARRAYLEN;
	radioa_array_table_a = RTL8812AE_RADIOA_ARRAY;
	radioa_arraylen_b = RTL8812AE_RADIOB_1TARRAYLEN;
	radioa_array_table_b = RTL8812AE_RADIOB_ARRAY;
	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "Radio_A:RTL8821AE_RADIOA_ARRAY %d\n", radioa_arraylen_a);
	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "Radio No %x\n", rfpath);
	rtstatus = true;
	switch (rfpath) {
	case RF90_PATH_A:
		return __rtl8821ae_phy_config_with_headerfile(hw,
				radioa_array_table_a, radioa_arraylen_a,
				_rtl8821ae_config_rf_radio_a);
		break;
	case RF90_PATH_B:
		return __rtl8821ae_phy_config_with_headerfile(hw,
				radioa_array_table_b, radioa_arraylen_b,
				_rtl8821ae_config_rf_radio_b);
		break;
	case RF90_PATH_C:
	case RF90_PATH_D:
		pr_err("switch case %#x not processed\n", rfpath);
		break;
	}
	return true;
}