#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct rtl_priv {TYPE_2__* cfg; } ;
struct rtl_mac {int rx_conf; scalar_t__ link_state; scalar_t__ opmode; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {int* maps; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_hw_reg ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_chk_bssid ) (struct ieee80211_hw*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_MAC80211 ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 unsigned int FIF_ALLMULTI ; 
 unsigned int FIF_BCN_PRBRESP_PROMISC ; 
 unsigned int FIF_CONTROL ; 
 unsigned int FIF_FCSFAIL ; 
 unsigned int FIF_OTHER_BSS ; 
 int /*<<< orphan*/  HW_VAR_RCR ; 
 scalar_t__ MAC80211_LINKED ; 
 size_t MAC_RCR_AAP ; 
 size_t MAC_RCR_AB ; 
 size_t MAC_RCR_ACF ; 
 size_t MAC_RCR_ACRC32 ; 
 size_t MAC_RCR_AM ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 unsigned int RTL_SUPPORTED_FILTERS ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  stub3 (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl_op_configure_filter(struct ieee80211_hw *hw,
				    unsigned int changed_flags,
				    unsigned int *new_flags, u64 multicast)
{
	bool update_rcr = false;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));

	*new_flags &= RTL_SUPPORTED_FILTERS;
	if (0 == changed_flags)
		return;

	/*TODO: we disable broadcase now, so enable here */
	if (changed_flags & FIF_ALLMULTI) {
		if (*new_flags & FIF_ALLMULTI) {
			mac->rx_conf |= rtlpriv->cfg->maps[MAC_RCR_AM] |
			    rtlpriv->cfg->maps[MAC_RCR_AB];
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
				 "Enable receive multicast frame\n");
		} else {
			mac->rx_conf &= ~(rtlpriv->cfg->maps[MAC_RCR_AM] |
					  rtlpriv->cfg->maps[MAC_RCR_AB]);
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
				 "Disable receive multicast frame\n");
		}
		update_rcr = true;
	}

	if (changed_flags & FIF_FCSFAIL) {
		if (*new_flags & FIF_FCSFAIL) {
			mac->rx_conf |= rtlpriv->cfg->maps[MAC_RCR_ACRC32];
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
				 "Enable receive FCS error frame\n");
		} else {
			mac->rx_conf &= ~rtlpriv->cfg->maps[MAC_RCR_ACRC32];
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
				 "Disable receive FCS error frame\n");
		}
		if (!update_rcr)
			update_rcr = true;
	}

	/* if ssid not set to hw don't check bssid
	 * here just used for linked scanning, & linked
	 * and nolink check bssid is set in set network_type
	 */
	if (changed_flags & FIF_BCN_PRBRESP_PROMISC &&
	    mac->link_state >= MAC80211_LINKED) {
		if (mac->opmode != NL80211_IFTYPE_AP &&
		    mac->opmode != NL80211_IFTYPE_MESH_POINT) {
			if (*new_flags & FIF_BCN_PRBRESP_PROMISC)
				rtlpriv->cfg->ops->set_chk_bssid(hw, false);
			else
				rtlpriv->cfg->ops->set_chk_bssid(hw, true);
			if (update_rcr)
				update_rcr = false;
		}
	}

	if (changed_flags & FIF_CONTROL) {
		if (*new_flags & FIF_CONTROL) {
			mac->rx_conf |= rtlpriv->cfg->maps[MAC_RCR_ACF];

			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
				 "Enable receive control frame.\n");
		} else {
			mac->rx_conf &= ~rtlpriv->cfg->maps[MAC_RCR_ACF];
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
				 "Disable receive control frame.\n");
		}
		if (!update_rcr)
			update_rcr = true;
	}

	if (changed_flags & FIF_OTHER_BSS) {
		if (*new_flags & FIF_OTHER_BSS) {
			mac->rx_conf |= rtlpriv->cfg->maps[MAC_RCR_AAP];
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
				 "Enable receive other BSS's frame.\n");
		} else {
			mac->rx_conf &= ~rtlpriv->cfg->maps[MAC_RCR_AAP];
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
				 "Disable receive other BSS's frame.\n");
		}
		if (!update_rcr)
			update_rcr = true;
	}

	if (update_rcr)
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RCR,
					      (u8 *)(&mac->rx_conf));
}