#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_12__ {TYPE_5__* ops; } ;
struct TYPE_10__ {TYPE_3__* btc_ops; } ;
struct rtl_phy {int current_channel; int sw_chnl_inprogress; scalar_t__ lck_inprogress; scalar_t__ set_bwmode_inprogress; } ;
struct rtl_priv {TYPE_6__ phydm; TYPE_4__ btcoexist; TYPE_2__* cfg; struct rtl_phy phy; } ;
struct rtl_mac {int /*<<< orphan*/  act_scanning; } ;
struct rtl_hal {int /*<<< orphan*/  current_bandtype; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* phydm_clear_txpowertracking_state ) (struct rtl_priv*) ;int /*<<< orphan*/  (* phydm_switch_channel ) (struct rtl_priv*,int) ;int /*<<< orphan*/  (* phydm_switch_band ) (struct rtl_priv*,int) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* btc_switch_band_notify_wifi_only ) (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* btc_switch_band_notify ) (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_1__* ops; } ;
struct TYPE_7__ {scalar_t__ (* get_btc_status ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BAND_ON_2_4G ; 
 int /*<<< orphan*/  BAND_ON_5G ; 
 int /*<<< orphan*/  COMP_CHAN ; 
 int /*<<< orphan*/  COMP_SCAN ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 scalar_t__ RT_CANNOT_IO (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ is_hal_stop (struct rtl_hal*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  rtl8822be_phy_set_txpower_level (struct ieee80211_hw*,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  stub2 (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  stub5 (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  stub6 (struct rtl_priv*) ; 

u8 rtl8822be_phy_sw_chnl(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u32 timeout = 1000, timecount = 0;
	u8 channel = rtlphy->current_channel;

	if (rtlphy->sw_chnl_inprogress)
		return 0;
	if (rtlphy->set_bwmode_inprogress)
		return 0;

	if ((is_hal_stop(rtlhal)) || (RT_CANNOT_IO(hw))) {
		RT_TRACE(rtlpriv, COMP_CHAN, DBG_LOUD,
			 "sw_chnl_inprogress false driver sleep or unload\n");
		return 0;
	}
	while (rtlphy->lck_inprogress && timecount < timeout) {
		mdelay(50);
		timecount += 50;
	}

	if (rtlphy->current_channel > 14)
		rtlhal->current_bandtype = BAND_ON_5G;
	else if (rtlphy->current_channel <= 14)
		rtlhal->current_bandtype = BAND_ON_2_4G;

	if (rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->btcoexist.btc_ops->btc_switch_band_notify(
			rtlpriv, rtlhal->current_bandtype, mac->act_scanning);
	else
		rtlpriv->btcoexist.btc_ops->btc_switch_band_notify_wifi_only(
			rtlpriv, rtlhal->current_bandtype, mac->act_scanning);

	rtlpriv->phydm.ops->phydm_switch_band(rtlpriv, rtlphy->current_channel);

	rtlphy->sw_chnl_inprogress = true;
	if (channel == 0)
		channel = 1;

	RT_TRACE(rtlpriv, COMP_SCAN, DBG_TRACE,
		 "switch to channel%d, band type is %d\n",
		 rtlphy->current_channel, rtlhal->current_bandtype);

	rtlpriv->phydm.ops->phydm_switch_channel(rtlpriv,
						 rtlphy->current_channel);

	rtlpriv->phydm.ops->phydm_clear_txpowertracking_state(rtlpriv);

	rtl8822be_phy_set_txpower_level(hw, rtlphy->current_channel);

	RT_TRACE(rtlpriv, COMP_SCAN, DBG_TRACE, "\n");
	rtlphy->sw_chnl_inprogress = false;
	return 1;
}