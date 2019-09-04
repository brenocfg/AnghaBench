#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct mwifiex_private {TYPE_5__* adapter; } ;
struct TYPE_13__ {void* len; void* type; } ;
struct mwifiex_ie_types_wildcard_ssid_params {TYPE_11__ header; int /*<<< orphan*/  ssid; scalar_t__ max_ssid_length; } ;
struct TYPE_20__ {void* len; void* type; } ;
struct mwifiex_ie_types_repeat_count {TYPE_7__ header; void* repeat_count; } ;
struct TYPE_19__ {void* len; void* type; } ;
struct mwifiex_ie_types_num_probes {TYPE_6__ header; void* num_probes; } ;
struct TYPE_21__ {void* len; void* type; } ;
struct mwifiex_ie_types_min_rssi_threshold {TYPE_8__ header; void* rssi_threshold; } ;
struct TYPE_15__ {void* len; void* type; } ;
struct mwifiex_ie_types_chan_list_param_set {TYPE_2__ header; struct mwifiex_chan_scan_param_set* chan_scan_param; } ;
struct TYPE_16__ {void* len; void* type; } ;
struct mwifiex_ie_types_bgscan_start_later {TYPE_3__ header; void* start_later; } ;
struct mwifiex_chan_scan_param_set {void* max_scan_time; void* min_scan_time; int /*<<< orphan*/  chan_scan_mode_bitmap; int /*<<< orphan*/  radio_type; scalar_t__ chan_number; } ;
struct mwifiex_bg_scan_cfg {int action; int repeat_count; int rssi_threshold; int num_ssids; int start_later; TYPE_1__* chan_list; TYPE_10__* ssid_list; scalar_t__ num_probes; int /*<<< orphan*/  chan_per_scan; int /*<<< orphan*/  report_condition; int /*<<< orphan*/  scan_interval; int /*<<< orphan*/  bss_type; int /*<<< orphan*/  enable; } ;
struct host_cmd_ds_802_11_bg_scan_config {scalar_t__* tlv; int /*<<< orphan*/  chan_per_scan; int /*<<< orphan*/  enable; void* report_condition; void* scan_interval; int /*<<< orphan*/  bss_type; void* action; } ;
struct TYPE_17__ {struct host_cmd_ds_802_11_bg_scan_config bg_scan_config; } ;
struct host_cmd_ds_command {void* size; void* command; TYPE_4__ params; } ;
struct TYPE_22__ {size_t ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_18__ {size_t passive_scan_time; size_t specific_scan_time; int /*<<< orphan*/  dev; scalar_t__ scan_probes; } ;
struct TYPE_14__ {size_t scan_type; scalar_t__ scan_time; int /*<<< orphan*/  radio_type; scalar_t__ chan_number; } ;
struct TYPE_12__ {TYPE_9__ ssid; } ;

/* Variables and functions */
 int HostCmd_CMD_802_11_BG_SCAN_CONFIG ; 
 scalar_t__ IEEE80211_MAX_SSID_LEN ; 
 size_t MWIFIEX_BG_SCAN_CHAN_MAX ; 
 int /*<<< orphan*/  MWIFIEX_PASSIVE_SCAN ; 
 size_t MWIFIEX_SCAN_TYPE_PASSIVE ; 
 int /*<<< orphan*/  MWIFIEX_VSIE_MASK_BGSCAN ; 
 int S_DS_GEN ; 
 int TLV_TYPE_BGSCAN_START_LATER ; 
 int TLV_TYPE_CHANLIST ; 
 int TLV_TYPE_NUMPROBES ; 
 int TLV_TYPE_REPEAT_COUNT ; 
 int TLV_TYPE_RSSI_LOW ; 
 int TLV_TYPE_WILDCARDSSID ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ le16_to_cpu (void*) ; 
 int /*<<< orphan*/  le16_unaligned_add_cpu (void**,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t mwifiex_bgscan_create_channel_list (struct mwifiex_private*,struct mwifiex_bg_scan_cfg*,struct mwifiex_chan_scan_param_set*) ; 
 int /*<<< orphan*/  mwifiex_cmd_append_vsie_tlv (struct mwifiex_private*,int /*<<< orphan*/ ,scalar_t__**) ; 

int mwifiex_cmd_802_11_bg_scan_config(struct mwifiex_private *priv,
				      struct host_cmd_ds_command *cmd,
				      void *data_buf)
{
	struct host_cmd_ds_802_11_bg_scan_config *bgscan_config =
					&cmd->params.bg_scan_config;
	struct mwifiex_bg_scan_cfg *bgscan_cfg_in = data_buf;
	u8 *tlv_pos = bgscan_config->tlv;
	u8 num_probes;
	u32 ssid_len, chan_idx, scan_type, scan_dur, chan_num;
	int i;
	struct mwifiex_ie_types_num_probes *num_probes_tlv;
	struct mwifiex_ie_types_repeat_count *repeat_count_tlv;
	struct mwifiex_ie_types_min_rssi_threshold *rssi_threshold_tlv;
	struct mwifiex_ie_types_bgscan_start_later *start_later_tlv;
	struct mwifiex_ie_types_wildcard_ssid_params *wildcard_ssid_tlv;
	struct mwifiex_ie_types_chan_list_param_set *chan_list_tlv;
	struct mwifiex_chan_scan_param_set *temp_chan;

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_BG_SCAN_CONFIG);
	cmd->size = cpu_to_le16(sizeof(*bgscan_config) + S_DS_GEN);

	bgscan_config->action = cpu_to_le16(bgscan_cfg_in->action);
	bgscan_config->enable = bgscan_cfg_in->enable;
	bgscan_config->bss_type = bgscan_cfg_in->bss_type;
	bgscan_config->scan_interval =
		cpu_to_le32(bgscan_cfg_in->scan_interval);
	bgscan_config->report_condition =
		cpu_to_le32(bgscan_cfg_in->report_condition);

	/*  stop sched scan  */
	if (!bgscan_config->enable)
		return 0;

	bgscan_config->chan_per_scan = bgscan_cfg_in->chan_per_scan;

	num_probes = (bgscan_cfg_in->num_probes ? bgscan_cfg_in->
		      num_probes : priv->adapter->scan_probes);

	if (num_probes) {
		num_probes_tlv = (struct mwifiex_ie_types_num_probes *)tlv_pos;
		num_probes_tlv->header.type = cpu_to_le16(TLV_TYPE_NUMPROBES);
		num_probes_tlv->header.len =
			cpu_to_le16(sizeof(num_probes_tlv->num_probes));
		num_probes_tlv->num_probes = cpu_to_le16((u16)num_probes);

		tlv_pos += sizeof(num_probes_tlv->header) +
			le16_to_cpu(num_probes_tlv->header.len);
	}

	if (bgscan_cfg_in->repeat_count) {
		repeat_count_tlv =
			(struct mwifiex_ie_types_repeat_count *)tlv_pos;
		repeat_count_tlv->header.type =
			cpu_to_le16(TLV_TYPE_REPEAT_COUNT);
		repeat_count_tlv->header.len =
			cpu_to_le16(sizeof(repeat_count_tlv->repeat_count));
		repeat_count_tlv->repeat_count =
			cpu_to_le16(bgscan_cfg_in->repeat_count);

		tlv_pos += sizeof(repeat_count_tlv->header) +
			le16_to_cpu(repeat_count_tlv->header.len);
	}

	if (bgscan_cfg_in->rssi_threshold) {
		rssi_threshold_tlv =
			(struct mwifiex_ie_types_min_rssi_threshold *)tlv_pos;
		rssi_threshold_tlv->header.type =
			cpu_to_le16(TLV_TYPE_RSSI_LOW);
		rssi_threshold_tlv->header.len =
			cpu_to_le16(sizeof(rssi_threshold_tlv->rssi_threshold));
		rssi_threshold_tlv->rssi_threshold =
			cpu_to_le16(bgscan_cfg_in->rssi_threshold);

		tlv_pos += sizeof(rssi_threshold_tlv->header) +
			le16_to_cpu(rssi_threshold_tlv->header.len);
	}

	for (i = 0; i < bgscan_cfg_in->num_ssids; i++) {
		ssid_len = bgscan_cfg_in->ssid_list[i].ssid.ssid_len;

		wildcard_ssid_tlv =
			(struct mwifiex_ie_types_wildcard_ssid_params *)tlv_pos;
		wildcard_ssid_tlv->header.type =
				cpu_to_le16(TLV_TYPE_WILDCARDSSID);
		wildcard_ssid_tlv->header.len = cpu_to_le16(
				(u16)(ssid_len + sizeof(wildcard_ssid_tlv->
							 max_ssid_length)));

		/* max_ssid_length = 0 tells firmware to perform
		 * specific scan for the SSID filled, whereas
		 * max_ssid_length = IEEE80211_MAX_SSID_LEN is for
		 * wildcard scan.
		 */
		if (ssid_len)
			wildcard_ssid_tlv->max_ssid_length = 0;
		else
			wildcard_ssid_tlv->max_ssid_length =
						IEEE80211_MAX_SSID_LEN;

		memcpy(wildcard_ssid_tlv->ssid,
		       bgscan_cfg_in->ssid_list[i].ssid.ssid, ssid_len);

		tlv_pos += (sizeof(wildcard_ssid_tlv->header)
				+ le16_to_cpu(wildcard_ssid_tlv->header.len));
	}

	chan_list_tlv = (struct mwifiex_ie_types_chan_list_param_set *)tlv_pos;

	if (bgscan_cfg_in->chan_list[0].chan_number) {
		dev_dbg(priv->adapter->dev, "info: bgscan: Using supplied channel list\n");

		chan_list_tlv->header.type = cpu_to_le16(TLV_TYPE_CHANLIST);

		for (chan_idx = 0;
		     chan_idx < MWIFIEX_BG_SCAN_CHAN_MAX &&
		     bgscan_cfg_in->chan_list[chan_idx].chan_number;
		     chan_idx++) {
			temp_chan = chan_list_tlv->chan_scan_param + chan_idx;

			/* Increment the TLV header length by size appended */
			le16_unaligned_add_cpu(&chan_list_tlv->header.len,
					       sizeof(
					       chan_list_tlv->chan_scan_param));

			temp_chan->chan_number =
				bgscan_cfg_in->chan_list[chan_idx].chan_number;
			temp_chan->radio_type =
				bgscan_cfg_in->chan_list[chan_idx].radio_type;

			scan_type =
				bgscan_cfg_in->chan_list[chan_idx].scan_type;

			if (scan_type == MWIFIEX_SCAN_TYPE_PASSIVE)
				temp_chan->chan_scan_mode_bitmap
					|= MWIFIEX_PASSIVE_SCAN;
			else
				temp_chan->chan_scan_mode_bitmap
					&= ~MWIFIEX_PASSIVE_SCAN;

			if (bgscan_cfg_in->chan_list[chan_idx].scan_time) {
				scan_dur = (u16)bgscan_cfg_in->
					chan_list[chan_idx].scan_time;
			} else {
				scan_dur = (scan_type ==
					    MWIFIEX_SCAN_TYPE_PASSIVE) ?
					    priv->adapter->passive_scan_time :
					    priv->adapter->specific_scan_time;
			}

			temp_chan->min_scan_time = cpu_to_le16(scan_dur);
			temp_chan->max_scan_time = cpu_to_le16(scan_dur);
		}
	} else {
		dev_dbg(priv->adapter->dev,
			"info: bgscan: Creating full region channel list\n");
		chan_num =
			mwifiex_bgscan_create_channel_list(priv, bgscan_cfg_in,
							   chan_list_tlv->
							   chan_scan_param);
		le16_unaligned_add_cpu(&chan_list_tlv->header.len,
				       chan_num *
			     sizeof(chan_list_tlv->chan_scan_param[0]));
	}

	tlv_pos += (sizeof(chan_list_tlv->header)
			+ le16_to_cpu(chan_list_tlv->header.len));

	if (bgscan_cfg_in->start_later) {
		start_later_tlv =
			(struct mwifiex_ie_types_bgscan_start_later *)tlv_pos;
		start_later_tlv->header.type =
			cpu_to_le16(TLV_TYPE_BGSCAN_START_LATER);
		start_later_tlv->header.len =
			cpu_to_le16(sizeof(start_later_tlv->start_later));
		start_later_tlv->start_later =
			cpu_to_le16(bgscan_cfg_in->start_later);

		tlv_pos += sizeof(start_later_tlv->header) +
			le16_to_cpu(start_later_tlv->header.len);
	}

	/* Append vendor specific IE TLV */
	mwifiex_cmd_append_vsie_tlv(priv, MWIFIEX_VSIE_MASK_BGSCAN, &tlv_pos);

	le16_unaligned_add_cpu(&cmd->size, tlv_pos - bgscan_config->tlv);

	return 0;
}