#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ current_bandtype; } ;
struct rtl_priv {TYPE_1__ rtlhal; } ;
struct rtl_mac {int beacon_interval; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAND_ON_5G ; 
 int /*<<< orphan*/  REG_ATIMWND ; 
 int /*<<< orphan*/  REG_BCNTCFG ; 
 int /*<<< orphan*/  REG_BCN_INTERVAL ; 
 int REG_RXTSF_OFFSET_CCK ; 
 int REG_RXTSF_OFFSET_OFDM ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

void rtl92de_set_beacon_related_registers(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 bcn_interval, atim_window;

	bcn_interval = mac->beacon_interval;
	atim_window = 2;
	/*rtl92de_disable_interrupt(hw);  */
	rtl_write_word(rtlpriv, REG_ATIMWND, atim_window);
	rtl_write_word(rtlpriv, REG_BCN_INTERVAL, bcn_interval);
	rtl_write_word(rtlpriv, REG_BCNTCFG, 0x660f);
	rtl_write_byte(rtlpriv, REG_RXTSF_OFFSET_CCK, 0x20);
	if (rtlpriv->rtlhal.current_bandtype == BAND_ON_5G)
		rtl_write_byte(rtlpriv, REG_RXTSF_OFFSET_OFDM, 0x30);
	else
		rtl_write_byte(rtlpriv, REG_RXTSF_OFFSET_OFDM, 0x20);
	rtl_write_byte(rtlpriv, 0x606, 0x30);
}