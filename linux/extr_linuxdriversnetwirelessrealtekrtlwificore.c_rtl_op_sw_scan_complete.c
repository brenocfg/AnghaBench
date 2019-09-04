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
struct TYPE_9__ {int /*<<< orphan*/  ap_num; } ;
struct TYPE_16__ {TYPE_7__* btc_ops; TYPE_1__ btc_info; } ;
struct TYPE_12__ {int load_imrandiqk_setting_for2g; } ;
struct TYPE_11__ {scalar_t__ higher_busytraffic; } ;
struct TYPE_10__ {int /*<<< orphan*/  num; } ;
struct rtl_priv {TYPE_8__ btcoexist; TYPE_6__* cfg; TYPE_4__ rtlhal; TYPE_3__ link_info; TYPE_2__ scan_list; } ;
struct rtl_mac {int act_scanning; int skip_scan; int n_channels; int p2p_in_use; scalar_t__ link_state; scalar_t__ opmode; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* btc_scan_notify_wifi_only ) (struct rtl_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* btc_scan_notify ) (struct rtl_priv*,int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {TYPE_5__* ops; } ;
struct TYPE_13__ {scalar_t__ (* get_btc_status ) () ;int /*<<< orphan*/  (* scan_operation_backup ) (struct ieee80211_hw*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_network_type ) (struct ieee80211_hw*,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_MAC80211 ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ MAC80211_LINKED ; 
 scalar_t__ MAC80211_LINKED_SCANNING ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SCAN_OPT_RESTORE ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 () ; 
 int /*<<< orphan*/  stub4 (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct rtl_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl_op_sw_scan_complete(struct ieee80211_hw *hw,
				    struct ieee80211_vif *vif)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));

	RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD, "\n");
	mac->act_scanning = false;
	mac->skip_scan = false;

	rtlpriv->btcoexist.btc_info.ap_num = rtlpriv->scan_list.num;

	if (rtlpriv->link_info.higher_busytraffic)
		return;

	/* p2p will use 1/6/11 to scan */
	if (mac->n_channels == 3)
		mac->p2p_in_use = true;
	else
		mac->p2p_in_use = false;
	mac->n_channels = 0;
	/* Dul mac */
	rtlpriv->rtlhal.load_imrandiqk_setting_for2g = false;

	if (mac->link_state == MAC80211_LINKED_SCANNING) {
		mac->link_state = MAC80211_LINKED;
		if (mac->opmode == NL80211_IFTYPE_STATION) {
			/* fix fwlps issue */
			rtlpriv->cfg->ops->set_network_type(hw, mac->opmode);
		}
	}

	rtlpriv->cfg->ops->scan_operation_backup(hw, SCAN_OPT_RESTORE);
	if (rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->btcoexist.btc_ops->btc_scan_notify(rtlpriv, 0);
	else if (rtlpriv->btcoexist.btc_ops)
		rtlpriv->btcoexist.btc_ops->btc_scan_notify_wifi_only(rtlpriv,
								      0);
}