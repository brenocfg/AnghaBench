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
struct rtl_hal {int rfe_type; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 size_t EEPROM_RFE_OPTION_8822B ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl8822be_read_rfe_type(struct ieee80211_hw *hw, u8 *hwinfo,
				     bool autoload_fail)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);

	if (!autoload_fail)
		rtlhal->rfe_type = hwinfo[EEPROM_RFE_OPTION_8822B];
	else
		rtlhal->rfe_type = 0;

	if (rtlhal->rfe_type == 0xFF)
		rtlhal->rfe_type = 0;

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "RFE Type: 0x%2x\n",
		 rtlhal->rfe_type);
}