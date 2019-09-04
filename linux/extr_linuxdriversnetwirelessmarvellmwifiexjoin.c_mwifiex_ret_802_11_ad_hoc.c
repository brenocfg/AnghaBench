#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_13__ {int /*<<< orphan*/  mac_address; } ;
struct TYPE_10__ {TYPE_6__ bss_descriptor; } ;
struct mwifiex_private {int media_connected; int /*<<< orphan*/  netdev; TYPE_3__ curr_bss_params; struct mwifiex_adapter* adapter; int /*<<< orphan*/  adhoc_channel; int /*<<< orphan*/  adhoc_state; struct mwifiex_bssdescriptor* attempted_bss_desc; } ;
struct TYPE_9__ {int /*<<< orphan*/  ssid; } ;
struct mwifiex_bssdescriptor {TYPE_2__ ssid; TYPE_6__* mac_address; } ;
struct TYPE_12__ {int status; } ;
struct mwifiex_adapter {TYPE_5__ cmd_wait_q; TYPE_4__* curr_cmd; } ;
struct host_cmd_ds_802_11_ad_hoc_join_result {scalar_t__ result; } ;
struct host_cmd_ds_802_11_ad_hoc_start_result {struct mwifiex_bssdescriptor* bssid; scalar_t__ result; } ;
struct TYPE_8__ {struct host_cmd_ds_802_11_ad_hoc_join_result join_result; struct host_cmd_ds_802_11_ad_hoc_start_result start_result; } ;
struct host_cmd_ds_command {int /*<<< orphan*/  command; TYPE_1__ params; } ;
struct TYPE_11__ {scalar_t__ wait_q_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADHOC_JOINED ; 
 int /*<<< orphan*/  ADHOC_STARTED ; 
 int /*<<< orphan*/  ERROR ; 
 int ETH_ALEN ; 
 scalar_t__ HostCmd_CMD_802_11_AD_HOC_START ; 
 int /*<<< orphan*/  INFO ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,struct mwifiex_bssdescriptor*,int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mwifiex_reset_connect_state (struct mwifiex_private*,scalar_t__,int) ; 
 int /*<<< orphan*/  mwifiex_save_curr_bcn (struct mwifiex_private*) ; 
 int /*<<< orphan*/  mwifiex_wake_up_net_dev_queue (int /*<<< orphan*/ ,struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 

int mwifiex_ret_802_11_ad_hoc(struct mwifiex_private *priv,
			      struct host_cmd_ds_command *resp)
{
	int ret = 0;
	struct mwifiex_adapter *adapter = priv->adapter;
	struct host_cmd_ds_802_11_ad_hoc_start_result *start_result =
				&resp->params.start_result;
	struct host_cmd_ds_802_11_ad_hoc_join_result *join_result =
				&resp->params.join_result;
	struct mwifiex_bssdescriptor *bss_desc;
	u16 cmd = le16_to_cpu(resp->command);
	u8 result;

	if (!priv->attempted_bss_desc) {
		mwifiex_dbg(priv->adapter, ERROR,
			    "ADHOC_RESP: failed, association terminated by host\n");
		goto done;
	}

	if (cmd == HostCmd_CMD_802_11_AD_HOC_START)
		result = start_result->result;
	else
		result = join_result->result;

	bss_desc = priv->attempted_bss_desc;

	/* Join result code 0 --> SUCCESS */
	if (result) {
		mwifiex_dbg(priv->adapter, ERROR, "ADHOC_RESP: failed\n");
		if (priv->media_connected)
			mwifiex_reset_connect_state(priv, result, true);

		memset(&priv->curr_bss_params.bss_descriptor,
		       0x00, sizeof(struct mwifiex_bssdescriptor));

		ret = -1;
		goto done;
	}

	/* Send a Media Connected event, according to the Spec */
	priv->media_connected = true;

	if (le16_to_cpu(resp->command) == HostCmd_CMD_802_11_AD_HOC_START) {
		mwifiex_dbg(priv->adapter, INFO, "info: ADHOC_S_RESP %s\n",
			    bss_desc->ssid.ssid);

		/* Update the created network descriptor with the new BSSID */
		memcpy(bss_desc->mac_address,
		       start_result->bssid, ETH_ALEN);

		priv->adhoc_state = ADHOC_STARTED;
	} else {
		/*
		 * Now the join cmd should be successful.
		 * If BSSID has changed use SSID to compare instead of BSSID
		 */
		mwifiex_dbg(priv->adapter, INFO,
			    "info: ADHOC_J_RESP %s\n",
			    bss_desc->ssid.ssid);

		/*
		 * Make a copy of current BSSID descriptor, only needed for
		 * join since the current descriptor is already being used
		 * for adhoc start
		 */
		memcpy(&priv->curr_bss_params.bss_descriptor,
		       bss_desc, sizeof(struct mwifiex_bssdescriptor));

		priv->adhoc_state = ADHOC_JOINED;
	}

	mwifiex_dbg(priv->adapter, INFO, "info: ADHOC_RESP: channel = %d\n",
		    priv->adhoc_channel);
	mwifiex_dbg(priv->adapter, INFO, "info: ADHOC_RESP: BSSID = %pM\n",
		    priv->curr_bss_params.bss_descriptor.mac_address);

	if (!netif_carrier_ok(priv->netdev))
		netif_carrier_on(priv->netdev);
	mwifiex_wake_up_net_dev_queue(priv->netdev, adapter);

	mwifiex_save_curr_bcn(priv);

done:
	/* Need to indicate IOCTL complete */
	if (adapter->curr_cmd->wait_q_enabled) {
		if (ret)
			adapter->cmd_wait_q.status = -1;
		else
			adapter->cmd_wait_q.status = 0;

	}

	return ret;
}