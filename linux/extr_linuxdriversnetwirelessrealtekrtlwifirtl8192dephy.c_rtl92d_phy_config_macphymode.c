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
typedef  int /*<<< orphan*/  u8 ;
struct rtl_priv {int dummy; } ;
struct rtl_hal {int macphymode; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  DUALMAC_DUALPHY 130 
#define  DUALMAC_SINGLEPHY 129 
 int /*<<< orphan*/  REG_MAC_PHY_CTRL_NORMAL ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
#define  SINGLEMAC_SINGLEPHY 128 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

void rtl92d_phy_config_macphymode(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 offset = REG_MAC_PHY_CTRL_NORMAL;

	switch (rtlhal->macphymode) {
	case DUALMAC_DUALPHY:
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "MacPhyMode: DUALMAC_DUALPHY\n");
		rtl_write_byte(rtlpriv, offset, 0xF3);
		break;
	case SINGLEMAC_SINGLEPHY:
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "MacPhyMode: SINGLEMAC_SINGLEPHY\n");
		rtl_write_byte(rtlpriv, offset, 0xF4);
		break;
	case DUALMAC_SINGLEPHY:
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "MacPhyMode: DUALMAC_SINGLEPHY\n");
		rtl_write_byte(rtlpriv, offset, 0xF1);
		break;
	}
}