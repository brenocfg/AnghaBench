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
typedef  enum version_8723e { ____Placeholder_version_8723e } version_8723e ;

/* Variables and functions */
 int CHIP_8723B ; 
 int CHIP_VENDOR_SMIC ; 
 int CHIP_VER_RTL_MASK ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int EXT_VENDOR_ID ; 
 int NORMAL_CHIP ; 
 int /*<<< orphan*/  REG_SYS_CFG ; 
 int /*<<< orphan*/  REG_SYS_CFG1 ; 
 scalar_t__ RF_1T1R ; 
 scalar_t__ RF_2T2R ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int VERSION_UNKNOWN ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum version_8723e _rtl8723be_read_chip_version(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	enum version_8723e version = VERSION_UNKNOWN;
	u32 value32;

	value32 = rtl_read_dword(rtlpriv, REG_SYS_CFG1);
	if ((value32 & (CHIP_8723B)) != CHIP_8723B)
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "unknown chip version\n");
	else
		version = (enum version_8723e)CHIP_8723B;

	rtlphy->rf_type = RF_1T1R;

	/* treat rtl8723be chip as  MP version in default */
	version = (enum version_8723e)(version | NORMAL_CHIP);

	value32 = rtl_read_dword(rtlpriv, REG_SYS_CFG);
	/* cut version */
	version |= (enum version_8723e)(value32 & CHIP_VER_RTL_MASK);
	/* Manufacture */
	if (((value32 & EXT_VENDOR_ID) >> 18) == 0x01)
		version = (enum version_8723e)(version | CHIP_VENDOR_SMIC);

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
		 "Chip RF Type: %s\n", (rtlphy->rf_type == RF_2T2R) ?
		  "RF_2T2R" : "RF_1T1R");

	return version;
}