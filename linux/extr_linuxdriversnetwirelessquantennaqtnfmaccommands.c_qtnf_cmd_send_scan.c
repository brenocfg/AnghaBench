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
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct qtnf_wmac {int /*<<< orphan*/  bus; int /*<<< orphan*/  macid; struct cfg80211_scan_request* scan_req; } ;
struct qlink_cmd {int dummy; } ;
struct ieee80211_channel {int flags; int /*<<< orphan*/  center_freq; int /*<<< orphan*/  hw_value; } ;
struct cfg80211_scan_request {int n_ssids; scalar_t__ ie_len; int n_channels; int flags; int /*<<< orphan*/  mac_addr_mask; int /*<<< orphan*/  mac_addr; struct ieee80211_channel** channels; int /*<<< orphan*/  ie; TYPE_1__* ssids; } ;
struct TYPE_2__ {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int IEEE80211_CHAN_DISABLED ; 
 int NL80211_SCAN_FLAG_RANDOM_ADDR ; 
 scalar_t__ QLINK_CMD_RESULT_OK ; 
 int /*<<< orphan*/  QLINK_CMD_SCAN ; 
 int /*<<< orphan*/  QLINK_IE_SET_PROBE_REQ ; 
 int /*<<< orphan*/  QLINK_VIFID_RSVD ; 
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  qtnf_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (int /*<<< orphan*/ ) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qtnf_cmd_channel_tlv_add (struct sk_buff*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  qtnf_cmd_randmac_tlv_add (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qtnf_cmd_send (int /*<<< orphan*/ ,struct sk_buff*,scalar_t__*) ; 
 int /*<<< orphan*/  qtnf_cmd_skb_put_tlv_arr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_cmd_tlv_ie_set_add (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

int qtnf_cmd_send_scan(struct qtnf_wmac *mac)
{
	struct sk_buff *cmd_skb;
	u16 res_code = QLINK_CMD_RESULT_OK;
	struct ieee80211_channel *sc;
	struct cfg80211_scan_request *scan_req = mac->scan_req;
	int n_channels;
	int count = 0;
	int ret;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(mac->macid, QLINK_VIFID_RSVD,
					    QLINK_CMD_SCAN,
					    sizeof(struct qlink_cmd));
	if (!cmd_skb)
		return -ENOMEM;

	qtnf_bus_lock(mac->bus);

	if (scan_req->n_ssids != 0) {
		while (count < scan_req->n_ssids) {
			qtnf_cmd_skb_put_tlv_arr(cmd_skb, WLAN_EID_SSID,
				scan_req->ssids[count].ssid,
				scan_req->ssids[count].ssid_len);
			count++;
		}
	}

	if (scan_req->ie_len != 0)
		qtnf_cmd_tlv_ie_set_add(cmd_skb, QLINK_IE_SET_PROBE_REQ,
					scan_req->ie, scan_req->ie_len);

	if (scan_req->n_channels) {
		n_channels = scan_req->n_channels;
		count = 0;

		while (n_channels != 0) {
			sc = scan_req->channels[count];
			if (sc->flags & IEEE80211_CHAN_DISABLED) {
				n_channels--;
				continue;
			}

			pr_debug("MAC%u: scan chan=%d, freq=%d, flags=%#x\n",
				 mac->macid, sc->hw_value, sc->center_freq,
				 sc->flags);

			qtnf_cmd_channel_tlv_add(cmd_skb, sc);
			n_channels--;
			count++;
		}
	}

	if (scan_req->flags & NL80211_SCAN_FLAG_RANDOM_ADDR) {
		pr_debug("MAC%u: scan with random addr=%pM, mask=%pM\n",
			 mac->macid,
			 scan_req->mac_addr, scan_req->mac_addr_mask);

		qtnf_cmd_randmac_tlv_add(cmd_skb, scan_req->mac_addr,
					 scan_req->mac_addr_mask);
	}

	ret = qtnf_cmd_send(mac->bus, cmd_skb, &res_code);

	if (unlikely(ret))
		goto out;

	pr_debug("MAC%u: scan started\n", mac->macid);

	if (unlikely(res_code != QLINK_CMD_RESULT_OK)) {
		pr_err("MAC%u: CMD failed: %u\n", mac->macid, res_code);
		ret = -EFAULT;
		goto out;
	}
out:
	qtnf_bus_unlock(mac->bus);
	return ret;
}