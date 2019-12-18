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
struct wiphy {int flags; int features; int bss_priv_size; int /*<<< orphan*/  extended_capabilities_len; int /*<<< orphan*/ * extended_capabilities_mask; int /*<<< orphan*/ * extended_capabilities; int /*<<< orphan*/ * vht_capa_mod_mask; int /*<<< orphan*/ * ht_capa_mod_mask; int /*<<< orphan*/  retry_short; int /*<<< orphan*/  retry_long; int /*<<< orphan*/  privid; int /*<<< orphan*/  mgmt_stypes; } ;
struct ieee80211_ops {scalar_t__ wake_tx_queue; int /*<<< orphan*/  set_key; int /*<<< orphan*/  hw_scan; scalar_t__ remain_on_channel; int /*<<< orphan*/  unassign_vif_chanctx; int /*<<< orphan*/  assign_vif_chanctx; int /*<<< orphan*/  change_chanctx; int /*<<< orphan*/  remove_chanctx; int /*<<< orphan*/  add_chanctx; scalar_t__ sta_remove; scalar_t__ sta_add; scalar_t__ sta_state; int /*<<< orphan*/  configure_filter; int /*<<< orphan*/  remove_interface; int /*<<< orphan*/  add_interface; int /*<<< orphan*/  config; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  tx; } ;
struct TYPE_4__ {int units_pos; int accuracy; } ;
struct TYPE_3__ {int /*<<< orphan*/  short_frame_max_tx_count; int /*<<< orphan*/  long_frame_max_tx_count; } ;
struct ieee80211_hw {char* priv; int tx_sk_pacing_shift; int queues; int max_rates; int radiotap_mcs_details; int radiotap_vht_details; TYPE_2__ radiotap_timestamp; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  uapsd_max_sp_len; int /*<<< orphan*/  uapsd_queues; TYPE_1__ conf; int /*<<< orphan*/  offchannel_tx_hw_queue; void* max_tx_aggregation_subframes; void* max_rx_aggregation_subframes; scalar_t__ max_report_rates; struct wiphy* wiphy; } ;
struct ieee80211_local {int use_chanctx; int airtime_flags; struct ieee80211_hw hw; int /*<<< orphan*/  skb_queue_tdls_chsw; int /*<<< orphan*/  skb_queue_unreliable; int /*<<< orphan*/  skb_queue; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  wake_txqs_tasklet; int /*<<< orphan*/  tx_pending_tasklet; int /*<<< orphan*/ * agg_queue_stop; int /*<<< orphan*/ * pending; int /*<<< orphan*/  ack_status_frames; int /*<<< orphan*/  ack_status_lock; int /*<<< orphan*/  tdls_chsw_work; int /*<<< orphan*/  sched_scan_stopped_work; int /*<<< orphan*/  dynamic_ps_timer; int /*<<< orphan*/  dynamic_ps_disable_work; int /*<<< orphan*/  dynamic_ps_enable_work; int /*<<< orphan*/  smps_mode; int /*<<< orphan*/  reconfig_filter; int /*<<< orphan*/  radar_detected_work; int /*<<< orphan*/  restart_work; int /*<<< orphan*/  scan_work; int /*<<< orphan*/  chanctx_mtx; int /*<<< orphan*/  chanctx_list; int /*<<< orphan*/ * active_txq_lock; int /*<<< orphan*/ * active_txqs; int /*<<< orphan*/  queue_stop_reason_lock; int /*<<< orphan*/  rx_path_lock; int /*<<< orphan*/  filter_lock; int /*<<< orphan*/  key_mtx; int /*<<< orphan*/  mtx; int /*<<< orphan*/  iflist_mtx; int /*<<< orphan*/  mc_list; int /*<<< orphan*/  mon_list; int /*<<< orphan*/  interfaces; int /*<<< orphan*/ * ext_capa; int /*<<< orphan*/  user_power_level; struct ieee80211_ops const* ops; } ;
struct ieee80211_bss {int dummy; } ;

