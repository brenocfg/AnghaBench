#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct lbs_private {int /*<<< orphan*/  fwrelease; } ;
struct TYPE_11__ {int len; int /*<<< orphan*/  id; } ;
struct TYPE_12__ {int /*<<< orphan*/  channel; TYPE_4__ header; } ;
struct TYPE_9__ {int len; int /*<<< orphan*/  id; } ;
struct TYPE_10__ {scalar_t__ atimwindow; TYPE_2__ header; } ;
struct TYPE_8__ {void* size; } ;
struct cmd_ds_802_11_ad_hoc_start {int /*<<< orphan*/  rates; void* capability; void* probedelay; TYPE_5__ ds; TYPE_3__ ibss; void* beaconperiod; int /*<<< orphan*/  bsstype; int /*<<< orphan*/  ssid; TYPE_1__ hdr; } ;
struct cmd_ds_802_11_ad_hoc_result {int /*<<< orphan*/  bssid; } ;
struct TYPE_14__ {TYPE_6__* chan; } ;
struct cfg80211_ibss_params {int beacon_interval; TYPE_7__ chandef; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_13__ {int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_AD_HOC_START ; 
 int /*<<< orphan*/  CMD_BSS_TYPE_IBSS ; 
 int CMD_SCAN_PROBE_DELAY_TIME ; 
 int MRVL_FW_MAJOR_REV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADIO_PREAMBLE_SHORT ; 
 int WLAN_CAPABILITY_IBSS ; 
 int /*<<< orphan*/  WLAN_EID_DS_PARAMS ; 
 int /*<<< orphan*/  WLAN_EID_IBSS_PARAMS ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  lbs_add_rates (int /*<<< orphan*/ ) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_802_11_ad_hoc_start*) ; 
 int /*<<< orphan*/  lbs_join_post (struct lbs_private*,struct cfg80211_ibss_params*,int /*<<< orphan*/ ,int) ; 
 int lbs_set_radio (struct lbs_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_802_11_ad_hoc_start*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lbs_ibss_start_new(struct lbs_private *priv,
	struct cfg80211_ibss_params *params)
{
	struct cmd_ds_802_11_ad_hoc_start cmd;
	struct cmd_ds_802_11_ad_hoc_result *resp =
		(struct cmd_ds_802_11_ad_hoc_result *) &cmd;
	u8 preamble = RADIO_PREAMBLE_SHORT;
	int ret = 0;
	u16 capability;

	ret = lbs_set_radio(priv, preamble, 1);
	if (ret)
		goto out;

	/*
	 * Example CMD_802_11_AD_HOC_START command:
	 *
	 * command         2b 00         CMD_802_11_AD_HOC_START
	 * size            b1 00
	 * sequence        xx xx
	 * result          00 00
	 * ssid            54 45 53 54 00 00 00 00
	 *                 00 00 00 00 00 00 00 00
	 *                 00 00 00 00 00 00 00 00
	 *                 00 00 00 00 00 00 00 00
	 * bss type        02
	 * beacon period   64 00
	 * dtim period     00
	 * IE IBSS         06
	 * IE IBSS len     02
	 * IE IBSS atim    00 00
	 * reserved        00 00 00 00
	 * IE DS           03
	 * IE DS len       01
	 * IE DS channel   01
	 * reserved        00 00 00 00
	 * probe delay     00 00
	 * capability      02 00
	 * rates           82 84 8b 96   (basic rates with have bit 7 set)
	 *                 0c 12 18 24 30 48 60 6c
	 * padding         100 bytes
	 */
	memset(&cmd, 0, sizeof(cmd));
	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	memcpy(cmd.ssid, params->ssid, params->ssid_len);
	cmd.bsstype = CMD_BSS_TYPE_IBSS;
	cmd.beaconperiod = cpu_to_le16(params->beacon_interval);
	cmd.ibss.header.id = WLAN_EID_IBSS_PARAMS;
	cmd.ibss.header.len = 2;
	cmd.ibss.atimwindow = 0;
	cmd.ds.header.id = WLAN_EID_DS_PARAMS;
	cmd.ds.header.len = 1;
	cmd.ds.channel = params->chandef.chan->hw_value;
	/* Only v8 and below support setting probe delay */
	if (MRVL_FW_MAJOR_REV(priv->fwrelease) <= 8)
		cmd.probedelay = cpu_to_le16(CMD_SCAN_PROBE_DELAY_TIME);
	/* TODO: mix in WLAN_CAPABILITY_PRIVACY */
	capability = WLAN_CAPABILITY_IBSS;
	cmd.capability = cpu_to_le16(capability);
	lbs_add_rates(cmd.rates);


	ret = lbs_cmd_with_response(priv, CMD_802_11_AD_HOC_START, &cmd);
	if (ret)
		goto out;

	/*
	 * This is a sample response to CMD_802_11_AD_HOC_JOIN:
	 *
	 * response        2b 80
	 * size            14 00
	 * sequence        xx xx
	 * result          00 00
	 * reserved        00
	 * bssid           02 2b 7b 0f 86 0e
	 */
	lbs_join_post(priv, params, resp->bssid, capability);

 out:
	return ret;
}