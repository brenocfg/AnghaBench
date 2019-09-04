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
typedef  int u32 ;
struct wmi_resource_config_10x {void* max_frag_entries; void* num_msdu_desc; void* vow_config; void* rx_skip_defrag_timeout_dup_detection_check; void* mac_aggr_delim; void* dma_burst_size; void* num_wds_entries; void* tx_dbg_log_size; void* mcast2ucast_mode; void* num_mcast_table_elems; void* num_mcast_groups; void* roam_offload_max_ap_profiles; void* roam_offload_max_vdev; void* bmiss_offload_max_vdev; void* scan_max_pending_reqs; void* rx_decap_mode; void* rx_timeout_pri_bk; void* rx_timeout_pri_be; void* rx_timeout_pri_vi; void* rx_timeout_pri_vo; void* rx_chain_mask; void* tx_chain_mask; void* ast_skid_limit; void* num_tids; void* num_peers; void* num_peer_keys; void* num_vdevs; } ;
struct TYPE_4__ {int /*<<< orphan*/  common; void* feature_mask; } ;
struct wmi_init_cmd_10_2 {int /*<<< orphan*/  mem_chunks; TYPE_2__ resource_config; } ;
struct sk_buff {scalar_t__ data; } ;
struct host_memory_chunk {int dummy; } ;
struct TYPE_3__ {int rx_decap_mode; int num_mem_chunks; int /*<<< orphan*/ * svc_map; } ;
struct ath10k {TYPE_1__ wmi; int /*<<< orphan*/  dev_flags; } ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ATH10K_FLAG_BTCOEX ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int TARGET_10X_AST_SKID_LIMIT ; 
 int TARGET_10X_BMISS_OFFLOAD_MAX_VDEV ; 
 int TARGET_10X_MAC_AGGR_DELIM ; 
 int TARGET_10X_MAX_FRAG_ENTRIES ; 
 int TARGET_10X_MCAST2UCAST_MODE ; 
 int TARGET_10X_NUM_MCAST_GROUPS ; 
 int TARGET_10X_NUM_MCAST_TABLE_ELEMS ; 
 int TARGET_10X_NUM_MSDU_DESC ; 
 int TARGET_10X_NUM_PEERS ; 
 int TARGET_10X_NUM_PEER_KEYS ; 
 int TARGET_10X_NUM_TIDS ; 
 int TARGET_10X_NUM_VDEVS ; 
 int TARGET_10X_NUM_WDS_ENTRIES ; 
 int TARGET_10X_ROAM_OFFLOAD_MAX_AP_PROFILES ; 
 int TARGET_10X_ROAM_OFFLOAD_MAX_VDEV ; 
 int TARGET_10X_RX_CHAIN_MASK ; 
 int TARGET_10X_RX_SKIP_DEFRAG_TIMEOUT_DUP_DETECTION_CHECK ; 
 int TARGET_10X_RX_TIMEOUT_HI_PRI ; 
 int TARGET_10X_RX_TIMEOUT_LO_PRI ; 
 int TARGET_10X_SCAN_MAX_PENDING_REQS ; 
 int TARGET_10X_TX_CHAIN_MASK ; 
 int TARGET_10X_TX_DBG_LOG_SIZE ; 
 int TARGET_10X_TX_STATS_NUM_PEERS ; 
 int TARGET_10X_TX_STATS_NUM_TIDS ; 
 int TARGET_10X_VOW_CONFIG ; 
 int TARGET_10_2_DMA_BURST_SIZE ; 
 int WMI_10_2_BSS_CHAN_INFO ; 
 int WMI_10_2_COEX_GPIO ; 
 int WMI_10_2_PEER_STATS ; 
 int WMI_10_2_RX_BATCH_MODE ; 
 int /*<<< orphan*/  WMI_SERVICE_BSS_CHANNEL_INFO_64 ; 
 int /*<<< orphan*/  WMI_SERVICE_COEX_GPIO ; 
 void* __cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ath10k_peer_stats_enabled (struct ath10k*) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int) ; 
 int /*<<< orphan*/  ath10k_wmi_put_host_mem_chunks (struct ath10k*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct wmi_resource_config_10x*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sk_buff *ath10k_wmi_10_2_op_gen_init(struct ath10k *ar)
{
	struct wmi_init_cmd_10_2 *cmd;
	struct sk_buff *buf;
	struct wmi_resource_config_10x config = {};
	u32 len, val, features;

	config.num_vdevs = __cpu_to_le32(TARGET_10X_NUM_VDEVS);
	config.num_peer_keys = __cpu_to_le32(TARGET_10X_NUM_PEER_KEYS);

	if (ath10k_peer_stats_enabled(ar)) {
		config.num_peers = __cpu_to_le32(TARGET_10X_TX_STATS_NUM_PEERS);
		config.num_tids = __cpu_to_le32(TARGET_10X_TX_STATS_NUM_TIDS);
	} else {
		config.num_peers = __cpu_to_le32(TARGET_10X_NUM_PEERS);
		config.num_tids = __cpu_to_le32(TARGET_10X_NUM_TIDS);
	}

	config.ast_skid_limit = __cpu_to_le32(TARGET_10X_AST_SKID_LIMIT);
	config.tx_chain_mask = __cpu_to_le32(TARGET_10X_TX_CHAIN_MASK);
	config.rx_chain_mask = __cpu_to_le32(TARGET_10X_RX_CHAIN_MASK);
	config.rx_timeout_pri_vo = __cpu_to_le32(TARGET_10X_RX_TIMEOUT_LO_PRI);
	config.rx_timeout_pri_vi = __cpu_to_le32(TARGET_10X_RX_TIMEOUT_LO_PRI);
	config.rx_timeout_pri_be = __cpu_to_le32(TARGET_10X_RX_TIMEOUT_LO_PRI);
	config.rx_timeout_pri_bk = __cpu_to_le32(TARGET_10X_RX_TIMEOUT_HI_PRI);
	config.rx_decap_mode = __cpu_to_le32(ar->wmi.rx_decap_mode);

	config.scan_max_pending_reqs =
		__cpu_to_le32(TARGET_10X_SCAN_MAX_PENDING_REQS);

	config.bmiss_offload_max_vdev =
		__cpu_to_le32(TARGET_10X_BMISS_OFFLOAD_MAX_VDEV);

	config.roam_offload_max_vdev =
		__cpu_to_le32(TARGET_10X_ROAM_OFFLOAD_MAX_VDEV);

	config.roam_offload_max_ap_profiles =
		__cpu_to_le32(TARGET_10X_ROAM_OFFLOAD_MAX_AP_PROFILES);

	config.num_mcast_groups = __cpu_to_le32(TARGET_10X_NUM_MCAST_GROUPS);
	config.num_mcast_table_elems =
		__cpu_to_le32(TARGET_10X_NUM_MCAST_TABLE_ELEMS);

	config.mcast2ucast_mode = __cpu_to_le32(TARGET_10X_MCAST2UCAST_MODE);
	config.tx_dbg_log_size = __cpu_to_le32(TARGET_10X_TX_DBG_LOG_SIZE);
	config.num_wds_entries = __cpu_to_le32(TARGET_10X_NUM_WDS_ENTRIES);
	config.dma_burst_size = __cpu_to_le32(TARGET_10_2_DMA_BURST_SIZE);
	config.mac_aggr_delim = __cpu_to_le32(TARGET_10X_MAC_AGGR_DELIM);

	val = TARGET_10X_RX_SKIP_DEFRAG_TIMEOUT_DUP_DETECTION_CHECK;
	config.rx_skip_defrag_timeout_dup_detection_check = __cpu_to_le32(val);

	config.vow_config = __cpu_to_le32(TARGET_10X_VOW_CONFIG);

	config.num_msdu_desc = __cpu_to_le32(TARGET_10X_NUM_MSDU_DESC);
	config.max_frag_entries = __cpu_to_le32(TARGET_10X_MAX_FRAG_ENTRIES);

	len = sizeof(*cmd) +
	      (sizeof(struct host_memory_chunk) * ar->wmi.num_mem_chunks);

	buf = ath10k_wmi_alloc_skb(ar, len);
	if (!buf)
		return ERR_PTR(-ENOMEM);

	cmd = (struct wmi_init_cmd_10_2 *)buf->data;

	features = WMI_10_2_RX_BATCH_MODE;

	if (test_bit(ATH10K_FLAG_BTCOEX, &ar->dev_flags) &&
	    test_bit(WMI_SERVICE_COEX_GPIO, ar->wmi.svc_map))
		features |= WMI_10_2_COEX_GPIO;

	if (ath10k_peer_stats_enabled(ar))
		features |= WMI_10_2_PEER_STATS;

	if (test_bit(WMI_SERVICE_BSS_CHANNEL_INFO_64, ar->wmi.svc_map))
		features |= WMI_10_2_BSS_CHAN_INFO;

	cmd->resource_config.feature_mask = __cpu_to_le32(features);

	memcpy(&cmd->resource_config.common, &config, sizeof(config));
	ath10k_wmi_put_host_mem_chunks(ar, &cmd->mem_chunks);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi init 10.2\n");
	return buf;
}