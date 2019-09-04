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
typedef  int u32 ;
struct rtl_phy {scalar_t__ rf_type; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum version_8192e { ____Placeholder_version_8192e } version_8192e ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  REG_SYS_CFG1 ; 
 scalar_t__ RF_2T2R ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int TRP_VAUX_EN ; 
 scalar_t__ VERSION_NORMAL_CHIP_2T2R_8192E ; 
 scalar_t__ VERSION_TEST_CHIP_2T2R_8192E ; 
 int VERSION_UNKNOWN ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum version_8192e _rtl92ee_read_chip_version(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	enum version_8192e version = VERSION_UNKNOWN;
	u32 value32;

	rtlphy->rf_type = RF_2T2R;

	value32 = rtl_read_dword(rtlpriv, REG_SYS_CFG1);
	if (value32 & TRP_VAUX_EN)
		version = (enum version_8192e)VERSION_TEST_CHIP_2T2R_8192E;
	else
		version = (enum version_8192e)VERSION_NORMAL_CHIP_2T2R_8192E;

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "Chip RF Type: %s\n", (rtlphy->rf_type == RF_2T2R) ?
		  "RF_2T2R" : "RF_1T1R");

	return version;
}