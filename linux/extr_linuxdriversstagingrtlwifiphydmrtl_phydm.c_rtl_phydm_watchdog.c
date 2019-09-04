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
struct TYPE_7__ {scalar_t__ p2p_ps_mode; } ;
struct rtl_ps_ctl {scalar_t__ rfpwr_state; int /*<<< orphan*/  rfchange_inprogress; TYPE_1__ p2p_ps_info; } ;
struct TYPE_12__ {TYPE_5__* btc_ops; } ;
struct rtl_priv {TYPE_6__ btcoexist; TYPE_4__* cfg; int /*<<< orphan*/  hw; } ;
struct rtl_mac {scalar_t__ link_state; TYPE_2__* vif; } ;
struct phy_dm_struct {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* btc_is_bt_disabled ) (struct rtl_priv*) ;} ;
struct TYPE_10__ {TYPE_3__* ops; } ;
struct TYPE_9__ {scalar_t__ (* get_btc_status ) () ;int /*<<< orphan*/  (* get_hw_reg ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_8__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ERFON ; 
 int /*<<< orphan*/  HW_VAR_FWLPS_RF_ON ; 
 int /*<<< orphan*/  HW_VAR_FW_PSMODE_STATUS ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  ODM_CMNINFO_BT_ENABLED ; 
 int /*<<< orphan*/  ODM_CMNINFO_LINK ; 
 int /*<<< orphan*/  ODM_CMNINFO_STATION_STATE ; 
 int /*<<< orphan*/  odm_cmn_info_update (struct phy_dm_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  odm_dm_watchdog (struct phy_dm_struct*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub3 () ; 
 int /*<<< orphan*/  stub4 (struct rtl_priv*) ; 

__attribute__((used)) static bool rtl_phydm_watchdog(struct rtl_priv *rtlpriv)
{
	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);
	struct rtl_mac *mac = rtl_mac(rtlpriv);
	struct rtl_ps_ctl *ppsc = rtl_psc(rtlpriv);
	bool fw_current_inpsmode = false;
	bool fw_ps_awake = true;
	u8 is_linked = false;
	u8 bsta_state = false;
	u8 is_bt_enabled = false;

	/* check whether do watchdog */
	rtlpriv->cfg->ops->get_hw_reg(rtlpriv->hw, HW_VAR_FW_PSMODE_STATUS,
				      (u8 *)(&fw_current_inpsmode));
	rtlpriv->cfg->ops->get_hw_reg(rtlpriv->hw, HW_VAR_FWLPS_RF_ON,
				      (u8 *)(&fw_ps_awake));
	if (ppsc->p2p_ps_info.p2p_ps_mode)
		fw_ps_awake = false;

	if ((ppsc->rfpwr_state == ERFON) &&
	    ((!fw_current_inpsmode) && fw_ps_awake) &&
	    (!ppsc->rfchange_inprogress))
		;
	else
		return false;

	/* update common info before doing watchdog */
	if (mac->link_state >= MAC80211_LINKED) {
		is_linked = true;
		if (mac->vif && mac->vif->type == NL80211_IFTYPE_STATION)
			bsta_state = true;
	}

	if (rtlpriv->cfg->ops->get_btc_status())
		is_bt_enabled = !rtlpriv->btcoexist.btc_ops->btc_is_bt_disabled(
			rtlpriv);

	odm_cmn_info_update(dm, ODM_CMNINFO_LINK, is_linked);
	odm_cmn_info_update(dm, ODM_CMNINFO_STATION_STATE, bsta_state);
	odm_cmn_info_update(dm, ODM_CMNINFO_BT_ENABLED, is_bt_enabled);

	/* do watchdog */
	odm_dm_watchdog(dm);

	return true;
}