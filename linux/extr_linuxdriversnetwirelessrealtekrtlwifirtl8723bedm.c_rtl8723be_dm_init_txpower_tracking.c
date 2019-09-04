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
struct TYPE_2__ {int txpower_tracking; int txpower_track_control; int* ofdm_index; int cck_index; int swing_idx_cck_base; int* swing_idx_ofdm_base; scalar_t__* power_index_offset; scalar_t__* delta_power_index_last; scalar_t__* delta_power_index; scalar_t__ thermalvalue; } ;
struct rtl_priv {TYPE_1__ dm; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER_TRACKING ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 size_t RF90_PATH_A ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8723be_dm_init_txpower_tracking(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.txpower_tracking = true;
	rtlpriv->dm.txpower_track_control = true;
	rtlpriv->dm.thermalvalue = 0;

	rtlpriv->dm.ofdm_index[0] = 30;
	rtlpriv->dm.cck_index = 20;

	rtlpriv->dm.swing_idx_cck_base = rtlpriv->dm.cck_index;

	rtlpriv->dm.swing_idx_ofdm_base[0] = rtlpriv->dm.ofdm_index[0];
	rtlpriv->dm.delta_power_index[RF90_PATH_A] = 0;
	rtlpriv->dm.delta_power_index_last[RF90_PATH_A] = 0;
	rtlpriv->dm.power_index_offset[RF90_PATH_A] = 0;

	RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		 "  rtlpriv->dm.txpower_tracking = %d\n",
		  rtlpriv->dm.txpower_tracking);
}