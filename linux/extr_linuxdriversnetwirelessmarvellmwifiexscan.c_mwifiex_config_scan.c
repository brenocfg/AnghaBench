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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct mwifiex_user_scan_cfg {int* specific_bssid; int num_ssids; int scan_chan_gap; TYPE_8__* chan_list; int /*<<< orphan*/  random_mac; TYPE_1__* ssid_list; scalar_t__ num_probes; scalar_t__ bss_mode; } ;
struct mwifiex_scan_cmd_config {int* tlv_buf; int bss_mode; int* specific_bssid; scalar_t__ tlv_buf_len; } ;
struct TYPE_22__ {scalar_t__ channel; } ;
struct TYPE_12__ {TYPE_9__ bss_descriptor; } ;
struct mwifiex_private {TYPE_10__ curr_bss_params; struct mwifiex_adapter* adapter; int /*<<< orphan*/  media_connected; } ;
struct TYPE_15__ {void* len; void* type; } ;
struct mwifiex_ie_types_wildcard_ssid_params {int max_ssid_length; int* ssid; TYPE_2__ header; } ;
struct TYPE_16__ {void* len; void* type; } ;
struct mwifiex_ie_types_scan_chan_gap {void* chan_gap; TYPE_3__ header; } ;
struct TYPE_17__ {void* len; void* type; } ;
struct mwifiex_ie_types_random_mac {int /*<<< orphan*/  mac; TYPE_4__ header; } ;
struct TYPE_19__ {void* len; void* type; } ;
struct mwifiex_ie_types_num_probes {TYPE_6__ header; void* num_probes; } ;
struct TYPE_20__ {void* len; void* type; } ;
struct mwifiex_ie_types_htcap {int /*<<< orphan*/  ht_cap; TYPE_7__ header; } ;
struct mwifiex_ie_types_chan_list_param_set {int dummy; } ;
struct TYPE_13__ {void* len; void* type; } ;
struct mwifiex_ie_types_bssid_list {int* bssid; TYPE_11__ header; } ;
struct TYPE_18__ {void* len; void* type; } ;
struct mwifiex_ie_types_bss_mode {int bss_mode; TYPE_5__ header; } ;
struct mwifiex_chan_scan_param_set {int chan_number; int radio_type; int chan_scan_mode_bitmap; void* max_scan_time; void* min_scan_time; } ;
struct mwifiex_adapter {int scan_probes; int config_bands; int passive_scan_time; int specific_scan_time; int active_scan_time; int /*<<< orphan*/  fw_cap_info; scalar_t__ ext_scan; scalar_t__ scan_mode; } ;
struct ieee80211_ht_cap {int dummy; } ;
struct TYPE_21__ {int chan_number; int radio_type; int scan_type; scalar_t__ scan_time; } ;
struct TYPE_14__ {int ssid_len; int* ssid; } ;

