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
struct rtl_sta_info {int /*<<< orphan*/  list; scalar_t__ ratr_index; scalar_t__ wireless_mode; } ;
struct TYPE_6__ {int /*<<< orphan*/  entry_list_lock; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct rtl_priv {TYPE_3__ locks; TYPE_2__ phydm; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {scalar_t__ drv_priv; int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* phydm_del_sta ) (struct rtl_priv*,struct ieee80211_sta*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_MAC80211 ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rtl_priv*,struct ieee80211_sta*) ; 

__attribute__((used)) static int rtl_op_sta_remove(struct ieee80211_hw *hw,
			     struct ieee80211_vif *vif,
			     struct ieee80211_sta *sta)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_sta_info *sta_entry;

	if (sta) {
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG,
			 "Remove sta addr is %pM\n", sta->addr);

		if (rtlpriv->phydm.ops)
			rtlpriv->phydm.ops->phydm_del_sta(rtlpriv, sta);

		sta_entry = (struct rtl_sta_info *)sta->drv_priv;
		sta_entry->wireless_mode = 0;
		sta_entry->ratr_index = 0;
		spin_lock_bh(&rtlpriv->locks.entry_list_lock);
		list_del(&sta_entry->list);
		spin_unlock_bh(&rtlpriv->locks.entry_list_lock);
	}
	return 0;
}