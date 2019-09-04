#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct wsm_protected_mgmt_policy {int unprotectedMgmtFramesAllowed; int encryptionForAuthFrame; scalar_t__ protectedMgmtEnable; } ;
struct wsm_join {int probe_for_join; int basic_rate_set; int beacon_interval; int ssid_len; int flags; int /*<<< orphan*/  ssid; scalar_t__ dtim_period; int /*<<< orphan*/  bssid; int /*<<< orphan*/  band; int /*<<< orphan*/  channel_number; int /*<<< orphan*/  atim_window; int /*<<< orphan*/  preamble_type; int /*<<< orphan*/  mode; } ;
struct ieee80211_bss_conf {int basic_rates; int* bssid; scalar_t__ ibss_joined; } ;
struct TYPE_6__ {int /*<<< orphan*/  in_progress; } ;
struct cw1200_common {int join_pending; int beacon_int; int conf_listen_interval; int listen_interval; int listening; int disable_beacon_filter; TYPE_4__* hw; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  unjoin_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  join_timeout; scalar_t__ join_status; int /*<<< orphan*/  ba_rx_tid_mask; int /*<<< orphan*/  ba_tx_tid_mask; int /*<<< orphan*/  pm_state; TYPE_3__* vif; TYPE_5__* channel; scalar_t__ join_dtim_period; scalar_t__ bt_present; TYPE_1__ scan; } ;
struct cfg80211_bss {int dummy; } ;
struct TYPE_10__ {scalar_t__ band; int /*<<< orphan*/  hw_value; } ;
struct TYPE_7__ {scalar_t__ ps_dtim_period; } ;
struct TYPE_9__ {int /*<<< orphan*/  wiphy; TYPE_2__ conf; } ;
struct TYPE_8__ {scalar_t__ p2p; struct ieee80211_bss_conf bss_conf; } ;

