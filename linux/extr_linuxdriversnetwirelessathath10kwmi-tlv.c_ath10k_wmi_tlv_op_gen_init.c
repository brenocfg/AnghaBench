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
struct wmi_tlv_resource_config {void* host_capab; void* num_ocb_schedules; void* num_ocb_channels; void* num_ocb_vdevs; void* wmi_send_separate; void* max_tdls_concurrent_buffer_sta; void* max_tdls_concurrent_sleep_sta; void* keep_alive_pattern_size; void* num_keep_alive_pattern; void* num_wow_filters; void* num_multicast_filter_entries; void* beacon_tx_offload_max_vdev; void* num_tdls_conn_table_entries; void* num_tdls_vdevs; void* max_frag_entries; void* num_msdu_desc; void* gtk_offload_max_vdev; void* vow_config; void* rx_skip_defrag_timeout_dup_detection_check; void* mac_aggr_delim; void* dma_burst_size; void* tx_dbg_log_size; void* mcast2ucast_mode; void* num_mcast_table_elems; void* num_mcast_groups; void* roam_offload_max_ap_profiles; void* roam_offload_max_vdev; void* bmiss_offload_max_vdev; void* scan_max_pending_reqs; void* rx_decap_mode; void** rx_timeout_pri; void* rx_chain_mask; void* tx_chain_mask; void* num_tids; void* num_peer_keys; void* num_offload_reorder_bufs; void* num_offload_peers; void* num_wds_entries; void* ast_skid_limit; void* num_peers; void* num_vdevs; } ;
struct TYPE_6__ {void* abi_ver_ns3; void* abi_ver_ns2; void* abi_ver_ns1; void* abi_ver_ns0; void* abi_ver1; void* abi_ver0; } ;
struct wmi_tlv_init_cmd {void* num_host_mem_chunks; TYPE_2__ abi; } ;
struct wmi_tlv {scalar_t__ value; void* len; void* tag; } ;
struct wmi_host_mem_chunks {int dummy; } ;
struct sk_buff {void* data; } ;
struct host_memory_chunk {int dummy; } ;
struct TYPE_5__ {int max_num_patterns; } ;
struct TYPE_8__ {int num_mem_chunks; int rx_decap_mode; int /*<<< orphan*/  svc_map; } ;
struct TYPE_7__ {int num_peers; int ast_skid_limit; int num_wds_entries; } ;
struct ath10k {TYPE_1__ wow; TYPE_4__ wmi; TYPE_3__ hw_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int TARGET_TLV_NUM_MSDU_DESC ; 
 int TARGET_TLV_NUM_TDLS_VDEVS ; 
 int TARGET_TLV_NUM_TIDS ; 
 int TARGET_TLV_NUM_VDEVS ; 
 int /*<<< orphan*/  WMI_SERVICE_RX_FULL_REORDER ; 
 int WMI_TLV_ABI_VER0 ; 
 int WMI_TLV_ABI_VER1 ; 
 int WMI_TLV_ABI_VER_NS0 ; 
 int WMI_TLV_ABI_VER_NS1 ; 
 int WMI_TLV_ABI_VER_NS2 ; 
 int WMI_TLV_ABI_VER_NS3 ; 
 size_t WMI_TLV_TAG_ARRAY_STRUCT ; 
 size_t WMI_TLV_TAG_STRUCT_INIT_CMD ; 
 size_t WMI_TLV_TAG_STRUCT_RESOURCE_CONFIG ; 
 void* __cpu_to_le16 (size_t) ; 
 void* __cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,size_t) ; 
 int /*<<< orphan*/  ath10k_wmi_put_host_mem_chunks (struct ath10k*,struct wmi_host_mem_chunks*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *ath10k_wmi_tlv_op_gen_init(struct ath10k *ar)
{
	struct sk_buff *skb;
	struct wmi_tlv *tlv;
	struct wmi_tlv_init_cmd *cmd;
	struct wmi_tlv_resource_config *cfg;
	struct wmi_host_mem_chunks *chunks;
	size_t len, chunks_len;
	void *ptr;

	chunks_len = ar->wmi.num_mem_chunks * sizeof(struct host_memory_chunk);
	len = (sizeof(*tlv) + sizeof(*cmd)) +
	      (sizeof(*tlv) + sizeof(*cfg)) +
	      (sizeof(*tlv) + chunks_len);

	skb = ath10k_wmi_alloc_skb(ar, len);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	ptr = skb->data;

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_INIT_CMD);
	tlv->len = __cpu_to_le16(sizeof(*cmd));
	cmd = (void *)tlv->value;
	ptr += sizeof(*tlv);
	ptr += sizeof(*cmd);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_STRUCT_RESOURCE_CONFIG);
	tlv->len = __cpu_to_le16(sizeof(*cfg));
	cfg = (void *)tlv->value;
	ptr += sizeof(*tlv);
	ptr += sizeof(*cfg);

	tlv = ptr;
	tlv->tag = __cpu_to_le16(WMI_TLV_TAG_ARRAY_STRUCT);
	tlv->len = __cpu_to_le16(chunks_len);
	chunks = (void *)tlv->value;

	ptr += sizeof(*tlv);
	ptr += chunks_len;

	cmd->abi.abi_ver0 = __cpu_to_le32(WMI_TLV_ABI_VER0);
	cmd->abi.abi_ver1 = __cpu_to_le32(WMI_TLV_ABI_VER1);
	cmd->abi.abi_ver_ns0 = __cpu_to_le32(WMI_TLV_ABI_VER_NS0);
	cmd->abi.abi_ver_ns1 = __cpu_to_le32(WMI_TLV_ABI_VER_NS1);
	cmd->abi.abi_ver_ns2 = __cpu_to_le32(WMI_TLV_ABI_VER_NS2);
	cmd->abi.abi_ver_ns3 = __cpu_to_le32(WMI_TLV_ABI_VER_NS3);
	cmd->num_host_mem_chunks = __cpu_to_le32(ar->wmi.num_mem_chunks);

	cfg->num_vdevs = __cpu_to_le32(TARGET_TLV_NUM_VDEVS);

	cfg->num_peers = __cpu_to_le32(ar->hw_params.num_peers);
	cfg->ast_skid_limit = __cpu_to_le32(ar->hw_params.ast_skid_limit);
	cfg->num_wds_entries = __cpu_to_le32(ar->hw_params.num_wds_entries);

	if (test_bit(WMI_SERVICE_RX_FULL_REORDER, ar->wmi.svc_map)) {
		cfg->num_offload_peers = __cpu_to_le32(TARGET_TLV_NUM_VDEVS);
		cfg->num_offload_reorder_bufs = __cpu_to_le32(TARGET_TLV_NUM_VDEVS);
	} else {
		cfg->num_offload_peers = __cpu_to_le32(0);
		cfg->num_offload_reorder_bufs = __cpu_to_le32(0);
	}

	cfg->num_peer_keys = __cpu_to_le32(2);
	cfg->num_tids = __cpu_to_le32(TARGET_TLV_NUM_TIDS);
	cfg->tx_chain_mask = __cpu_to_le32(0x7);
	cfg->rx_chain_mask = __cpu_to_le32(0x7);
	cfg->rx_timeout_pri[0] = __cpu_to_le32(0x64);
	cfg->rx_timeout_pri[1] = __cpu_to_le32(0x64);
	cfg->rx_timeout_pri[2] = __cpu_to_le32(0x64);
	cfg->rx_timeout_pri[3] = __cpu_to_le32(0x28);
	cfg->rx_decap_mode = __cpu_to_le32(ar->wmi.rx_decap_mode);
	cfg->scan_max_pending_reqs = __cpu_to_le32(4);
	cfg->bmiss_offload_max_vdev = __cpu_to_le32(TARGET_TLV_NUM_VDEVS);
	cfg->roam_offload_max_vdev = __cpu_to_le32(TARGET_TLV_NUM_VDEVS);
	cfg->roam_offload_max_ap_profiles = __cpu_to_le32(8);
	cfg->num_mcast_groups = __cpu_to_le32(0);
	cfg->num_mcast_table_elems = __cpu_to_le32(0);
	cfg->mcast2ucast_mode = __cpu_to_le32(0);
	cfg->tx_dbg_log_size = __cpu_to_le32(0x400);
	cfg->dma_burst_size = __cpu_to_le32(0);
	cfg->mac_aggr_delim = __cpu_to_le32(0);
	cfg->rx_skip_defrag_timeout_dup_detection_check = __cpu_to_le32(0);
	cfg->vow_config = __cpu_to_le32(0);
	cfg->gtk_offload_max_vdev = __cpu_to_le32(2);
	cfg->num_msdu_desc = __cpu_to_le32(TARGET_TLV_NUM_MSDU_DESC);
	cfg->max_frag_entries = __cpu_to_le32(2);
	cfg->num_tdls_vdevs = __cpu_to_le32(TARGET_TLV_NUM_TDLS_VDEVS);
	cfg->num_tdls_conn_table_entries = __cpu_to_le32(0x20);
	cfg->beacon_tx_offload_max_vdev = __cpu_to_le32(2);
	cfg->num_multicast_filter_entries = __cpu_to_le32(5);
	cfg->num_wow_filters = __cpu_to_le32(ar->wow.max_num_patterns);
	cfg->num_keep_alive_pattern = __cpu_to_le32(6);
	cfg->keep_alive_pattern_size = __cpu_to_le32(0);
	cfg->max_tdls_concurrent_sleep_sta = __cpu_to_le32(1);
	cfg->max_tdls_concurrent_buffer_sta = __cpu_to_le32(1);
	cfg->wmi_send_separate = __cpu_to_le32(0);
	cfg->num_ocb_vdevs = __cpu_to_le32(0);
	cfg->num_ocb_channels = __cpu_to_le32(0);
	cfg->num_ocb_schedules = __cpu_to_le32(0);
	cfg->host_capab = __cpu_to_le32(0);

	ath10k_wmi_put_host_mem_chunks(ar, chunks);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi tlv init\n");
	return skb;
}