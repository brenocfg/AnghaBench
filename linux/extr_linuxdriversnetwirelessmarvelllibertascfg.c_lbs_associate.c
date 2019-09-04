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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct lbs_private {int /*<<< orphan*/  dev; int /*<<< orphan*/  tx_pending_len; int /*<<< orphan*/  connect_status; int /*<<< orphan*/  assoc_bss; int /*<<< orphan*/  fwrelease; } ;
struct TYPE_6__ {void* size; } ;
struct cmd_ds_802_11_associate_response {int /*<<< orphan*/  iebuf; TYPE_3__ hdr; void* aid; void* capability; void* statuscode; } ;
struct TYPE_5__ {void* size; void* command; } ;
struct cmd_ds_802_11_associate {TYPE_2__ hdr; int /*<<< orphan*/ * iebuf; void* capability; void* listeninterval; int /*<<< orphan*/  bssid; } ;
struct cfg80211_connect_params {int /*<<< orphan*/  ie_len; int /*<<< orphan*/  ie; int /*<<< orphan*/  auth_type; } ;
struct cfg80211_bss {size_t capability; int /*<<< orphan*/  bssid; TYPE_1__* channel; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 size_t CMD_802_11_ASSOCIATE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LBS_ASSOC_MAX_CMD_SIZE ; 
 int /*<<< orphan*/  LBS_CONNECTED ; 
 int /*<<< orphan*/  LBS_DEB_ASSOC ; 
 size_t MRVDRV_DEFAULT_LISTEN_INTERVAL ; 
 int MRVL_FW_MAJOR_REV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 int WLAN_STATUS_ASSOC_DENIED_UNSPEC ; 
 int WLAN_STATUS_AUTH_TIMEOUT ; 
 int WLAN_STATUS_CAPS_UNSUPPORTED ; 
 int WLAN_STATUS_UNKNOWN_AUTH_TRANSACTION ; 
 int /*<<< orphan*/  cfg80211_connect_result (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (size_t) ; 
 int /*<<< orphan*/ * ieee80211_bss_get_ie (struct cfg80211_bss*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmd_ds_802_11_associate*) ; 
 struct cmd_ds_802_11_associate* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_add_auth_type_tlv (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_add_cf_param_tlv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lbs_add_channel_tlv (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_add_common_rates_tlv (int /*<<< orphan*/ *,struct cfg80211_bss*) ; 
 int /*<<< orphan*/  lbs_add_ssid_tlv (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  lbs_add_wpa_tlv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lbs_cmd_with_response (struct lbs_private*,size_t,struct cmd_ds_802_11_associate*) ; 
 int /*<<< orphan*/  lbs_deb_assoc (char*,...) ; 
 int /*<<< orphan*/  lbs_deb_hex (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int le16_to_cpu (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int lbs_associate(struct lbs_private *priv,
		struct cfg80211_bss *bss,
		struct cfg80211_connect_params *sme)
{
	struct cmd_ds_802_11_associate_response *resp;
	struct cmd_ds_802_11_associate *cmd = kzalloc(LBS_ASSOC_MAX_CMD_SIZE,
						      GFP_KERNEL);
	const u8 *ssid_eid;
	size_t len, resp_ie_len;
	int status;
	int ret;
	u8 *pos;
	u8 *tmp;

	if (!cmd) {
		ret = -ENOMEM;
		goto done;
	}
	pos = &cmd->iebuf[0];

	/*
	 * cmd              50 00
	 * length           34 00
	 * sequence         xx xx
	 * result           00 00
	 * BSS id           00 13 19 80 da 30
	 * capabilities     11 00
	 * listen interval  0a 00
	 * beacon interval  00 00
	 * DTIM period      00
	 * TLVs             xx   (up to 512 bytes)
	 */
	cmd->hdr.command = cpu_to_le16(CMD_802_11_ASSOCIATE);

	/* Fill in static fields */
	memcpy(cmd->bssid, bss->bssid, ETH_ALEN);
	cmd->listeninterval = cpu_to_le16(MRVDRV_DEFAULT_LISTEN_INTERVAL);
	cmd->capability = cpu_to_le16(bss->capability);

	/* add SSID TLV */
	rcu_read_lock();
	ssid_eid = ieee80211_bss_get_ie(bss, WLAN_EID_SSID);
	if (ssid_eid)
		pos += lbs_add_ssid_tlv(pos, ssid_eid + 2, ssid_eid[1]);
	else
		lbs_deb_assoc("no SSID\n");
	rcu_read_unlock();

	/* add DS param TLV */
	if (bss->channel)
		pos += lbs_add_channel_tlv(pos, bss->channel->hw_value);
	else
		lbs_deb_assoc("no channel\n");

	/* add (empty) CF param TLV */
	pos += lbs_add_cf_param_tlv(pos);

	/* add rates TLV */
	tmp = pos + 4; /* skip Marvell IE header */
	pos += lbs_add_common_rates_tlv(pos, bss);
	lbs_deb_hex(LBS_DEB_ASSOC, "Common Rates", tmp, pos - tmp);

	/* add auth type TLV */
	if (MRVL_FW_MAJOR_REV(priv->fwrelease) >= 9)
		pos += lbs_add_auth_type_tlv(pos, sme->auth_type);

	/* add WPA/WPA2 TLV */
	if (sme->ie && sme->ie_len)
		pos += lbs_add_wpa_tlv(pos, sme->ie, sme->ie_len);

	len = (sizeof(*cmd) - sizeof(cmd->iebuf)) +
		(u16)(pos - (u8 *) &cmd->iebuf);
	cmd->hdr.size = cpu_to_le16(len);

	lbs_deb_hex(LBS_DEB_ASSOC, "ASSOC_CMD", (u8 *) cmd,
			le16_to_cpu(cmd->hdr.size));

	/* store for later use */
	memcpy(priv->assoc_bss, bss->bssid, ETH_ALEN);

	ret = lbs_cmd_with_response(priv, CMD_802_11_ASSOCIATE, cmd);
	if (ret)
		goto done;

	/* generate connect message to cfg80211 */

	resp = (void *) cmd; /* recast for easier field access */
	status = le16_to_cpu(resp->statuscode);

	/* Older FW versions map the IEEE 802.11 Status Code in the association
	 * response to the following values returned in resp->statuscode:
	 *
	 *    IEEE Status Code                Marvell Status Code
	 *    0                       ->      0x0000 ASSOC_RESULT_SUCCESS
	 *    13                      ->      0x0004 ASSOC_RESULT_AUTH_REFUSED
	 *    14                      ->      0x0004 ASSOC_RESULT_AUTH_REFUSED
	 *    15                      ->      0x0004 ASSOC_RESULT_AUTH_REFUSED
	 *    16                      ->      0x0004 ASSOC_RESULT_AUTH_REFUSED
	 *    others                  ->      0x0003 ASSOC_RESULT_REFUSED
	 *
	 * Other response codes:
	 *    0x0001 -> ASSOC_RESULT_INVALID_PARAMETERS (unused)
	 *    0x0002 -> ASSOC_RESULT_TIMEOUT (internal timer expired waiting for
	 *                                    association response from the AP)
	 */
	if (MRVL_FW_MAJOR_REV(priv->fwrelease) <= 8) {
		switch (status) {
		case 0:
			break;
		case 1:
			lbs_deb_assoc("invalid association parameters\n");
			status = WLAN_STATUS_CAPS_UNSUPPORTED;
			break;
		case 2:
			lbs_deb_assoc("timer expired while waiting for AP\n");
			status = WLAN_STATUS_AUTH_TIMEOUT;
			break;
		case 3:
			lbs_deb_assoc("association refused by AP\n");
			status = WLAN_STATUS_ASSOC_DENIED_UNSPEC;
			break;
		case 4:
			lbs_deb_assoc("authentication refused by AP\n");
			status = WLAN_STATUS_UNKNOWN_AUTH_TRANSACTION;
			break;
		default:
			lbs_deb_assoc("association failure %d\n", status);
			/* v5 OLPC firmware does return the AP status code if
			 * it's not one of the values above.  Let that through.
			 */
			break;
		}
	}

	lbs_deb_assoc("status %d, statuscode 0x%04x, capability 0x%04x, "
		      "aid 0x%04x\n", status, le16_to_cpu(resp->statuscode),
		      le16_to_cpu(resp->capability), le16_to_cpu(resp->aid));

	resp_ie_len = le16_to_cpu(resp->hdr.size)
		- sizeof(resp->hdr)
		- 6;
	cfg80211_connect_result(priv->dev,
				priv->assoc_bss,
				sme->ie, sme->ie_len,
				resp->iebuf, resp_ie_len,
				status,
				GFP_KERNEL);

	if (status == 0) {
		/* TODO: get rid of priv->connect_status */
		priv->connect_status = LBS_CONNECTED;
		netif_carrier_on(priv->dev);
		if (!priv->tx_pending_len)
			netif_tx_wake_all_queues(priv->dev);
	}

	kfree(cmd);
done:
	return ret;
}