/* Variables and functions */
 scalar_t__ CW1200_AUTH_TIMEOUT ; 
 scalar_t__ CW1200_JOIN_STATUS_JOINING ; 
 scalar_t__ CW1200_JOIN_TIMEOUT ; 
 int /*<<< orphan*/  IEEE80211_BSS_TYPE_ANY ; 
 int /*<<< orphan*/  IEEE80211_PRIVACY_ANY ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 int WSM_JOIN_FLAGS_FORCE ; 
 int WSM_JOIN_FLAGS_FORCE_WITH_COMPLETE_IND ; 
 int WSM_JOIN_FLAGS_P2P_GO ; 
 int /*<<< orphan*/  WSM_JOIN_MODE_BSS ; 
 int /*<<< orphan*/  WSM_JOIN_MODE_IBSS ; 
 int /*<<< orphan*/  WSM_JOIN_PREAMBLE_LONG ; 
 int /*<<< orphan*/  WSM_PHY_BAND_2_4G ; 
 int /*<<< orphan*/  WSM_PHY_BAND_5G ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct cfg80211_bss* cfg80211_get_bss (int /*<<< orphan*/ ,TYPE_5__*,int const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_put_bss (int /*<<< orphan*/ ,struct cfg80211_bss*) ; 
 int /*<<< orphan*/  cw1200_do_unjoin (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_join_complete (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_pm_stay_awake (int /*<<< orphan*/ *,scalar_t__) ; 
 int cw1200_rate_mask_to_wsm (struct cw1200_common*,int) ; 
 int /*<<< orphan*/  cw1200_update_filtering (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_update_listening (struct cw1200_common*,int) ; 
 int /*<<< orphan*/  cw1200_upload_keys (struct cw1200_common*) ; 
 scalar_t__ delayed_work_pending (int /*<<< orphan*/ *) ; 
 int* ieee80211_bss_get_ie (struct cfg80211_bss*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  wsm_flush_tx (struct cw1200_common*) ; 
 scalar_t__ wsm_join (struct cw1200_common*,struct wsm_join*) ; 
 int /*<<< orphan*/  wsm_set_block_ack_policy (struct cw1200_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsm_set_protected_mgmt_policy (struct cw1200_common*,struct wsm_protected_mgmt_policy*) ; 
 int /*<<< orphan*/  wsm_unlock_tx (struct cw1200_common*) ; 

__attribute__((used)) static void cw1200_do_join(struct cw1200_common *priv)
{
	const u8 *bssid;
	struct ieee80211_bss_conf *conf = &priv->vif->bss_conf;
	struct cfg80211_bss *bss = NULL;
	struct wsm_protected_mgmt_policy mgmt_policy;
	struct wsm_join join = {
		.mode = conf->ibss_joined ?
				WSM_JOIN_MODE_IBSS : WSM_JOIN_MODE_BSS,
		.preamble_type = WSM_JOIN_PREAMBLE_LONG,
		.probe_for_join = 1,
		.atim_window = 0,
		.basic_rate_set = cw1200_rate_mask_to_wsm(priv,
							  conf->basic_rates),
	};
	if (delayed_work_pending(&priv->join_timeout)) {
		pr_warn("[STA] - Join request already pending, skipping..\n");
		wsm_unlock_tx(priv);
		return;
	}

	if (priv->join_status)
		cw1200_do_unjoin(priv);

	bssid = priv->vif->bss_conf.bssid;

	bss = cfg80211_get_bss(priv->hw->wiphy, priv->channel, bssid, NULL, 0,
			       IEEE80211_BSS_TYPE_ANY, IEEE80211_PRIVACY_ANY);

	if (!bss && !conf->ibss_joined) {
		wsm_unlock_tx(priv);
		return;
	}

	mutex_lock(&priv->conf_mutex);

	/* Under the conf lock: check scan status and
	 * bail out if it is in progress.
	 */
	if (atomic_read(&priv->scan.in_progress)) {
		wsm_unlock_tx(priv);
		goto done_put;
	}

	priv->join_pending = true;

	/* Sanity check basic rates */
	if (!join.basic_rate_set)
		join.basic_rate_set = 7;

	/* Sanity check beacon interval */
	if (!priv->beacon_int)
		priv->beacon_int = 1;

	join.beacon_interval = priv->beacon_int;

	/* BT Coex related changes */
	if (priv->bt_present) {
		if (((priv->conf_listen_interval * 100) %
		     priv->beacon_int) == 0)
			priv->listen_interval =
				((priv->conf_listen_interval * 100) /
				 priv->beacon_int);
		else
			priv->listen_interval =
				((priv->conf_listen_interval * 100) /
				 priv->beacon_int + 1);
	}

	if (priv->hw->conf.ps_dtim_period)
		priv->join_dtim_period = priv->hw->conf.ps_dtim_period;
	join.dtim_period = priv->join_dtim_period;

	join.channel_number = priv->channel->hw_value;
	join.band = (priv->channel->band == NL80211_BAND_5GHZ) ?
		WSM_PHY_BAND_5G : WSM_PHY_BAND_2_4G;

	memcpy(join.bssid, bssid, sizeof(join.bssid));

	pr_debug("[STA] Join BSSID: %pM DTIM: %d, interval: %d\n",
		 join.bssid,
		 join.dtim_period, priv->beacon_int);

	if (!conf->ibss_joined) {
		const u8 *ssidie;
		rcu_read_lock();
		ssidie = ieee80211_bss_get_ie(bss, WLAN_EID_SSID);
		if (ssidie) {
			join.ssid_len = ssidie[1];
			memcpy(join.ssid, &ssidie[2], join.ssid_len);
		}
		rcu_read_unlock();
	}

	if (priv->vif->p2p) {
		join.flags |= WSM_JOIN_FLAGS_P2P_GO;
		join.basic_rate_set =
			cw1200_rate_mask_to_wsm(priv, 0xFF0);
	}

	/* Enable asynchronous join calls */
	if (!conf->ibss_joined) {
		join.flags |= WSM_JOIN_FLAGS_FORCE;
		join.flags |= WSM_JOIN_FLAGS_FORCE_WITH_COMPLETE_IND;
	}

	wsm_flush_tx(priv);

	/* Stay Awake for Join and Auth Timeouts and a bit more */
	cw1200_pm_stay_awake(&priv->pm_state,
			     CW1200_JOIN_TIMEOUT + CW1200_AUTH_TIMEOUT);

	cw1200_update_listening(priv, false);

	/* Turn on Block ACKs */
	wsm_set_block_ack_policy(priv, priv->ba_tx_tid_mask,
				 priv->ba_rx_tid_mask);

	/* Set up timeout */
	if (join.flags & WSM_JOIN_FLAGS_FORCE_WITH_COMPLETE_IND) {
		priv->join_status = CW1200_JOIN_STATUS_JOINING;
		queue_delayed_work(priv->workqueue,
				   &priv->join_timeout,
				   CW1200_JOIN_TIMEOUT);
	}

	/* 802.11w protected mgmt frames */
	mgmt_policy.protectedMgmtEnable = 0;
	mgmt_policy.unprotectedMgmtFramesAllowed = 1;
	mgmt_policy.encryptionForAuthFrame = 1;
	wsm_set_protected_mgmt_policy(priv, &mgmt_policy);

	/* Perform actual join */
	if (wsm_join(priv, &join)) {
		pr_err("[STA] cw1200_join_work: wsm_join failed!\n");
		cancel_delayed_work_sync(&priv->join_timeout);
		cw1200_update_listening(priv, priv->listening);
		/* Tx lock still held, unjoin will clear it. */
		if (queue_work(priv->workqueue, &priv->unjoin_work) <= 0)
			wsm_unlock_tx(priv);
	} else {
		if (!(join.flags & WSM_JOIN_FLAGS_FORCE_WITH_COMPLETE_IND))
			cw1200_join_complete(priv); /* Will clear tx_lock */

		/* Upload keys */
		cw1200_upload_keys(priv);

		/* Due to beacon filtering it is possible that the
		 * AP's beacon is not known for the mac80211 stack.
		 * Disable filtering temporary to make sure the stack
		 * receives at least one
		 */
		priv->disable_beacon_filter = true;
	}
	cw1200_update_filtering(priv);

done_put:
	mutex_unlock(&priv->conf_mutex);
	if (bss)
		cfg80211_put_bss(priv->hw->wiphy, bss);
}