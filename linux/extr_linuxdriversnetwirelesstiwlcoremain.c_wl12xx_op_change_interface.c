#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wl1271 {int /*<<< orphan*/  flags; } ;
struct ieee80211_vif {int type; int p2p; } ;
struct ieee80211_hw {struct wl1271* priv; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int /*<<< orphan*/  WL1271_FLAG_VIF_CHANGE_IN_PROGRESS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wl1271_op_add_interface (struct ieee80211_hw*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  wl1271_op_remove_interface (struct ieee80211_hw*,struct ieee80211_vif*) ; 

__attribute__((used)) static int wl12xx_op_change_interface(struct ieee80211_hw *hw,
				      struct ieee80211_vif *vif,
				      enum nl80211_iftype new_type, bool p2p)
{
	struct wl1271 *wl = hw->priv;
	int ret;

	set_bit(WL1271_FLAG_VIF_CHANGE_IN_PROGRESS, &wl->flags);
	wl1271_op_remove_interface(hw, vif);

	vif->type = new_type;
	vif->p2p = p2p;
	ret = wl1271_op_add_interface(hw, vif);

	clear_bit(WL1271_FLAG_VIF_CHANGE_IN_PROGRESS, &wl->flags);
	return ret;
}