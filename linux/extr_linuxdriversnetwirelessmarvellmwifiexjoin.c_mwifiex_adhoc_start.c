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
struct TYPE_5__ {int /*<<< orphan*/  channel; } ;
struct TYPE_4__ {int /*<<< orphan*/  band; TYPE_2__ bss_descriptor; } ;
struct mwifiex_private {TYPE_3__* adapter; TYPE_1__ curr_bss_params; int /*<<< orphan*/  adhoc_channel; } ;
struct cfg80211_ssid {int dummy; } ;
struct TYPE_6__ {int config_bands; int /*<<< orphan*/  fw_cap_info; } ;

/* Variables and functions */
 int BAND_AAC ; 
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  HostCmd_CMD_802_11_AD_HOC_START ; 
 int /*<<< orphan*/  INFO ; 
 scalar_t__ ISSUPP_11ACENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfg80211_ssid*,int) ; 
 int /*<<< orphan*/  mwifiex_set_11ac_ba_params (struct mwifiex_private*) ; 
 int /*<<< orphan*/  mwifiex_set_ba_params (struct mwifiex_private*) ; 

int
mwifiex_adhoc_start(struct mwifiex_private *priv,
		    struct cfg80211_ssid *adhoc_ssid)
{
	mwifiex_dbg(priv->adapter, INFO, "info: Adhoc Channel = %d\n",
		    priv->adhoc_channel);
	mwifiex_dbg(priv->adapter, INFO, "info: curr_bss_params.channel = %d\n",
		    priv->curr_bss_params.bss_descriptor.channel);
	mwifiex_dbg(priv->adapter, INFO, "info: curr_bss_params.band = %d\n",
		    priv->curr_bss_params.band);

	if (ISSUPP_11ACENABLED(priv->adapter->fw_cap_info) &&
	    priv->adapter->config_bands & BAND_AAC)
		mwifiex_set_11ac_ba_params(priv);
	else
		mwifiex_set_ba_params(priv);

	return mwifiex_send_cmd(priv, HostCmd_CMD_802_11_AD_HOC_START,
				HostCmd_ACT_GEN_SET, 0, adhoc_ssid, true);
}