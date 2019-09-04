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
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum version_8192d { ____Placeholder_version_8192d } version_8192d ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  REG_SYS_CFG ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int VERSION_NORMAL_CHIP_92D_SINGLEPHY ; 
 int VERSION_TEST_CHIP_92D_SINGLEPHY ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum version_8192d _rtl92de_read_chip_version(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	enum version_8192d version = VERSION_NORMAL_CHIP_92D_SINGLEPHY;
	u32 value32;

	value32 = rtl_read_dword(rtlpriv, REG_SYS_CFG);
	if (!(value32 & 0x000f0000)) {
		version = VERSION_TEST_CHIP_92D_SINGLEPHY;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "TEST CHIP!!!\n");
	} else {
		version = VERSION_NORMAL_CHIP_92D_SINGLEPHY;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "Normal CHIP!!!\n");
	}
	return version;
}