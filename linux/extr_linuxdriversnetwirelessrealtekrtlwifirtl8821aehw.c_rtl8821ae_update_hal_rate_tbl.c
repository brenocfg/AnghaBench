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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ useramask; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl8821ae_update_hal_rate_mask (struct ieee80211_hw*,struct ieee80211_sta*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8821ae_update_hal_rate_table (struct ieee80211_hw*,struct ieee80211_sta*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl8821ae_update_hal_rate_tbl(struct ieee80211_hw *hw,
		struct ieee80211_sta *sta, u8 rssi_level, bool update_bw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	if (rtlpriv->dm.useramask)
		rtl8821ae_update_hal_rate_mask(hw, sta, rssi_level, update_bw);
	else
		/*RT_TRACE(rtlpriv, COMP_RATR,DBG_LOUD,
			   "rtl8821ae_update_hal_rate_tbl() Error! 8821ae FW RA Only\n");*/
		rtl8821ae_update_hal_rate_table(hw, sta);
}