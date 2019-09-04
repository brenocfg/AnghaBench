#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct mwifiex_scan_cmd_config {scalar_t__ tlv_buf_len; scalar_t__* tlv_buf; } ;
struct mwifiex_private {int csa_chan; struct mwifiex_adapter* adapter; } ;
struct mwifiex_ie_types_header {int dummy; } ;
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/  type; } ;
struct mwifiex_ie_types_chan_list_param_set {scalar_t__ chan_scan_param; TYPE_1__ header; } ;
struct mwifiex_chan_scan_param_set {int chan_number; int chan_scan_mode_bitmap; scalar_t__ max_scan_time; scalar_t__ radio_type; } ;
struct mwifiex_adapter {scalar_t__ ext_scan; struct mwifiex_chan_scan_param_set* scan_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 scalar_t__ HostCmd_CMD_802_11_SCAN ; 
 scalar_t__ HostCmd_CMD_802_11_SCAN_EXT ; 
 int /*<<< orphan*/  INFO ; 
 int MWIFIEX_DISABLE_CHAN_FILT ; 
 scalar_t__ MWIFIEX_MAX_TOTAL_SCAN_TIME ; 
 int MWIFIEX_PASSIVE_SCAN ; 
 int /*<<< orphan*/  TLV_TYPE_CHANLIST ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le16_unaligned_add_cpu (scalar_t__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct mwifiex_chan_scan_param_set*,int) ; 
 int /*<<< orphan*/  mwifiex_11h_get_csa_closed_channel (struct mwifiex_private*) ; 
 scalar_t__ mwifiex_append_rate_tlv (struct mwifiex_private*,struct mwifiex_scan_cmd_config*,scalar_t__) ; 
 int /*<<< orphan*/  mwifiex_cancel_pending_scan_cmd (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,...) ; 
 int mwifiex_send_cmd (struct mwifiex_private*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mwifiex_scan_cmd_config*,int) ; 

__attribute__((used)) static int
mwifiex_scan_channel_list(struct mwifiex_private *priv,
			  u32 max_chan_per_scan, u8 filtered_scan,
			  struct mwifiex_scan_cmd_config *scan_cfg_out,
			  struct mwifiex_ie_types_chan_list_param_set
			  *chan_tlv_out,
			  struct mwifiex_chan_scan_param_set *scan_chan_list)
{
	struct mwifiex_adapter *adapter = priv->adapter;
	int ret = 0;
	struct mwifiex_chan_scan_param_set *tmp_chan_list;
	struct mwifiex_chan_scan_param_set *start_chan;
	u32 tlv_idx, rates_size, cmd_no;
	u32 total_scan_time;
	u32 done_early;
	u8 radio_type;

	if (!scan_cfg_out || !chan_tlv_out || !scan_chan_list) {
		mwifiex_dbg(priv->adapter, ERROR,
			    "info: Scan: Null detect: %p, %p, %p\n",
			    scan_cfg_out, chan_tlv_out, scan_chan_list);
		return -1;
	}

	/* Check csa channel expiry before preparing scan list */
	mwifiex_11h_get_csa_closed_channel(priv);

	chan_tlv_out->header.type = cpu_to_le16(TLV_TYPE_CHANLIST);

	/* Set the temp channel struct pointer to the start of the desired
	   list */
	tmp_chan_list = scan_chan_list;

