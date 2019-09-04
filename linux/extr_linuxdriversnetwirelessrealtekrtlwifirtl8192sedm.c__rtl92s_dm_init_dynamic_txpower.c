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
struct TYPE_2__ {scalar_t__ dm_type; int dynamic_txpower_enable; void* dynamic_txhighpower_lvl; void* last_dtp_lvl; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ DM_TYPE_BYDRIVER ; 
 void* TX_HIGHPWR_LEVEL_NORMAL ; 
 int hal_get_firmwareversion (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl92s_dm_init_dynamic_txpower(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if ((hal_get_firmwareversion(rtlpriv) >= 60) &&
	    (rtlpriv->dm.dm_type == DM_TYPE_BYDRIVER))
		rtlpriv->dm.dynamic_txpower_enable = true;
	else
		rtlpriv->dm.dynamic_txpower_enable = false;

	rtlpriv->dm.last_dtp_lvl = TX_HIGHPWR_LEVEL_NORMAL;
	rtlpriv->dm.dynamic_txhighpower_lvl = TX_HIGHPWR_LEVEL_NORMAL;
}