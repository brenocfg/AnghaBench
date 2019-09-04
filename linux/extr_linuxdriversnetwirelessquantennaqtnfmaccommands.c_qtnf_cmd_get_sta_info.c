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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct station_info {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct qtnf_vif {TYPE_1__* mac; int /*<<< orphan*/  vifid; } ;
struct qlink_tlv_hdr {int dummy; } ;
struct qlink_resp_get_sta_info {scalar_t__ info; int /*<<< orphan*/  sta_addr; } ;
struct qlink_cmd_get_sta_info {int /*<<< orphan*/  sta_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QLINK_CMD_GET_STA_INFO ; 
#define  QLINK_CMD_RESULT_ENOTFOUND 128 
 int QLINK_CMD_RESULT_OK ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  qtnf_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (int /*<<< orphan*/ ) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_send_with_reply (int /*<<< orphan*/ ,struct sk_buff*,struct sk_buff**,int*,int,size_t*) ; 
 int /*<<< orphan*/  qtnf_cmd_sta_info_parse (struct station_info*,struct qlink_tlv_hdr const*,size_t) ; 
 scalar_t__ unlikely (int) ; 

int qtnf_cmd_get_sta_info(struct qtnf_vif *vif, const u8 *sta_mac,
			  struct station_info *sinfo)
{
	struct sk_buff *cmd_skb, *resp_skb = NULL;
	struct qlink_cmd_get_sta_info *cmd;
	const struct qlink_resp_get_sta_info *resp;
	size_t var_resp_len;
	u16 res_code = QLINK_CMD_RESULT_OK;
	int ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QLINK_CMD_GET_STA_INFO,
					    sizeof(*cmd));
	if (!cmd_skb)
		return -ENOMEM;

	qtnf_bus_lock(vif->mac->bus);

	cmd = (struct qlink_cmd_get_sta_info *)cmd_skb->data;
	ether_addr_copy(cmd->sta_addr, sta_mac);

	ret = qtnf_cmd_send_with_reply(vif->mac->bus, cmd_skb, &resp_skb,
				       &res_code, sizeof(*resp),
				       &var_resp_len);

	if (unlikely(ret))
		goto out;

	if (unlikely(res_code != QLINK_CMD_RESULT_OK)) {
		switch (res_code) {
		case QLINK_CMD_RESULT_ENOTFOUND:
			pr_warn("VIF%u.%u: %pM STA not found\n",
				vif->mac->macid, vif->vifid, sta_mac);
			ret = -ENOENT;
			break;
		default:
			pr_err("VIF%u.%u: can't get info for %pM: %u\n",
			       vif->mac->macid, vif->vifid, sta_mac, res_code);
			ret = -EFAULT;
			break;
		}
		goto out;
	}

	resp = (const struct qlink_resp_get_sta_info *)resp_skb->data;

	if (unlikely(!ether_addr_equal(sta_mac, resp->sta_addr))) {
		pr_err("VIF%u.%u: wrong mac in reply: %pM != %pM\n",
		       vif->mac->macid, vif->vifid, resp->sta_addr, sta_mac);
		ret = -EINVAL;
		goto out;
	}

	qtnf_cmd_sta_info_parse(sinfo,
				(const struct qlink_tlv_hdr *)resp->info,
				var_resp_len);

out:
	qtnf_bus_unlock(vif->mac->bus);
	consume_skb(resp_skb);

	return ret;
}