	/* Loop through the desired channel list, sending a new firmware scan
	   commands for each max_chan_per_scan channels (or for 1,6,11
	   individually if configured accordingly) */
	while (tmp_chan_list->chan_number) {

		tlv_idx = 0;
		total_scan_time = 0;
		radio_type = 0;
		chan_tlv_out->header.len = 0;
		start_chan = tmp_chan_list;
		done_early = false;

		/*
		 * Construct the Channel TLV for the scan command.  Continue to
		 * insert channel TLVs until:
		 *   - the tlv_idx hits the maximum configured per scan command
		 *   - the next channel to insert is 0 (end of desired channel
		 *     list)
		 *   - done_early is set (controlling individual scanning of
		 *     1,6,11)
		 */
		while (tlv_idx < max_chan_per_scan &&
		       tmp_chan_list->chan_number && !done_early) {

			if (tmp_chan_list->chan_number == priv->csa_chan) {
				tmp_chan_list++;
				continue;
			}

			radio_type = tmp_chan_list->radio_type;
			mwifiex_dbg(priv->adapter, INFO,
				    "info: Scan: Chan(%3d), Radio(%d),\t"
				    "Mode(%d, %d), Dur(%d)\n",
				    tmp_chan_list->chan_number,
				    tmp_chan_list->radio_type,
				    tmp_chan_list->chan_scan_mode_bitmap
				    & MWIFIEX_PASSIVE_SCAN,
				    (tmp_chan_list->chan_scan_mode_bitmap
				    & MWIFIEX_DISABLE_CHAN_FILT) >> 1,
				    le16_to_cpu(tmp_chan_list->max_scan_time));

			/* Copy the current channel TLV to the command being
			   prepared */
			memcpy(chan_tlv_out->chan_scan_param + tlv_idx,
			       tmp_chan_list,
			       sizeof(chan_tlv_out->chan_scan_param));

			/* Increment the TLV header length by the size
			   appended */
			le16_unaligned_add_cpu(&chan_tlv_out->header.len,
					       sizeof(
						chan_tlv_out->chan_scan_param));

			/*
			 * The tlv buffer length is set to the number of bytes
			 * of the between the channel tlv pointer and the start
			 * of the tlv buffer.  This compensates for any TLVs
			 * that were appended before the channel list.
			 */
			scan_cfg_out->tlv_buf_len = (u32) ((u8 *) chan_tlv_out -
							scan_cfg_out->tlv_buf);

			/* Add the size of the channel tlv header and the data
			   length */
			scan_cfg_out->tlv_buf_len +=
				(sizeof(chan_tlv_out->header)
				 + le16_to_cpu(chan_tlv_out->header.len));

			/* Increment the index to the channel tlv we are
			   constructing */
			tlv_idx++;

			/* Count the total scan time per command */
			total_scan_time +=
				le16_to_cpu(tmp_chan_list->max_scan_time);

			done_early = false;

			/* Stop the loop if the *current* channel is in the
			   1,6,11 set and we are not filtering on a BSSID
			   or SSID. */
			if (!filtered_scan &&
			    (tmp_chan_list->chan_number == 1 ||
			     tmp_chan_list->chan_number == 6 ||
			     tmp_chan_list->chan_number == 11))
				done_early = true;

			/* Increment the tmp pointer to the next channel to
			   be scanned */
			tmp_chan_list++;

			/* Stop the loop if the *next* channel is in the 1,6,11
			   set.  This will cause it to be the only channel
			   scanned on the next interation */
			if (!filtered_scan &&
			    (tmp_chan_list->chan_number == 1 ||
			     tmp_chan_list->chan_number == 6 ||
			     tmp_chan_list->chan_number == 11))
				done_early = true;
		}

		/* The total scan time should be less than scan command timeout
		   value */
		if (total_scan_time > MWIFIEX_MAX_TOTAL_SCAN_TIME) {
			mwifiex_dbg(priv->adapter, ERROR,
				    "total scan time %dms\t"
				    "is over limit (%dms), scan skipped\n",
				    total_scan_time,
				    MWIFIEX_MAX_TOTAL_SCAN_TIME);
			ret = -1;
			break;
		}

		rates_size = mwifiex_append_rate_tlv(priv, scan_cfg_out,
						     radio_type);

		priv->adapter->scan_channels = start_chan;

		/* Send the scan command to the firmware with the specified
		   cfg */
		if (priv->adapter->ext_scan)
			cmd_no = HostCmd_CMD_802_11_SCAN_EXT;
		else
			cmd_no = HostCmd_CMD_802_11_SCAN;

		ret = mwifiex_send_cmd(priv, cmd_no, HostCmd_ACT_GEN_SET,
				       0, scan_cfg_out, false);

		/* rate IE is updated per scan command but same starting
		 * pointer is used each time so that rate IE from earlier
		 * scan_cfg_out->buf is overwritten with new one.
		 */
		scan_cfg_out->tlv_buf_len -=
			    sizeof(struct mwifiex_ie_types_header) + rates_size;

		if (ret) {
			mwifiex_cancel_pending_scan_cmd(adapter);
			break;
		}
	}

	if (ret)
		return -1;

	return 0;
}