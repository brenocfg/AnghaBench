#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  support_p2p_ps; } ;
struct sta_info {int sta_state; TYPE_2__ sta; TYPE_3__* sdata; int /*<<< orphan*/  _flags; int /*<<< orphan*/  assoc_at; int /*<<< orphan*/  local; } ;
typedef  enum ieee80211_sta_state { ____Placeholder_ieee80211_sta_state } ieee80211_sta_state ;
struct TYPE_9__ {int /*<<< orphan*/  type; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; TYPE_1__ vif; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IEEE80211_STA_ASSOC 131 
#define  IEEE80211_STA_AUTH 130 
#define  IEEE80211_STA_AUTHORIZED 129 
#define  IEEE80211_STA_NONE 128 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP_VLAN ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  WLAN_STA_ASSOC ; 
 int /*<<< orphan*/  WLAN_STA_AUTH ; 
 int /*<<< orphan*/  WLAN_STA_AUTHORIZED ; 
 int /*<<< orphan*/  WLAN_STA_INSERTED ; 
 int /*<<< orphan*/  cfg80211_send_layer2_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drv_sta_state (int /*<<< orphan*/ ,TYPE_3__*,struct sta_info*,int const,int) ; 
 int /*<<< orphan*/  ieee80211_check_fast_rx (struct sta_info*) ; 
 int /*<<< orphan*/  ieee80211_check_fast_xmit (struct sta_info*) ; 
 int /*<<< orphan*/  ieee80211_clear_fast_rx (struct sta_info*) ; 
 int /*<<< orphan*/  ieee80211_clear_fast_xmit (struct sta_info*) ; 
 int /*<<< orphan*/  ieee80211_recalc_min_chandef (TYPE_3__*) ; 
 int /*<<< orphan*/  ieee80211_recalc_p2p_go_ps_allowed (TYPE_3__*) ; 
 int /*<<< orphan*/  ieee80211_vif_dec_num_mcast (TYPE_3__*) ; 
 int /*<<< orphan*/  ieee80211_vif_inc_num_mcast (TYPE_3__*) ; 
 int /*<<< orphan*/  ktime_get_boottime_ns () ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sta_dbg (TYPE_3__*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

int sta_info_move_state(struct sta_info *sta,
			enum ieee80211_sta_state new_state)
{
	might_sleep();

	if (sta->sta_state == new_state)
		return 0;

	/* check allowed transitions first */

	switch (new_state) {
	case IEEE80211_STA_NONE:
		if (sta->sta_state != IEEE80211_STA_AUTH)
			return -EINVAL;
		break;
	case IEEE80211_STA_AUTH:
		if (sta->sta_state != IEEE80211_STA_NONE &&
		    sta->sta_state != IEEE80211_STA_ASSOC)
			return -EINVAL;
		break;
	case IEEE80211_STA_ASSOC:
		if (sta->sta_state != IEEE80211_STA_AUTH &&
		    sta->sta_state != IEEE80211_STA_AUTHORIZED)
			return -EINVAL;
		break;
	case IEEE80211_STA_AUTHORIZED:
		if (sta->sta_state != IEEE80211_STA_ASSOC)
			return -EINVAL;
		break;
	default:
		WARN(1, "invalid state %d", new_state);
		return -EINVAL;
	}

	sta_dbg(sta->sdata, "moving STA %pM to state %d\n",
		sta->sta.addr, new_state);

	/*
	 * notify the driver before the actual changes so it can
	 * fail the transition
	 */
	if (test_sta_flag(sta, WLAN_STA_INSERTED)) {
		int err = drv_sta_state(sta->local, sta->sdata, sta,
					sta->sta_state, new_state);
		if (err)
			return err;
	}

	/* reflect the change in all state variables */

	switch (new_state) {
	case IEEE80211_STA_NONE:
		if (sta->sta_state == IEEE80211_STA_AUTH)
			clear_bit(WLAN_STA_AUTH, &sta->_flags);
		break;
	case IEEE80211_STA_AUTH:
		if (sta->sta_state == IEEE80211_STA_NONE) {
			set_bit(WLAN_STA_AUTH, &sta->_flags);
		} else if (sta->sta_state == IEEE80211_STA_ASSOC) {
			clear_bit(WLAN_STA_ASSOC, &sta->_flags);
			ieee80211_recalc_min_chandef(sta->sdata);
			if (!sta->sta.support_p2p_ps)
				ieee80211_recalc_p2p_go_ps_allowed(sta->sdata);
		}
		break;
	case IEEE80211_STA_ASSOC:
		if (sta->sta_state == IEEE80211_STA_AUTH) {
			set_bit(WLAN_STA_ASSOC, &sta->_flags);
			sta->assoc_at = ktime_get_boottime_ns();
			ieee80211_recalc_min_chandef(sta->sdata);
			if (!sta->sta.support_p2p_ps)
				ieee80211_recalc_p2p_go_ps_allowed(sta->sdata);
		} else if (sta->sta_state == IEEE80211_STA_AUTHORIZED) {
			ieee80211_vif_dec_num_mcast(sta->sdata);
			clear_bit(WLAN_STA_AUTHORIZED, &sta->_flags);
			ieee80211_clear_fast_xmit(sta);
			ieee80211_clear_fast_rx(sta);
		}
		break;
	case IEEE80211_STA_AUTHORIZED:
		if (sta->sta_state == IEEE80211_STA_ASSOC) {
			ieee80211_vif_inc_num_mcast(sta->sdata);
			set_bit(WLAN_STA_AUTHORIZED, &sta->_flags);
			ieee80211_check_fast_xmit(sta);
			ieee80211_check_fast_rx(sta);
		}
		if (sta->sdata->vif.type == NL80211_IFTYPE_AP_VLAN ||
		    sta->sdata->vif.type == NL80211_IFTYPE_AP)
			cfg80211_send_layer2_update(sta->sdata->dev,
						    sta->sta.addr);
		break;
	default:
		break;
	}

	sta->sta_state = new_state;

	return 0;
}