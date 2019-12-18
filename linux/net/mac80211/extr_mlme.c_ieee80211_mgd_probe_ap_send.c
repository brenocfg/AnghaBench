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
typedef  scalar_t__ u8 ;
struct sta_info {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct ieee80211_if_managed {scalar_t__ probe_send_count; int nullfunc_failed; int flags; scalar_t__ probe_timeout; TYPE_4__* associated; } ;
struct TYPE_5__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; TYPE_3__* local; TYPE_1__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/  channel; scalar_t__* bssid; } ;
struct TYPE_7__ {int /*<<< orphan*/  hw; int /*<<< orphan*/  sta_mtx; } ;

/* Variables and functions */
 int IEEE80211_STA_DISABLE_HE ; 
 int /*<<< orphan*/  REPORTS_TX_ACK_STATUS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 scalar_t__* ieee80211_bss_get_ie (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_check_fast_rx (struct sta_info*) ; 
 scalar_t__ ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_mlme_send_probe_req (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__ const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_send_nullfunc (TYPE_3__*,struct ieee80211_sub_if_data*,int) ; 
 scalar_t__ jiffies ; 
 scalar_t__ max (int,scalar_t__) ; 
 scalar_t__ max_probe_tries ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  probe_wait_ms ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  run_again (struct ieee80211_sub_if_data*,scalar_t__) ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,scalar_t__*) ; 

__attribute__((used)) static void ieee80211_mgd_probe_ap_send(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	const u8 *ssid;
	u8 *dst = ifmgd->associated->bssid;
	u8 unicast_limit = max(1, max_probe_tries - 3);
	struct sta_info *sta;

	/*
	 * Try sending broadcast probe requests for the last three
	 * probe requests after the first ones failed since some
	 * buggy APs only support broadcast probe requests.
	 */
	if (ifmgd->probe_send_count >= unicast_limit)
		dst = NULL;

	/*
	 * When the hardware reports an accurate Tx ACK status, it's
	 * better to send a nullfunc frame instead of a probe request,
	 * as it will kick us off the AP quickly if we aren't associated
	 * anymore. The timeout will be reset if the frame is ACKed by
	 * the AP.
	 */
	ifmgd->probe_send_count++;

	if (dst) {
		mutex_lock(&sdata->local->sta_mtx);
		sta = sta_info_get(sdata, dst);
		if (!WARN_ON(!sta))
			ieee80211_check_fast_rx(sta);
		mutex_unlock(&sdata->local->sta_mtx);
	}

	if (ieee80211_hw_check(&sdata->local->hw, REPORTS_TX_ACK_STATUS)) {
		ifmgd->nullfunc_failed = false;
		if (!(ifmgd->flags & IEEE80211_STA_DISABLE_HE))
			ifmgd->probe_send_count--;
		else
			ieee80211_send_nullfunc(sdata->local, sdata, false);
	} else {
		int ssid_len;

		rcu_read_lock();
		ssid = ieee80211_bss_get_ie(ifmgd->associated, WLAN_EID_SSID);
		if (WARN_ON_ONCE(ssid == NULL))
			ssid_len = 0;
		else
			ssid_len = ssid[1];

		ieee80211_mlme_send_probe_req(sdata, sdata->vif.addr, dst,
					      ssid + 2, ssid_len,
					      ifmgd->associated->channel);
		rcu_read_unlock();
	}

	ifmgd->probe_timeout = jiffies + msecs_to_jiffies(probe_wait_ms);
	run_again(sdata, ifmgd->probe_timeout);
}