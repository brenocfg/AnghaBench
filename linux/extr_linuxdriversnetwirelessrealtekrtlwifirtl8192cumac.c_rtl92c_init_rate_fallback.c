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
 scalar_t__ REG_DARFRC ; 
 scalar_t__ REG_RARFRC ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,scalar_t__,int) ; 

void rtl92c_init_rate_fallback(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	/* Set Data Auto Rate Fallback Retry Count register. */
	rtl_write_dword(rtlpriv,  REG_DARFRC, 0x00000000);
	rtl_write_dword(rtlpriv,  REG_DARFRC+4, 0x10080404);
	rtl_write_dword(rtlpriv,  REG_RARFRC, 0x04030201);
	rtl_write_dword(rtlpriv,  REG_RARFRC+4, 0x08070605);
}