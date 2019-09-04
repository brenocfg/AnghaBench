#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_8__ {TYPE_3__* ops; } ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct rtl_phy {int set_bwmode_inprogress; int /*<<< orphan*/  current_chan_bw; int /*<<< orphan*/  current_channel; } ;
struct rtl_priv {TYPE_4__ phydm; TYPE_2__ halmac; struct rtl_phy phy; } ;
struct rtl_mac {int /*<<< orphan*/  act_scanning; } ;
struct rtl_hal {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum nl80211_channel_type { ____Placeholder_nl80211_channel_type } nl80211_channel_type ;
struct TYPE_7__ {int /*<<< orphan*/  (* phydm_iq_calibrate ) (struct rtl_priv*) ;int /*<<< orphan*/  (* phydm_switch_bandwidth ) (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* halmac_set_bandwidth ) (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  DBG_WARNING ; 
 int /*<<< orphan*/  RT_CANNOT_IO (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _rtl8822be_phy_get_pri_ch_id (struct rtl_priv*) ; 
 int /*<<< orphan*/  is_hal_stop (struct rtl_hal*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct rtl_priv*) ; 

void rtl8822be_phy_set_bw_mode(struct ieee80211_hw *hw,
			       enum nl80211_channel_type ch_type)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &rtlpriv->phy;
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u8 tmp_bw = rtlphy->current_chan_bw;

	if (rtlphy->set_bwmode_inprogress)
		return;
	rtlphy->set_bwmode_inprogress = true;
	if ((!is_hal_stop(rtlhal)) && !(RT_CANNOT_IO(hw))) {
		/* get primary channel index */
		u8 pri_ch_idx = _rtl8822be_phy_get_pri_ch_id(rtlpriv);

		/* 3.1 set MAC register */
		rtlpriv->halmac.ops->halmac_set_bandwidth(
			rtlpriv, rtlphy->current_channel, pri_ch_idx,
			rtlphy->current_chan_bw);

		/* 3.2 set BB/RF registet */
		rtlpriv->phydm.ops->phydm_switch_bandwidth(
			rtlpriv, pri_ch_idx, rtlphy->current_chan_bw);

		if (!mac->act_scanning)
			rtlpriv->phydm.ops->phydm_iq_calibrate(rtlpriv);

		rtlphy->set_bwmode_inprogress = false;
	} else {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
			 "FALSE driver sleep or unload\n");
		rtlphy->set_bwmode_inprogress = false;
		rtlphy->current_chan_bw = tmp_bw;
	}
}