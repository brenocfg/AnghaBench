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
 scalar_t__ RQPN ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,scalar_t__,int) ; 

__attribute__((used)) static void _rtl92s_fw_set_rqpn(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_write_dword(rtlpriv, RQPN, 0xffffffff);
	rtl_write_dword(rtlpriv, RQPN + 4, 0xffffffff);
	rtl_write_byte(rtlpriv, RQPN + 8, 0xff);
	rtl_write_byte(rtlpriv, RQPN + 0xB, 0x80);
}