/* Variables and functions */
 int AIRTIME_USE_RX ; 
 int AIRTIME_USE_TX ; 
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEEE80211_DEFAULT_MAX_SP_LEN ; 
 int /*<<< orphan*/  IEEE80211_DEFAULT_UAPSD_QUEUES ; 
 int /*<<< orphan*/  IEEE80211_INVAL_HW_QUEUE ; 
 void* IEEE80211_MAX_AMPDU_BUF_HT ; 
 int /*<<< orphan*/  IEEE80211_MAX_DATA_LEN ; 
 int IEEE80211_MAX_QUEUES ; 
 int IEEE80211_NUM_ACS ; 
 int IEEE80211_RADIOTAP_MCS_HAVE_BW ; 
 int IEEE80211_RADIOTAP_MCS_HAVE_GI ; 
 int IEEE80211_RADIOTAP_MCS_HAVE_MCS ; 
 int IEEE80211_RADIOTAP_VHT_KNOWN_BANDWIDTH ; 
 int IEEE80211_RADIOTAP_VHT_KNOWN_GI ; 
 int /*<<< orphan*/  IEEE80211_SMPS_OFF ; 
 int /*<<< orphan*/  IEEE80211_UNSET_POWER_LEVEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETDEV_ALIGN ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_CONTROL_PORT_OVER_NL80211 ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_FILS_STA ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_RRM ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_SCAN_MIN_PREQ_CONTENT ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_SCAN_RANDOM_SN ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_TXQS ; 
 int NL80211_FEATURE_AP_SCAN ; 
 int NL80211_FEATURE_FULL_AP_CLIENT_STATE ; 
 int NL80211_FEATURE_HT_IBSS ; 
 int NL80211_FEATURE_LOW_PRIORITY_SCAN ; 
 int NL80211_FEATURE_MAC_ON_CREATE ; 
 int NL80211_FEATURE_SAE ; 
 int NL80211_FEATURE_SK_TX_STATUS ; 
 int NL80211_FEATURE_USERSPACE_MPM ; 
 int NL80211_FEATURE_VIF_TXPOWER ; 
 scalar_t__ WARN_ON (int) ; 
 int WIPHY_FLAG_4ADDR_AP ; 
 int WIPHY_FLAG_4ADDR_STATION ; 
 int WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL ; 
 int WIPHY_FLAG_IBSS_RSN ; 
 int WIPHY_FLAG_NETNS_OK ; 
 int WIPHY_FLAG_OFFCHAN_TX ; 
 int WIPHY_FLAG_REPORTS_OBSS ; 
 int /*<<< orphan*/  WLAN_EXT_CAPA8_OPMODE_NOTIF ; 
 int /*<<< orphan*/  __hw_addr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_alloc_led_names (struct ieee80211_local*) ; 
 int /*<<< orphan*/  ieee80211_default_mgmt_stypes ; 
 int /*<<< orphan*/  ieee80211_dfs_radar_detected_work ; 
 int /*<<< orphan*/  ieee80211_dynamic_ps_disable_work ; 
 int /*<<< orphan*/  ieee80211_dynamic_ps_enable_work ; 
 int /*<<< orphan*/  ieee80211_dynamic_ps_timer ; 
 int /*<<< orphan*/  ieee80211_reconfig_filter ; 
 int /*<<< orphan*/  ieee80211_restart_work ; 
 int /*<<< orphan*/  ieee80211_roc_setup (struct ieee80211_local*) ; 
 int /*<<< orphan*/  ieee80211_scan_work ; 
 int /*<<< orphan*/  ieee80211_sched_scan_stopped_work ; 
 int /*<<< orphan*/  ieee80211_tasklet_handler ; 
 int /*<<< orphan*/  ieee80211_tdls_chsw_work ; 
 int /*<<< orphan*/  ieee80211_tx_pending ; 
 int /*<<< orphan*/  ieee80211_wake_txqs ; 
 int /*<<< orphan*/  mac80211_config_ops ; 
 int /*<<< orphan*/  mac80211_ht_capa_mod_mask ; 
 int /*<<< orphan*/  mac80211_vht_capa_mod_mask ; 
 int /*<<< orphan*/  mac80211_wiphy_privid ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ sta_info_init (struct ieee80211_local*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_ext_feature_set (struct wiphy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_free (struct wiphy*) ; 
 struct wiphy* wiphy_new_nm (int /*<<< orphan*/ *,int,char const*) ; 
 struct ieee80211_local* wiphy_priv (struct wiphy*) ; 

struct ieee80211_hw *ieee80211_alloc_hw_nm(size_t priv_data_len,
					   const struct ieee80211_ops *ops,
					   const char *requested_name)
{
	struct ieee80211_local *local;
	int priv_size, i;
	struct wiphy *wiphy;
	bool use_chanctx;

	if (WARN_ON(!ops->tx || !ops->start || !ops->stop || !ops->config ||
		    !ops->add_interface || !ops->remove_interface ||
		    !ops->configure_filter))
		return NULL;

	if (WARN_ON(ops->sta_state && (ops->sta_add || ops->sta_remove)))
		return NULL;

	/* check all or no channel context operations exist */
	i = !!ops->add_chanctx + !!ops->remove_chanctx +
	    !!ops->change_chanctx + !!ops->assign_vif_chanctx +
	    !!ops->unassign_vif_chanctx;
	if (WARN_ON(i != 0 && i != 5))
		return NULL;
	use_chanctx = i == 5;

	/* Ensure 32-byte alignment of our private data and hw private data.
	 * We use the wiphy priv data for both our ieee80211_local and for
	 * the driver's private data
	 *
	 * In memory it'll be like this:
	 *
	 * +-------------------------+
	 * | struct wiphy	    |
	 * +-------------------------+
	 * | struct ieee80211_local  |
	 * +-------------------------+
	 * | driver's private data   |
	 * +-------------------------+
	 *
	 */
	priv_size = ALIGN(sizeof(*local), NETDEV_ALIGN) + priv_data_len;

	wiphy = wiphy_new_nm(&mac80211_config_ops, priv_size, requested_name);

	if (!wiphy)
		return NULL;

	wiphy->mgmt_stypes = ieee80211_default_mgmt_stypes;

	wiphy->privid = mac80211_wiphy_privid;

	wiphy->flags |= WIPHY_FLAG_NETNS_OK |
			WIPHY_FLAG_4ADDR_AP |
			WIPHY_FLAG_4ADDR_STATION |
			WIPHY_FLAG_REPORTS_OBSS |
			WIPHY_FLAG_OFFCHAN_TX;

	if (ops->remain_on_channel)
		wiphy->flags |= WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL;

	wiphy->features |= NL80211_FEATURE_SK_TX_STATUS |
			   NL80211_FEATURE_SAE |
			   NL80211_FEATURE_HT_IBSS |
			   NL80211_FEATURE_VIF_TXPOWER |
			   NL80211_FEATURE_MAC_ON_CREATE |
			   NL80211_FEATURE_USERSPACE_MPM |
			   NL80211_FEATURE_FULL_AP_CLIENT_STATE;
	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_FILS_STA);
	wiphy_ext_feature_set(wiphy,
			      NL80211_EXT_FEATURE_CONTROL_PORT_OVER_NL80211);

	if (!ops->hw_scan) {
		wiphy->features |= NL80211_FEATURE_LOW_PRIORITY_SCAN |
				   NL80211_FEATURE_AP_SCAN;
		/*
		 * if the driver behaves correctly using the probe request
		 * (template) from mac80211, then both of these should be
		 * supported even with hw scan - but let drivers opt in.
		 */
		wiphy_ext_feature_set(wiphy,
				      NL80211_EXT_FEATURE_SCAN_RANDOM_SN);
		wiphy_ext_feature_set(wiphy,
				      NL80211_EXT_FEATURE_SCAN_MIN_PREQ_CONTENT);
	}

	if (!ops->set_key)
		wiphy->flags |= WIPHY_FLAG_IBSS_RSN;

	if (ops->wake_tx_queue)
		wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_TXQS);

	wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_RRM);

	wiphy->bss_priv_size = sizeof(struct ieee80211_bss);

	local = wiphy_priv(wiphy);

	if (sta_info_init(local))
		goto err_free;

	local->hw.wiphy = wiphy;

	local->hw.priv = (char *)local + ALIGN(sizeof(*local), NETDEV_ALIGN);

	local->ops = ops;
	local->use_chanctx = use_chanctx;

	/*
	 * We need a bit of data queued to build aggregates properly, so
	 * instruct the TCP stack to allow more than a single ms of data
	 * to be queued in the stack. The value is a bit-shift of 1
	 * second, so 7 is ~8ms of queued data. Only affects local TCP
	 * sockets.
	 * This is the default, anyhow - drivers may need to override it
	 * for local reasons (longer buffers, longer completion time, or
	 * similar).
	 */
	local->hw.tx_sk_pacing_shift = 7;

	/* set up some defaults */
	local->hw.queues = 1;
	local->hw.max_rates = 1;
	local->hw.max_report_rates = 0;
	local->hw.max_rx_aggregation_subframes = IEEE80211_MAX_AMPDU_BUF_HT;
	local->hw.max_tx_aggregation_subframes = IEEE80211_MAX_AMPDU_BUF_HT;
	local->hw.offchannel_tx_hw_queue = IEEE80211_INVAL_HW_QUEUE;
	local->hw.conf.long_frame_max_tx_count = wiphy->retry_long;
	local->hw.conf.short_frame_max_tx_count = wiphy->retry_short;
	local->hw.radiotap_mcs_details = IEEE80211_RADIOTAP_MCS_HAVE_MCS |
					 IEEE80211_RADIOTAP_MCS_HAVE_GI |
					 IEEE80211_RADIOTAP_MCS_HAVE_BW;
	local->hw.radiotap_vht_details = IEEE80211_RADIOTAP_VHT_KNOWN_GI |
					 IEEE80211_RADIOTAP_VHT_KNOWN_BANDWIDTH;
	local->hw.uapsd_queues = IEEE80211_DEFAULT_UAPSD_QUEUES;
	local->hw.uapsd_max_sp_len = IEEE80211_DEFAULT_MAX_SP_LEN;
	local->hw.max_mtu = IEEE80211_MAX_DATA_LEN;
	local->user_power_level = IEEE80211_UNSET_POWER_LEVEL;
	wiphy->ht_capa_mod_mask = &mac80211_ht_capa_mod_mask;
	wiphy->vht_capa_mod_mask = &mac80211_vht_capa_mod_mask;

	local->ext_capa[7] = WLAN_EXT_CAPA8_OPMODE_NOTIF;

	wiphy->extended_capabilities = local->ext_capa;
	wiphy->extended_capabilities_mask = local->ext_capa;
	wiphy->extended_capabilities_len =
		ARRAY_SIZE(local->ext_capa);

	INIT_LIST_HEAD(&local->interfaces);
	INIT_LIST_HEAD(&local->mon_list);

	__hw_addr_init(&local->mc_list);

	mutex_init(&local->iflist_mtx);
	mutex_init(&local->mtx);

	mutex_init(&local->key_mtx);
	spin_lock_init(&local->filter_lock);
	spin_lock_init(&local->rx_path_lock);
	spin_lock_init(&local->queue_stop_reason_lock);

	for (i = 0; i < IEEE80211_NUM_ACS; i++) {
		INIT_LIST_HEAD(&local->active_txqs[i]);
		spin_lock_init(&local->active_txq_lock[i]);
	}
	local->airtime_flags = AIRTIME_USE_TX | AIRTIME_USE_RX;

	INIT_LIST_HEAD(&local->chanctx_list);
	mutex_init(&local->chanctx_mtx);

	INIT_DELAYED_WORK(&local->scan_work, ieee80211_scan_work);

	INIT_WORK(&local->restart_work, ieee80211_restart_work);

	INIT_WORK(&local->radar_detected_work,
		  ieee80211_dfs_radar_detected_work);

	INIT_WORK(&local->reconfig_filter, ieee80211_reconfig_filter);
	local->smps_mode = IEEE80211_SMPS_OFF;

	INIT_WORK(&local->dynamic_ps_enable_work,
		  ieee80211_dynamic_ps_enable_work);
	INIT_WORK(&local->dynamic_ps_disable_work,
		  ieee80211_dynamic_ps_disable_work);
	timer_setup(&local->dynamic_ps_timer, ieee80211_dynamic_ps_timer, 0);

	INIT_WORK(&local->sched_scan_stopped_work,
		  ieee80211_sched_scan_stopped_work);

	INIT_WORK(&local->tdls_chsw_work, ieee80211_tdls_chsw_work);

	spin_lock_init(&local->ack_status_lock);
	idr_init(&local->ack_status_frames);

	for (i = 0; i < IEEE80211_MAX_QUEUES; i++) {
		skb_queue_head_init(&local->pending[i]);
		atomic_set(&local->agg_queue_stop[i], 0);
	}
	tasklet_init(&local->tx_pending_tasklet, ieee80211_tx_pending,
		     (unsigned long)local);

	if (ops->wake_tx_queue)
		tasklet_init(&local->wake_txqs_tasklet, ieee80211_wake_txqs,
			     (unsigned long)local);

	tasklet_init(&local->tasklet,
		     ieee80211_tasklet_handler,
		     (unsigned long) local);

	skb_queue_head_init(&local->skb_queue);
	skb_queue_head_init(&local->skb_queue_unreliable);
	skb_queue_head_init(&local->skb_queue_tdls_chsw);

	ieee80211_alloc_led_names(local);

	ieee80211_roc_setup(local);

	local->hw.radiotap_timestamp.units_pos = -1;
	local->hw.radiotap_timestamp.accuracy = -1;

	return &local->hw;
 err_free:
	wiphy_free(wiphy);
	return NULL;
}