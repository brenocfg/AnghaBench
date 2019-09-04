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
typedef  scalar_t__ u32 ;
struct rtl_hal {scalar_t__ ic_class; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
 scalar_t__ IC_INFERIORITY_A ; 
 int /*<<< orphan*/  RF_IPA ; 
 scalar_t__ rtl92s_phy_query_rf_reg (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl92s_phy_set_rf_reg (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int,scalar_t__) ; 
 struct rtl_hal* rtl_hal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static bool _rtl92s_phy_config_rfpa_bias_current(struct ieee80211_hw *hw,
						 enum radio_path rfpath)
{
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool rtstatus = true;
	u32 tmpval = 0;

	/* If inferiority IC, we have to increase the PA bias current */
	if (rtlhal->ic_class != IC_INFERIORITY_A) {
		tmpval = rtl92s_phy_query_rf_reg(hw, rfpath, RF_IPA, 0xf);
		rtl92s_phy_set_rf_reg(hw, rfpath, RF_IPA, 0xf, tmpval + 1);
	}

	return rtstatus;
}