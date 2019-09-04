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
typedef  scalar_t__ u8 ;
struct TYPE_5__ {scalar_t__ erp_flags; scalar_t__ beacon_period; int /*<<< orphan*/  mac_address; } ;
struct TYPE_6__ {TYPE_2__ bss_descriptor; } ;
struct mwifiex_private {int /*<<< orphan*/  adhoc_state; TYPE_3__ curr_bss_params; int /*<<< orphan*/  adapter; } ;
struct host_cmd_ds_802_11_ibss_status {int /*<<< orphan*/  use_g_rate_protect; int /*<<< orphan*/  beacon_interval; int /*<<< orphan*/  bssid; int /*<<< orphan*/  action; } ;
struct TYPE_4__ {struct host_cmd_ds_802_11_ibss_status ibss_coalescing; } ;
struct host_cmd_ds_command {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADHOC_COALESCED ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  FATAL ; 
 scalar_t__ HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int mwifiex_ret_ibss_coalescing_status(struct mwifiex_private *priv,
					      struct host_cmd_ds_command *resp)
{
	struct host_cmd_ds_802_11_ibss_status *ibss_coal_resp =
					&(resp->params.ibss_coalescing);

	if (le16_to_cpu(ibss_coal_resp->action) == HostCmd_ACT_GEN_SET)
		return 0;

	mwifiex_dbg(priv->adapter, INFO,
		    "info: new BSSID %pM\n", ibss_coal_resp->bssid);

	/* If rsp has NULL BSSID, Just return..... No Action */
	if (is_zero_ether_addr(ibss_coal_resp->bssid)) {
		mwifiex_dbg(priv->adapter, FATAL, "new BSSID is NULL\n");
		return 0;
	}

	/* If BSSID is diff, modify current BSS parameters */
	if (!ether_addr_equal(priv->curr_bss_params.bss_descriptor.mac_address, ibss_coal_resp->bssid)) {
		/* BSSID */
		memcpy(priv->curr_bss_params.bss_descriptor.mac_address,
		       ibss_coal_resp->bssid, ETH_ALEN);

		/* Beacon Interval */
		priv->curr_bss_params.bss_descriptor.beacon_period
			= le16_to_cpu(ibss_coal_resp->beacon_interval);

		/* ERP Information */
		priv->curr_bss_params.bss_descriptor.erp_flags =
			(u8) le16_to_cpu(ibss_coal_resp->use_g_rate_protect);

		priv->adhoc_state = ADHOC_COALESCED;
	}

	return 0;
}