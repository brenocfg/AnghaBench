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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ data; } ;
struct qtnf_wmac {int /*<<< orphan*/  bus; int /*<<< orphan*/  macid; } ;
struct qlink_resp_band_info_get {scalar_t__ band; } ;
struct qlink_cmd_band_info_get {scalar_t__ band; } ;
struct ieee80211_supported_band {int band; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
#define  NL80211_BAND_2GHZ 130 
#define  NL80211_BAND_5GHZ 129 
#define  NL80211_BAND_60GHZ 128 
 scalar_t__ QLINK_BAND_2GHZ ; 
 scalar_t__ QLINK_BAND_5GHZ ; 
 scalar_t__ QLINK_BAND_60GHZ ; 
 int /*<<< orphan*/  QLINK_CMD_BAND_INFO_GET ; 
 scalar_t__ QLINK_CMD_RESULT_OK ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int /*<<< orphan*/  qtnf_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (int /*<<< orphan*/ ) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_resp_fill_band_info (struct ieee80211_supported_band*,struct qlink_resp_band_info_get*,size_t) ; 
 int qtnf_cmd_send_with_reply (int /*<<< orphan*/ ,struct sk_buff*,struct sk_buff**,scalar_t__*,int,size_t*) ; 
 scalar_t__ unlikely (int) ; 

int qtnf_cmd_band_info_get(struct qtnf_wmac *mac,
			   struct ieee80211_supported_band *band)
{
	struct sk_buff *cmd_skb, *resp_skb = NULL;
	size_t info_len;
	struct qlink_cmd_band_info_get *cmd;
	struct qlink_resp_band_info_get *resp;
	u16 res_code = QLINK_CMD_RESULT_OK;
	int ret = 0;
	u8 qband;

	switch (band->band) {
	case NL80211_BAND_2GHZ:
		qband = QLINK_BAND_2GHZ;
		break;
	case NL80211_BAND_5GHZ:
		qband = QLINK_BAND_5GHZ;
		break;
	case NL80211_BAND_60GHZ:
		qband = QLINK_BAND_60GHZ;
		break;
	default:
		return -EINVAL;
	}

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(mac->macid, 0,
					    QLINK_CMD_BAND_INFO_GET,
					    sizeof(*cmd));
	if (!cmd_skb)
		return -ENOMEM;

	cmd = (struct qlink_cmd_band_info_get *)cmd_skb->data;
	cmd->band = qband;

	qtnf_bus_lock(mac->bus);

	ret = qtnf_cmd_send_with_reply(mac->bus, cmd_skb, &resp_skb, &res_code,
				       sizeof(*resp), &info_len);

	if (unlikely(ret))
		goto out;

	if (unlikely(res_code != QLINK_CMD_RESULT_OK)) {
		pr_err("MAC%u: CMD failed: %u\n", mac->macid, res_code);
		ret = -EFAULT;
		goto out;
	}

	resp = (struct qlink_resp_band_info_get *)resp_skb->data;
	if (resp->band != qband) {
		pr_err("MAC%u: reply band %u != cmd band %u\n", mac->macid,
		       resp->band, qband);
		ret = -EINVAL;
		goto out;
	}

	ret = qtnf_cmd_resp_fill_band_info(band, resp, info_len);

out:
	qtnf_bus_unlock(mac->bus);
	consume_skb(resp_skb);

	return ret;
}