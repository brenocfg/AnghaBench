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
typedef  void* u8 ;
struct TYPE_8__ {int /*<<< orphan*/  conf_mutex; } ;
struct TYPE_5__ {int /*<<< orphan*/  current_bandtype; } ;
struct rtl_priv {TYPE_4__ locks; TYPE_3__* cfg; TYPE_1__ rtlhal; } ;
struct rtl_mac {int beacon_enabled; int basic_rates; void** mac_addr; void* retry_short; void* retry_long; struct ieee80211_vif* opmode; struct ieee80211_vif* vif; scalar_t__ p2p; void* link_state; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; struct ieee80211_vif* type; int /*<<< orphan*/  driver_flags; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_7__ {TYPE_2__* ops; int /*<<< orphan*/ * maps; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,void**) ;int /*<<< orphan*/  (* set_network_type ) (struct ieee80211_hw*,struct ieee80211_vif*) ;int /*<<< orphan*/  (* set_bcn_reg ) (struct ieee80211_hw*) ;int /*<<< orphan*/  (* update_interrupt_mask ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BAND_ON_2_4G ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_MAC80211 ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  DBG_WARNING ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HW_VAR_BASIC_RATE ; 
 int /*<<< orphan*/  HW_VAR_ETHER_ADDR ; 
 int /*<<< orphan*/  HW_VAR_RETRY_LIMIT ; 
 int /*<<< orphan*/  IEEE80211_VIF_BEACON_FILTER ; 
 void* MAC80211_LINKED ; 
#define  NL80211_IFTYPE_ADHOC 133 
#define  NL80211_IFTYPE_AP 132 
#define  NL80211_IFTYPE_MESH_POINT 131 
#define  NL80211_IFTYPE_P2P_CLIENT 130 
#define  NL80211_IFTYPE_P2P_GO 129 
#define  NL80211_IFTYPE_STATION 128 
 scalar_t__ P2P_ROLE_CLIENT ; 
 scalar_t__ P2P_ROLE_GO ; 
 size_t RTL_IBSS_INT_MASKS ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int ieee80211_vif_type_p2p (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  memcpy (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  rtl_ips_nic_on (struct ieee80211_hw*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (struct ieee80211_hw*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  stub11 (struct ieee80211_hw*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub3 (struct ieee80211_hw*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  stub4 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub5 (struct ieee80211_hw*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  stub6 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub7 (struct ieee80211_hw*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  stub8 (struct ieee80211_hw*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  stub9 (struct ieee80211_hw*,struct ieee80211_vif*) ; 

__attribute__((used)) static int rtl_op_add_interface(struct ieee80211_hw *hw,
		struct ieee80211_vif *vif)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	int err = 0;
	u8 retry_limit = 0x30;

	if (mac->vif) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
			 "vif has been set!! mac->vif = 0x%p\n", mac->vif);
		return -EOPNOTSUPP;
	}

	vif->driver_flags |= IEEE80211_VIF_BEACON_FILTER;

	rtl_ips_nic_on(hw);

	mutex_lock(&rtlpriv->locks.conf_mutex);
	switch (ieee80211_vif_type_p2p(vif)) {
	case NL80211_IFTYPE_P2P_CLIENT:
		mac->p2p = P2P_ROLE_CLIENT;
		/*fall through*/
	case NL80211_IFTYPE_STATION:
		if (mac->beacon_enabled == 1) {
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
				 "NL80211_IFTYPE_STATION\n");
			mac->beacon_enabled = 0;
			rtlpriv->cfg->ops->update_interrupt_mask(hw, 0,
					rtlpriv->cfg->maps[RTL_IBSS_INT_MASKS]);
		}
		break;
	case NL80211_IFTYPE_ADHOC:
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
			 "NL80211_IFTYPE_ADHOC\n");

		mac->link_state = MAC80211_LINKED;
		rtlpriv->cfg->ops->set_bcn_reg(hw);
		if (rtlpriv->rtlhal.current_bandtype == BAND_ON_2_4G)
			mac->basic_rates = 0xfff;
		else
			mac->basic_rates = 0xff0;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_BASIC_RATE,
				(u8 *)(&mac->basic_rates));

		retry_limit = 0x07;
		break;
	case NL80211_IFTYPE_P2P_GO:
		mac->p2p = P2P_ROLE_GO;
		/*fall through*/
	case NL80211_IFTYPE_AP:
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
			 "NL80211_IFTYPE_AP\n");

		mac->link_state = MAC80211_LINKED;
		rtlpriv->cfg->ops->set_bcn_reg(hw);
		if (rtlpriv->rtlhal.current_bandtype == BAND_ON_2_4G)
			mac->basic_rates = 0xfff;
		else
			mac->basic_rates = 0xff0;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_BASIC_RATE,
					      (u8 *)(&mac->basic_rates));

		retry_limit = 0x07;
		break;
	case NL80211_IFTYPE_MESH_POINT:
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
			 "NL80211_IFTYPE_MESH_POINT\n");

		mac->link_state = MAC80211_LINKED;
		rtlpriv->cfg->ops->set_bcn_reg(hw);
		if (rtlpriv->rtlhal.current_bandtype == BAND_ON_2_4G)
			mac->basic_rates = 0xfff;
		else
			mac->basic_rates = 0xff0;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_BASIC_RATE,
				(u8 *)(&mac->basic_rates));

		retry_limit = 0x07;
		break;
	default:
		pr_err("operation mode %d is not supported!\n",
		       vif->type);
		err = -EOPNOTSUPP;
		goto out;
	}

	if (mac->p2p) {
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
			 "p2p role %x\n", vif->type);
		mac->basic_rates = 0xff0;/*disable cck rate for p2p*/
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_BASIC_RATE,
				(u8 *)(&mac->basic_rates));
	}
	mac->vif = vif;
	mac->opmode = vif->type;
	rtlpriv->cfg->ops->set_network_type(hw, vif->type);
	memcpy(mac->mac_addr, vif->addr, ETH_ALEN);
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ETHER_ADDR, mac->mac_addr);

	mac->retry_long = retry_limit;
	mac->retry_short = retry_limit;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RETRY_LIMIT,
			(u8 *)(&retry_limit));
out:
	mutex_unlock(&rtlpriv->locks.conf_mutex);
	return err;
}