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
 int EN_AMPDU_RTY_NEW ; 
 int /*<<< orphan*/  REG_ACKTO ; 
 int /*<<< orphan*/  REG_FWHW_TXQ_CTRL ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

void rtl92c_init_retry_function(struct ieee80211_hw *hw)
{
	u8	value8;
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	value8 = rtl_read_byte(rtlpriv, REG_FWHW_TXQ_CTRL);
	value8 |= EN_AMPDU_RTY_NEW;
	rtl_write_byte(rtlpriv, REG_FWHW_TXQ_CTRL, value8);
	/* Set ACK timeout */
	rtl_write_byte(rtlpriv, REG_ACKTO, 0x40);
}