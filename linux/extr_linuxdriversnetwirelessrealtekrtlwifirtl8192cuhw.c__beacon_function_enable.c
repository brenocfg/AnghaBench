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
 scalar_t__ REG_RD_CTRL ; 
 int /*<<< orphan*/  _rtl92cu_set_bcn_ctrl_reg (struct ieee80211_hw*,int,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 

__attribute__((used)) static void _beacon_function_enable(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	_rtl92cu_set_bcn_ctrl_reg(hw, (BIT(4) | BIT(3) | BIT(1)), 0x00);
	rtl_write_byte(rtlpriv, REG_RD_CTRL+1, 0x6F);
}