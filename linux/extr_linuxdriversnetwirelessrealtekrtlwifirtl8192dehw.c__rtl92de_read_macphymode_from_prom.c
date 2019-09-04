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
struct rtl_hal {int /*<<< orphan*/  macphymode; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DUALMAC_DUALPHY ; 
 size_t EEPROM_MAC_FUNCTION ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SINGLEMAC_SINGLEPHY ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92de_read_macphymode_from_prom(struct ieee80211_hw *hw,
					       u8 *content)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 macphy_crvalue = content[EEPROM_MAC_FUNCTION];

	if (macphy_crvalue & BIT(3)) {
		rtlhal->macphymode = SINGLEMAC_SINGLEPHY;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "MacPhyMode SINGLEMAC_SINGLEPHY\n");
	} else {
		rtlhal->macphymode = DUALMAC_DUALPHY;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "MacPhyMode DUALMAC_DUALPHY\n");
	}
}