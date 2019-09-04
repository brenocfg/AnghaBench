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
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 

__attribute__((used)) static void _rtl8821ae_iqk_configure_mac(
		struct ieee80211_hw *hw
		)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	/* ========MAC register setting========*/
	rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /*[31] = 0 --> Page C*/
	rtl_write_byte(rtlpriv, 0x522, 0x3f);
	rtl_set_bbreg(hw, 0x550, BIT(11) | BIT(3), 0x0);
	rtl_write_byte(rtlpriv, 0x808, 0x00);		/*RX ante off*/
	rtl_set_bbreg(hw, 0x838, 0xf, 0xc);		/*CCA off*/
}