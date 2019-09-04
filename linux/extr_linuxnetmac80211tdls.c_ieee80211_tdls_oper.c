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
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int flags; } ;
struct sta_info {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  request_smps_work; int /*<<< orphan*/  tdls_peer; int /*<<< orphan*/  tdls_peer_del_work; } ;
struct TYPE_6__ {TYPE_2__ mgd; } ;
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  csa_active; } ;
struct ieee80211_sub_if_data {TYPE_3__ u; struct ieee80211_local* local; TYPE_1__ vif; } ;
struct ieee80211_local {int /*<<< orphan*/  mtx; int /*<<< orphan*/  hw; int /*<<< orphan*/  sta_mtx; int /*<<< orphan*/  tx_pending_tasklet; } ;
typedef  enum nl80211_tdls_operation { ____Placeholder_nl80211_tdls_operation } nl80211_tdls_operation ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOLINK ; 
 int ENOTSUPP ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
#define  NL80211_TDLS_DISABLE_LINK 132 
#define  NL80211_TDLS_DISCOVERY_REQ 131 
#define  NL80211_TDLS_ENABLE_LINK 130 
#define  NL80211_TDLS_SETUP 129 
#define  NL80211_TDLS_TEARDOWN 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int WIPHY_FLAG_SUPPORTS_TDLS ; 
 int /*<<< orphan*/  WLAN_STA_TDLS_PEER_AUTH ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  iee80211_tdls_recalc_chanctx (struct ieee80211_sub_if_data*,struct sta_info*) ; 
 int /*<<< orphan*/  iee80211_tdls_recalc_ht_protection (struct ieee80211_sub_if_data*,struct sta_info*) ; 
 int /*<<< orphan*/  ieee80211_flush_queues (struct ieee80211_local*,struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdata_lock (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  sdata_unlock (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  set_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int sta_info_destroy_addr (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*) ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdls_dbg (struct ieee80211_sub_if_data*,char*,...) ; 

int ieee80211_tdls_oper(struct wiphy *wiphy, struct net_device *dev,
			const u8 *peer, enum nl80211_tdls_operation oper)
{
	struct sta_info *sta;
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_local *local = sdata->local;
	int ret;

	if (!(wiphy->flags & WIPHY_FLAG_SUPPORTS_TDLS))
		return -ENOTSUPP;

	if (sdata->vif.type != NL80211_IFTYPE_STATION)
		return -EINVAL;

	switch (oper) {
	case NL80211_TDLS_ENABLE_LINK:
	case NL80211_TDLS_DISABLE_LINK:
		break;
	case NL80211_TDLS_TEARDOWN:
	case NL80211_TDLS_SETUP:
	case NL80211_TDLS_DISCOVERY_REQ:
		/* We don't support in-driver setup/teardown/discovery */
		return -ENOTSUPP;
	}

	/* protect possible bss_conf changes and avoid concurrency in
	 * ieee80211_bss_info_change_notify()
	 */
	sdata_lock(sdata);
	mutex_lock(&local->mtx);
	tdls_dbg(sdata, "TDLS oper %d peer %pM\n", oper, peer);

	switch (oper) {
	case NL80211_TDLS_ENABLE_LINK:
		if (sdata->vif.csa_active) {
			tdls_dbg(sdata, "TDLS: disallow link during CSA\n");
			ret = -EBUSY;
			break;
		}

		mutex_lock(&local->sta_mtx);
		sta = sta_info_get(sdata, peer);
		if (!sta) {
			mutex_unlock(&local->sta_mtx);
			ret = -ENOLINK;
			break;
		}

		iee80211_tdls_recalc_chanctx(sdata, sta);
		iee80211_tdls_recalc_ht_protection(sdata, sta);

		set_sta_flag(sta, WLAN_STA_TDLS_PEER_AUTH);
		mutex_unlock(&local->sta_mtx);

		WARN_ON_ONCE(is_zero_ether_addr(sdata->u.mgd.tdls_peer) ||
			     !ether_addr_equal(sdata->u.mgd.tdls_peer, peer));
		ret = 0;
		break;
	case NL80211_TDLS_DISABLE_LINK:
		/*
		 * The teardown message in ieee80211_tdls_mgmt_teardown() was
		 * created while the queues were stopped, so it might still be
		 * pending. Before flushing the queues we need to be sure the
		 * message is handled by the tasklet handling pending messages,
		 * otherwise we might start destroying the station before
		 * sending the teardown packet.
		 * Note that this only forces the tasklet to flush pendings -
		 * not to stop the tasklet from rescheduling itself.
		 */
		tasklet_kill(&local->tx_pending_tasklet);
		/* flush a potentially queued teardown packet */
		ieee80211_flush_queues(local, sdata, false);

		ret = sta_info_destroy_addr(sdata, peer);

		mutex_lock(&local->sta_mtx);
		iee80211_tdls_recalc_ht_protection(sdata, NULL);
		mutex_unlock(&local->sta_mtx);

		iee80211_tdls_recalc_chanctx(sdata, NULL);
		break;
	default:
		ret = -ENOTSUPP;
		break;
	}

	if (ret == 0 && ether_addr_equal(sdata->u.mgd.tdls_peer, peer)) {
		cancel_delayed_work(&sdata->u.mgd.tdls_peer_del_work);
		eth_zero_addr(sdata->u.mgd.tdls_peer);
	}

	if (ret == 0)
		ieee80211_queue_work(&sdata->local->hw,
				     &sdata->u.mgd.request_smps_work);

	mutex_unlock(&local->mtx);
	sdata_unlock(sdata);
	return ret;
}