/* Variables and functions */
 int BAND_AN ; 
 int BAND_GN ; 
 int ETH_ALEN ; 
 int IEEE80211_MAX_SSID_LEN ; 
 int /*<<< orphan*/  INFO ; 
 scalar_t__ ISSUPP_11NENABLED (int /*<<< orphan*/ ) ; 
 int MWIFIEX_DEF_CHANNELS_PER_SCAN_CMD ; 
 int MWIFIEX_DISABLE_CHAN_FILT ; 
 int MWIFIEX_HIDDEN_SSID_REPORT ; 
 int MWIFIEX_MAX_CHANNELS_PER_SPECIFIC_SCAN ; 
 int MWIFIEX_PASSIVE_SCAN ; 
 int MWIFIEX_SCAN_TYPE_PASSIVE ; 
 int MWIFIEX_USER_SCAN_CHAN_MAX ; 
 int /*<<< orphan*/  MWIFIEX_VSIE_MASK_SCAN ; 
 int TLV_TYPE_BSSID ; 
 int TLV_TYPE_BSS_MODE ; 
 int TLV_TYPE_NUMPROBES ; 
 int TLV_TYPE_RANDOM_MAC ; 
 int TLV_TYPE_SCAN_CHANNEL_GAP ; 
 int TLV_TYPE_WILDCARDSSID ; 
 int WLAN_EID_HT_CAPABILITY ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int const*) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int*) ; 
 scalar_t__ le16_to_cpu (void*) ; 
 int /*<<< orphan*/  memcmp (int*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (struct mwifiex_ie_types_htcap*,int /*<<< orphan*/ ,int) ; 
 int mwifiex_band_to_radio_type (int) ; 
 int /*<<< orphan*/  mwifiex_cmd_append_vsie_tlv (struct mwifiex_private*,int /*<<< orphan*/ ,int**) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mwifiex_fill_cap_info (struct mwifiex_private*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwifiex_scan_create_channel_list (struct mwifiex_private*,struct mwifiex_user_scan_cfg const*,struct mwifiex_chan_scan_param_set*,int) ; 

__attribute__((used)) static void
mwifiex_config_scan(struct mwifiex_private *priv,
		    const struct mwifiex_user_scan_cfg *user_scan_in,
		    struct mwifiex_scan_cmd_config *scan_cfg_out,
		    struct mwifiex_ie_types_chan_list_param_set **chan_list_out,
		    struct mwifiex_chan_scan_param_set *scan_chan_list,
		    u8 *max_chan_per_scan, u8 *filtered_scan,
		    u8 *scan_current_only)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	struct mwifiex_ie_types_num_probes *num_probes_tlv;
	struct mwifiex_ie_types_scan_chan_gap *chan_gap_tlv;
	struct mwifiex_ie_types_random_mac *random_mac_tlv;
	struct mwifiex_ie_types_wildcard_ssid_params *wildcard_ssid_tlv;
	struct mwifiex_ie_types_bssid_list *bssid_tlv;
	u8 *tlv_pos;
	u32 num_probes;
	u32 ssid_len;
	u32 chan_idx;
	u32 scan_type;
	u16 scan_dur;
	u8 channel;
	u8 radio_type;
	int i;
	u8 ssid_filter;
	struct mwifiex_ie_types_htcap *ht_cap;
	struct mwifiex_ie_types_bss_mode *bss_mode;
	const u8 zero_mac[6] = {0, 0, 0, 0, 0, 0};

	/* The tlv_buf_len is calculated for each scan command.  The TLVs added
	   in this routine will be preserved since the routine that sends the
	   command will append channelTLVs at *chan_list_out.  The difference
	   between the *chan_list_out and the tlv_buf start will be used to
	   calculate the size of anything we add in this routine. */
	scan_cfg_out->tlv_buf_len = 0;

	/* Running tlv pointer.  Assigned to chan_list_out at end of function
	   so later routines know where channels can be added to the command
	   buf */
	tlv_pos = scan_cfg_out->tlv_buf;

	/* Initialize the scan as un-filtered; the flag is later set to TRUE
	   below if a SSID or BSSID filter is sent in the command */
	*filtered_scan = false;

	/* Initialize the scan as not being only on the current channel.  If
	   the channel list is customized, only contains one channel, and is
	   the active channel, this is set true and data flow is not halted. */
	*scan_current_only = false;

	if (user_scan_in) {
		u8 tmpaddr[ETH_ALEN];

		/* Default the ssid_filter flag to TRUE, set false under
		   certain wildcard conditions and qualified by the existence
		   of an SSID list before marking the scan as filtered */
		ssid_filter = true;

		/* Set the BSS type scan filter, use Adapter setting if
		   unset */
		scan_cfg_out->bss_mode =
			(u8)(user_scan_in->bss_mode ?: adapter->scan_mode);

		/* Set the number of probes to send, use Adapter setting
		   if unset */
		num_probes = user_scan_in->num_probes ?: adapter->scan_probes;

		/*
		 * Set the BSSID filter to the incoming configuration,
		 * if non-zero.  If not set, it will remain disabled
		 * (all zeros).
		 */
		memcpy(scan_cfg_out->specific_bssid,
		       user_scan_in->specific_bssid,
		       sizeof(scan_cfg_out->specific_bssid));

		memcpy(tmpaddr, scan_cfg_out->specific_bssid, ETH_ALEN);

		if (adapter->ext_scan &&
		    !is_zero_ether_addr(tmpaddr)) {
			bssid_tlv =
				(struct mwifiex_ie_types_bssid_list *)tlv_pos;
			bssid_tlv->header.type = cpu_to_le16(TLV_TYPE_BSSID);
			bssid_tlv->header.len = cpu_to_le16(ETH_ALEN);
			memcpy(bssid_tlv->bssid, user_scan_in->specific_bssid,
			       ETH_ALEN);
			tlv_pos += sizeof(struct mwifiex_ie_types_bssid_list);
		}

		for (i = 0; i < user_scan_in->num_ssids; i++) {
			ssid_len = user_scan_in->ssid_list[i].ssid_len;

			wildcard_ssid_tlv =
				(struct mwifiex_ie_types_wildcard_ssid_params *)
				tlv_pos;
			wildcard_ssid_tlv->header.type =
				cpu_to_le16(TLV_TYPE_WILDCARDSSID);
			wildcard_ssid_tlv->header.len = cpu_to_le16(
				(u16) (ssid_len + sizeof(wildcard_ssid_tlv->
							 max_ssid_length)));

			/*
			 * max_ssid_length = 0 tells firmware to perform
			 * specific scan for the SSID filled, whereas
			 * max_ssid_length = IEEE80211_MAX_SSID_LEN is for
			 * wildcard scan.
			 */
			if (ssid_len)
				wildcard_ssid_tlv->max_ssid_length = 0;
			else
				wildcard_ssid_tlv->max_ssid_length =
							IEEE80211_MAX_SSID_LEN;

			if (!memcmp(user_scan_in->ssid_list[i].ssid,
				    "DIRECT-", 7))
				wildcard_ssid_tlv->max_ssid_length = 0xfe;

			memcpy(wildcard_ssid_tlv->ssid,
			       user_scan_in->ssid_list[i].ssid, ssid_len);

			tlv_pos += (sizeof(wildcard_ssid_tlv->header)
				+ le16_to_cpu(wildcard_ssid_tlv->header.len));

			mwifiex_dbg(adapter, INFO,
				    "info: scan: ssid[%d]: %s, %d\n",
				    i, wildcard_ssid_tlv->ssid,
				    wildcard_ssid_tlv->max_ssid_length);

			/* Empty wildcard ssid with a maxlen will match many or
			   potentially all SSIDs (maxlen == 32), therefore do
			   not treat the scan as
			   filtered. */
			if (!ssid_len && wildcard_ssid_tlv->max_ssid_length)
				ssid_filter = false;
		}

		/*
		 *  The default number of channels sent in the command is low to
		 *  ensure the response buffer from the firmware does not
		 *  truncate scan results.  That is not an issue with an SSID
		 *  or BSSID filter applied to the scan results in the firmware.
		 */
		memcpy(tmpaddr, scan_cfg_out->specific_bssid, ETH_ALEN);
		if ((i && ssid_filter) ||
		    !is_zero_ether_addr(tmpaddr))
			*filtered_scan = true;

		if (user_scan_in->scan_chan_gap) {
			mwifiex_dbg(adapter, INFO,
				    "info: scan: channel gap = %d\n",
				    user_scan_in->scan_chan_gap);
			*max_chan_per_scan =
					MWIFIEX_MAX_CHANNELS_PER_SPECIFIC_SCAN;

			chan_gap_tlv = (void *)tlv_pos;
			chan_gap_tlv->header.type =
					 cpu_to_le16(TLV_TYPE_SCAN_CHANNEL_GAP);
			chan_gap_tlv->header.len =
				    cpu_to_le16(sizeof(chan_gap_tlv->chan_gap));
			chan_gap_tlv->chan_gap =
				     cpu_to_le16((user_scan_in->scan_chan_gap));
			tlv_pos +=
				  sizeof(struct mwifiex_ie_types_scan_chan_gap);
		}

		if (!ether_addr_equal(user_scan_in->random_mac, zero_mac)) {
			random_mac_tlv = (void *)tlv_pos;
			random_mac_tlv->header.type =
					 cpu_to_le16(TLV_TYPE_RANDOM_MAC);
			random_mac_tlv->header.len =
				    cpu_to_le16(sizeof(random_mac_tlv->mac));
			ether_addr_copy(random_mac_tlv->mac,
					user_scan_in->random_mac);
			tlv_pos +=
				  sizeof(struct mwifiex_ie_types_random_mac);
		}
	} else {
		scan_cfg_out->bss_mode = (u8) adapter->scan_mode;
		num_probes = adapter->scan_probes;
	}

	/*
	 *  If a specific BSSID or SSID is used, the number of channels in the
	 *  scan command will be increased to the absolute maximum.
	 */
	if (*filtered_scan) {
		*max_chan_per_scan = MWIFIEX_MAX_CHANNELS_PER_SPECIFIC_SCAN;
	} else {
		if (!priv->media_connected)
			*max_chan_per_scan = MWIFIEX_DEF_CHANNELS_PER_SCAN_CMD;
		else
			*max_chan_per_scan =
					MWIFIEX_DEF_CHANNELS_PER_SCAN_CMD / 2;
	}

	if (adapter->ext_scan) {
		bss_mode = (struct mwifiex_ie_types_bss_mode *)tlv_pos;
		bss_mode->header.type = cpu_to_le16(TLV_TYPE_BSS_MODE);
		bss_mode->header.len = cpu_to_le16(sizeof(bss_mode->bss_mode));
		bss_mode->bss_mode = scan_cfg_out->bss_mode;
		tlv_pos += sizeof(bss_mode->header) +
			   le16_to_cpu(bss_mode->header.len);
	}

	/* If the input config or adapter has the number of Probes set,
	   add tlv */
	if (num_probes) {

		mwifiex_dbg(adapter, INFO,
			    "info: scan: num_probes = %d\n",
			    num_probes);

		num_probes_tlv = (struct mwifiex_ie_types_num_probes *) tlv_pos;
		num_probes_tlv->header.type = cpu_to_le16(TLV_TYPE_NUMPROBES);
		num_probes_tlv->header.len =
			cpu_to_le16(sizeof(num_probes_tlv->num_probes));
		num_probes_tlv->num_probes = cpu_to_le16((u16) num_probes);

		tlv_pos += sizeof(num_probes_tlv->header) +
			le16_to_cpu(num_probes_tlv->header.len);

	}

	if (ISSUPP_11NENABLED(priv->adapter->fw_cap_info) &&
	    (priv->adapter->config_bands & BAND_GN ||
	     priv->adapter->config_bands & BAND_AN)) {
		ht_cap = (struct mwifiex_ie_types_htcap *) tlv_pos;
		memset(ht_cap, 0, sizeof(struct mwifiex_ie_types_htcap));
		ht_cap->header.type = cpu_to_le16(WLAN_EID_HT_CAPABILITY);
		ht_cap->header.len =
				cpu_to_le16(sizeof(struct ieee80211_ht_cap));
		radio_type =
			mwifiex_band_to_radio_type(priv->adapter->config_bands);
		mwifiex_fill_cap_info(priv, radio_type, &ht_cap->ht_cap);
		tlv_pos += sizeof(struct mwifiex_ie_types_htcap);
	}

	/* Append vendor specific IE TLV */
	mwifiex_cmd_append_vsie_tlv(priv, MWIFIEX_VSIE_MASK_SCAN, &tlv_pos);

	/*
	 * Set the output for the channel TLV to the address in the tlv buffer
	 *   past any TLVs that were added in this function (SSID, num_probes).
	 *   Channel TLVs will be added past this for each scan command,
	 *   preserving the TLVs that were previously added.
	 */
	*chan_list_out =
		(struct mwifiex_ie_types_chan_list_param_set *) tlv_pos;

	if (user_scan_in && user_scan_in->chan_list[0].chan_number) {

		mwifiex_dbg(adapter, INFO,
			    "info: Scan: Using supplied channel list\n");

		for (chan_idx = 0;
		     chan_idx < MWIFIEX_USER_SCAN_CHAN_MAX &&
		     user_scan_in->chan_list[chan_idx].chan_number;
		     chan_idx++) {

			channel = user_scan_in->chan_list[chan_idx].chan_number;
			scan_chan_list[chan_idx].chan_number = channel;

			radio_type =
				user_scan_in->chan_list[chan_idx].radio_type;
			scan_chan_list[chan_idx].radio_type = radio_type;

			scan_type = user_scan_in->chan_list[chan_idx].scan_type;

			if (scan_type == MWIFIEX_SCAN_TYPE_PASSIVE)
				scan_chan_list[chan_idx].chan_scan_mode_bitmap
					|= (MWIFIEX_PASSIVE_SCAN |
					    MWIFIEX_HIDDEN_SSID_REPORT);
			else
				scan_chan_list[chan_idx].chan_scan_mode_bitmap
					&= ~MWIFIEX_PASSIVE_SCAN;

			scan_chan_list[chan_idx].chan_scan_mode_bitmap
				|= MWIFIEX_DISABLE_CHAN_FILT;

			if (user_scan_in->chan_list[chan_idx].scan_time) {
				scan_dur = (u16) user_scan_in->
					chan_list[chan_idx].scan_time;
			} else {
				if (scan_type == MWIFIEX_SCAN_TYPE_PASSIVE)
					scan_dur = adapter->passive_scan_time;
				else if (*filtered_scan)
					scan_dur = adapter->specific_scan_time;
				else
					scan_dur = adapter->active_scan_time;
			}

			scan_chan_list[chan_idx].min_scan_time =
				cpu_to_le16(scan_dur);
			scan_chan_list[chan_idx].max_scan_time =
				cpu_to_le16(scan_dur);
		}

		/* Check if we are only scanning the current channel */
		if ((chan_idx == 1) &&
		    (user_scan_in->chan_list[0].chan_number ==
		     priv->curr_bss_params.bss_descriptor.channel)) {
			*scan_current_only = true;
			mwifiex_dbg(adapter, INFO,
				    "info: Scan: Scanning current channel only\n");
		}
	} else {
		mwifiex_dbg(adapter, INFO,
			    "info: Scan: Creating full region channel list\n");
		mwifiex_scan_create_channel_list(priv, user_scan_in,
						 scan_chan_list,
						 *filtered_scan);
	}

}