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
struct TYPE_2__ {int dynamic_txpower_enable; void* dynamic_txhighpower_lvl; void* last_dtp_lvl; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 void* TXHIGHPWRLEVEL_NORMAL ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl8723_dm_init_dynamic_txpower(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.dynamic_txpower_enable = false;

	rtlpriv->dm.last_dtp_lvl = TXHIGHPWRLEVEL_NORMAL;
	rtlpriv->dm.dynamic_txhighpower_lvl = TXHIGHPWRLEVEL_NORMAL;
}