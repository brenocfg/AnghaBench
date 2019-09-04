#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct usbnet {int /*<<< orphan*/  net; } ;
struct rndis_wlan_private {scalar_t__ infra_mode; int connected; int /*<<< orphan*/  bssid; int /*<<< orphan*/  work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  work_pending; } ;
struct ndis_80211_assoc_info {int /*<<< orphan*/  offset_resp_ies; int /*<<< orphan*/  resp_ie_length; int /*<<< orphan*/  offset_req_ies; int /*<<< orphan*/  req_ie_length; } ;
struct cfg80211_roam_info {unsigned int req_ie_len; unsigned int resp_ie_len; int /*<<< orphan*/ * resp_ie; int /*<<< orphan*/ * req_ie; int /*<<< orphan*/ * bssid; int /*<<< orphan*/  channel; } ;
typedef  int /*<<< orphan*/  bssid ;

/* Variables and functions */
 unsigned int CONTROL_BUFFER_SIZE ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NDIS_80211_INFRA_ADHOC ; 
 scalar_t__ NDIS_80211_INFRA_INFRA ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WORK_LINK_UP ; 
 int /*<<< orphan*/  cfg80211_connect_result (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_ibss_joined (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_roamed (int /*<<< orphan*/ ,struct cfg80211_roam_info*,int /*<<< orphan*/ ) ; 
 int get_association_info (struct usbnet*,struct ndis_80211_assoc_info*,unsigned int) ; 
 int get_bssid (struct usbnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_current_channel (struct usbnet*,int /*<<< orphan*/ *) ; 
 struct rndis_wlan_private* get_rndis_wlan_priv (struct usbnet*) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ndis_80211_assoc_info*) ; 
 struct ndis_80211_assoc_info* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rndis_check_bssid_list (struct usbnet*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  rndis_wlan_craft_connected_bss (struct usbnet*,int /*<<< orphan*/ *,struct ndis_80211_assoc_info*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbnet_resume_rx (struct usbnet*) ; 

__attribute__((used)) static void rndis_wlan_do_link_up_work(struct usbnet *usbdev)
{
	struct rndis_wlan_private *priv = get_rndis_wlan_priv(usbdev);
	struct ndis_80211_assoc_info *info = NULL;
	u8 bssid[ETH_ALEN];
	unsigned int resp_ie_len, req_ie_len;
	unsigned int offset;
	u8 *req_ie, *resp_ie;
	int ret;
	bool roamed = false;
	bool match_bss;

	if (priv->infra_mode == NDIS_80211_INFRA_INFRA && priv->connected) {
		/* received media connect indication while connected, either
		 * device reassociated with same AP or roamed to new. */
		roamed = true;
	}

	req_ie_len = 0;
	resp_ie_len = 0;
	req_ie = NULL;
	resp_ie = NULL;

	if (priv->infra_mode == NDIS_80211_INFRA_INFRA) {
		info = kzalloc(CONTROL_BUFFER_SIZE, GFP_KERNEL);
		if (!info) {
			/* No memory? Try resume work later */
			set_bit(WORK_LINK_UP, &priv->work_pending);
			queue_work(priv->workqueue, &priv->work);
			return;
		}

		/* Get association info IEs from device. */
		ret = get_association_info(usbdev, info, CONTROL_BUFFER_SIZE);
		if (!ret) {
			req_ie_len = le32_to_cpu(info->req_ie_length);
			if (req_ie_len > CONTROL_BUFFER_SIZE)
				req_ie_len = CONTROL_BUFFER_SIZE;
			if (req_ie_len != 0) {
				offset = le32_to_cpu(info->offset_req_ies);

				if (offset > CONTROL_BUFFER_SIZE)
					offset = CONTROL_BUFFER_SIZE;

				req_ie = (u8 *)info + offset;

				if (offset + req_ie_len > CONTROL_BUFFER_SIZE)
					req_ie_len =
						CONTROL_BUFFER_SIZE - offset;
			}

			resp_ie_len = le32_to_cpu(info->resp_ie_length);
			if (resp_ie_len > CONTROL_BUFFER_SIZE)
				resp_ie_len = CONTROL_BUFFER_SIZE;
			if (resp_ie_len != 0) {
				offset = le32_to_cpu(info->offset_resp_ies);

				if (offset > CONTROL_BUFFER_SIZE)
					offset = CONTROL_BUFFER_SIZE;

				resp_ie = (u8 *)info + offset;

				if (offset + resp_ie_len > CONTROL_BUFFER_SIZE)
					resp_ie_len =
						CONTROL_BUFFER_SIZE - offset;
			}
		} else {
			/* Since rndis_wlan_craft_connected_bss() might use info
			 * later and expects info to contain valid data if
			 * non-null, free info and set NULL here.
			 */
			kfree(info);
			info = NULL;
		}
	} else if (WARN_ON(priv->infra_mode != NDIS_80211_INFRA_ADHOC))
		return;

	ret = get_bssid(usbdev, bssid);
	if (ret < 0)
		memset(bssid, 0, sizeof(bssid));

	netdev_dbg(usbdev->net, "link up work: [%pM]%s\n",
		   bssid, roamed ? " roamed" : "");

	/* Internal bss list in device should contain at least the currently
	 * connected bss and we can get it to cfg80211 with
	 * rndis_check_bssid_list().
	 *
	 * NDIS spec says: "If the device is associated, but the associated
	 *  BSSID is not in its BSSID scan list, then the driver must add an
	 *  entry for the BSSID at the end of the data that it returns in
	 *  response to query of RNDIS_OID_802_11_BSSID_LIST."
	 *
	 * NOTE: Seems to be true for BCM4320b variant, but not BCM4320a.
	 */
	match_bss = false;
	rndis_check_bssid_list(usbdev, bssid, &match_bss);

	if (!is_zero_ether_addr(bssid) && !match_bss) {
		/* Couldn't get bss from device, we need to manually craft bss
		 * for cfg80211.
		 */
		rndis_wlan_craft_connected_bss(usbdev, bssid, info);
	}

	if (priv->infra_mode == NDIS_80211_INFRA_INFRA) {
		if (!roamed) {
			cfg80211_connect_result(usbdev->net, bssid, req_ie,
						req_ie_len, resp_ie,
						resp_ie_len, 0, GFP_KERNEL);
		} else {
			struct cfg80211_roam_info roam_info = {
				.channel = get_current_channel(usbdev, NULL),
				.bssid = bssid,
				.req_ie = req_ie,
				.req_ie_len = req_ie_len,
				.resp_ie = resp_ie,
				.resp_ie_len = resp_ie_len,
			};

			cfg80211_roamed(usbdev->net, &roam_info, GFP_KERNEL);
		}
	} else if (priv->infra_mode == NDIS_80211_INFRA_ADHOC)
		cfg80211_ibss_joined(usbdev->net, bssid,
				     get_current_channel(usbdev, NULL),
				     GFP_KERNEL);

	kfree(info);

	priv->connected = true;
	memcpy(priv->bssid, bssid, ETH_ALEN);

	usbnet_resume_rx(usbdev);
	netif_carrier_on(usbdev->net);
}