#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct rtl_ps_ctl {scalar_t__ rfoff_reason; } ;
struct TYPE_16__ {int iqk_initialized; } ;
struct TYPE_13__ {TYPE_4__* ops; } ;
struct TYPE_11__ {TYPE_2__* ops; } ;
struct TYPE_9__ {scalar_t__ driver_is_goingto_unload; } ;
struct rtl_priv {TYPE_8__ phy; TYPE_7__* cfg; TYPE_5__ halmac; TYPE_3__ phydm; TYPE_1__ rtlhal; } ;
struct rtl_mac {int /*<<< orphan*/  link_state; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_15__ {TYPE_6__* ops; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* get_btc_status ) () ;int /*<<< orphan*/  (* led_control ) (struct ieee80211_hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  (* halmac_deinit_hal ) (struct rtl_priv*) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  (* phydm_deinit_dm ) (struct rtl_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  LED_CTL_POWER_OFF ; 
 int /*<<< orphan*/  MAC80211_NOLINK ; 
 int NL80211_IFTYPE_UNSPECIFIED ; 
 scalar_t__ RF_CHANGE_BY_PS ; 
 int /*<<< orphan*/  RT_RF_OFF_LEVL_HALT_NIC ; 
 int /*<<< orphan*/  RT_SET_PS_LEVEL (struct rtl_ps_ctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _rtl8822be_set_media_status (struct ieee80211_hw*,int) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub3 (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub4 () ; 

void rtl8822be_card_disable(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	enum nl80211_iftype opmode;

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "RTL8822be card disable\n");

	RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);

	mac->link_state = MAC80211_NOLINK;
	opmode = NL80211_IFTYPE_UNSPECIFIED;

	_rtl8822be_set_media_status(hw, opmode);

	if (rtlpriv->rtlhal.driver_is_goingto_unload ||
	    ppsc->rfoff_reason > RF_CHANGE_BY_PS)
		rtlpriv->cfg->ops->led_control(hw, LED_CTL_POWER_OFF);

	rtlpriv->phydm.ops->phydm_deinit_dm(rtlpriv);

	rtlpriv->halmac.ops->halmac_deinit_hal(rtlpriv);

	/* after power off we should do iqk again */
	if (!rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->phy.iqk_initialized = false;
}