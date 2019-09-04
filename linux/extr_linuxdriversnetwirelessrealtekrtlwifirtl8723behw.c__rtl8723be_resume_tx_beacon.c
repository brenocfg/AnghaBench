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
typedef  int u8 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ REG_FWHW_TXQ_CTRL ; 
 scalar_t__ REG_TBTT_PROHIBIT ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 

__attribute__((used)) static void _rtl8723be_resume_tx_beacon(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 tmp1byte;

	tmp1byte = rtl_read_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2);
	rtl_write_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2, tmp1byte | BIT(6));
	rtl_write_byte(rtlpriv, REG_TBTT_PROHIBIT + 1, 0xff);
	tmp1byte = rtl_read_byte(rtlpriv, REG_TBTT_PROHIBIT + 2);
	tmp1byte |= BIT(1);
	rtl_write_byte(rtlpriv, REG_TBTT_PROHIBIT + 2, tmp1byte);
}