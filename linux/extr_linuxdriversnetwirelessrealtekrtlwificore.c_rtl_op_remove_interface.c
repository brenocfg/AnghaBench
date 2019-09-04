#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  conf_mutex; } ;
struct rtl_priv {TYPE_3__ locks; TYPE_2__* cfg; } ;
struct rtl_mac {int beacon_enabled; int /*<<< orphan*/  opmode; int /*<<< orphan*/  vendor; int /*<<< orphan*/  bssid; int /*<<< orphan*/  link_state; int /*<<< orphan*/ * vif; scalar_t__ p2p; } ;
struct ieee80211_vif {scalar_t__ type; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_5__ {TYPE_1__* ops; int /*<<< orphan*/ * maps; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_network_type ) (struct ieee80211_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* update_interrupt_mask ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MAC80211_NOLINK ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_UNSPECIFIED ; 
 int /*<<< orphan*/  PEER_UNKNOWN ; 
 size_t RTL_IBSS_INT_MASKS ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl_op_remove_interface(struct ieee80211_hw *hw,
		struct ieee80211_vif *vif)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));

	mutex_lock(&rtlpriv->locks.conf_mutex);

	/* Free beacon resources */
	if (vif->type == NL80211_IFTYPE_AP ||
	    vif->type == NL80211_IFTYPE_ADHOC ||
	    vif->type == NL80211_IFTYPE_MESH_POINT) {
		if (mac->beacon_enabled == 1) {
			mac->beacon_enabled = 0;
			rtlpriv->cfg->ops->update_interrupt_mask(hw, 0,
					rtlpriv->cfg->maps[RTL_IBSS_INT_MASKS]);
		}
	}

	/*
	 *Note: We assume NL80211_IFTYPE_UNSPECIFIED as
	 *NO LINK for our hardware.
	 */
	mac->p2p = 0;
	mac->vif = NULL;
	mac->link_state = MAC80211_NOLINK;
	eth_zero_addr(mac->bssid);
	mac->vendor = PEER_UNKNOWN;
	mac->opmode = NL80211_IFTYPE_UNSPECIFIED;
	rtlpriv->cfg->ops->set_network_type(hw, mac->opmode);

	mutex_unlock(&rtlpriv->locks.conf_mutex);
}