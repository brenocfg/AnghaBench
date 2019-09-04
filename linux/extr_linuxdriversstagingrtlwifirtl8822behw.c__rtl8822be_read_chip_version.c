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
struct rtl_phy {scalar_t__ rf_type; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  REG_SYS_CFG1_8822B ; 
 scalar_t__ RF_2T2R ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 _rtl8822be_read_chip_version(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	/*enum version_8822b version = VERSION_UNKNOWN;*/
	u32 version;
	u32 value32;

	rtlphy->rf_type = RF_2T2R;

	value32 = rtl_read_dword(rtlpriv, REG_SYS_CFG1_8822B);

	version = value32;

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "Chip RF Type: %s\n",
		 (rtlphy->rf_type == RF_2T2R) ? "RF_2T2R" : "RF_1T1R");

	return version;
}