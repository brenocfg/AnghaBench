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
struct TYPE_8__ {TYPE_3__* ops; } ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct rtl_priv {TYPE_4__ phydm; TYPE_2__ halmac; struct ieee80211_hw* hw; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum radio_mask { ____Placeholder_radio_mask } radio_mask ;
struct TYPE_7__ {int (* phydm_trx_mode ) (struct rtl_priv*,int,int,int) ;int /*<<< orphan*/  (* phydm_parameter_init ) (struct rtl_priv*,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* halmac_phy_power_switch ) (struct rtl_priv*,int) ;} ;

/* Variables and functions */
 int RF_MASK_A ; 
 int RF_MASK_B ; 
 int /*<<< orphan*/  _rtl8822be_phy_init_bb_rf_register_definition (struct ieee80211_hw*) ; 
 scalar_t__ rtl8822be_phy_bb_config (struct ieee80211_hw*) ; 
 scalar_t__ rtl8822be_phy_rf_config (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  stub2 (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  stub3 (struct rtl_priv*,int) ; 
 int stub4 (struct rtl_priv*,int,int,int) ; 

bool rtl8822be_halmac_cb_init_bb_rf_register(struct rtl_priv *rtlpriv)
{
	struct ieee80211_hw *hw = rtlpriv->hw;
	enum radio_mask txpath, rxpath;
	bool tx2path;
	bool ret = false;

	_rtl8822be_phy_init_bb_rf_register_definition(hw);

	rtlpriv->halmac.ops->halmac_phy_power_switch(rtlpriv, 1);

	/* beofre bb/rf config */
	rtlpriv->phydm.ops->phydm_parameter_init(rtlpriv, 0);

	/* do bb/rf config */
	if (rtl8822be_phy_bb_config(hw) && rtl8822be_phy_rf_config(hw))
		ret = true;

	/* after bb/rf config */
	rtlpriv->phydm.ops->phydm_parameter_init(rtlpriv, 1);

	/* set trx mode (keep it to be last, r17376) */
	txpath = RF_MASK_A | RF_MASK_B;
	rxpath = RF_MASK_A | RF_MASK_B;
	tx2path = false;
	ret = rtlpriv->phydm.ops->phydm_trx_mode(rtlpriv, txpath, rxpath,
						 tx2path);

	return ret;
}