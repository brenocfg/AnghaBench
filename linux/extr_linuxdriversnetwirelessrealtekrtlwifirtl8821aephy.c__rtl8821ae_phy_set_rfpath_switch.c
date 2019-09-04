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
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ RA_RFE_PINMUX ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,scalar_t__,int,int) ; 

__attribute__((used)) static void _rtl8821ae_phy_set_rfpath_switch(struct ieee80211_hw *hw, bool main)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	/* struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw)); */
	/* struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw)); */
	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "\n");

	if (main)
		rtl_set_bbreg(hw, RA_RFE_PINMUX + 4, BIT(29) | BIT(28), 0x1);
	else
		rtl_set_bbreg(hw, RA_RFE_PINMUX + 4, BIT(29) | BIT(28), 0x2);
}