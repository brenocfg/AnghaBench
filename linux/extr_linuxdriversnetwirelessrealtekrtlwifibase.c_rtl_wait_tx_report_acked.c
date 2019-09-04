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
typedef  int u32 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_SEC ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ rtl_check_tx_report_acked (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void rtl_wait_tx_report_acked(struct ieee80211_hw *hw, u32 wait_ms)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	int i;

	for (i = 0; i < wait_ms; i++) {
		if (rtl_check_tx_report_acked(hw))
			break;
		usleep_range(1000, 2000);
		RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG,
			 "Wait 1ms (%d/%d) to disable key.\n", i, wait_ms);
	}
}