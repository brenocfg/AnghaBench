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
 int /*<<< orphan*/  REG_AGGLEN_LMT ; 
 int /*<<< orphan*/  REG_AGGR_BREAK_TIME ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int,int) ; 

void rtl92c_init_ampdu_aggregation(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_write_dword(rtlpriv, REG_AGGLEN_LMT, 0x99997631);
	rtl_write_byte(rtlpriv, REG_AGGR_BREAK_TIME, 0x16);
	/* init AMPDU aggregation number, tuning for Tx's TP, */
	rtl_write_word(rtlpriv, 0x4CA, 0x0708);
}