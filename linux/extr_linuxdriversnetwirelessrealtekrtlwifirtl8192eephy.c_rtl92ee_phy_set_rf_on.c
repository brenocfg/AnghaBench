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
 int /*<<< orphan*/  REG_SPS0_CTRL ; 
 int /*<<< orphan*/  REG_SYS_FUNC_EN ; 
 int /*<<< orphan*/  REG_TXPAUSE ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl92ee_phy_set_rf_on(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_write_byte(rtlpriv, REG_SPS0_CTRL, 0x2b);
	rtl_write_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE3);
	/*rtl_write_byte(rtlpriv, REG_APSD_CTRL, 0x00);*/
	rtl_write_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE2);
	rtl_write_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE3);
	rtl_write_byte(rtlpriv, REG_TXPAUSE, 0x00);
}