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
typedef  int /*<<< orphan*/  u16 ;
struct rtl_priv {int dummy; } ;
struct rtl_mac {int /*<<< orphan*/  beacon_interval; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_BEACON ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  REG_MBSSID_BCN_SPACE_8822B ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtl8822be_set_beacon_interval(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 bcn_interval = mac->beacon_interval;

	RT_TRACE(rtlpriv, COMP_BEACON, DBG_DMESG, "beacon_interval:%d\n",
		 bcn_interval);
	rtl_write_word(rtlpriv, REG_MBSSID_BCN_SPACE_8822B, bcn_interval);
}