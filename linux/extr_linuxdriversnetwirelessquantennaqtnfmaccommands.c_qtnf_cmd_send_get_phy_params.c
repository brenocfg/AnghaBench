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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ data; } ;
struct qtnf_wmac {int /*<<< orphan*/  bus; int /*<<< orphan*/  macid; } ;
struct qlink_resp_phy_params {int /*<<< orphan*/  info; } ;
struct qlink_cmd {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QLINK_CMD_PHY_PARAMS_GET ; 
 scalar_t__ QLINK_CMD_RESULT_OK ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  qtnf_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (int /*<<< orphan*/ ) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_resp_proc_phy_params (struct qtnf_wmac*,int /*<<< orphan*/ ,size_t) ; 
 int qtnf_cmd_send_with_reply (int /*<<< orphan*/ ,struct sk_buff*,struct sk_buff**,scalar_t__*,int,size_t*) ; 
 scalar_t__ unlikely (int) ; 

int qtnf_cmd_send_get_phy_params(struct qtnf_wmac *mac)
{
	struct sk_buff *cmd_skb, *resp_skb = NULL;
	size_t response_size;
	struct qlink_resp_phy_params *resp;
	u16 res_code = QLINK_CMD_RESULT_OK;
	int ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(mac->macid, 0,
					    QLINK_CMD_PHY_PARAMS_GET,
					    sizeof(struct qlink_cmd));
	if (!cmd_skb)
		return -ENOMEM;

	qtnf_bus_lock(mac->bus);

	ret = qtnf_cmd_send_with_reply(mac->bus, cmd_skb, &resp_skb, &res_code,
				       sizeof(*resp), &response_size);

	if (unlikely(ret))
		goto out;

	if (unlikely(res_code != QLINK_CMD_RESULT_OK)) {
		pr_err("MAC%u: CMD failed: %u\n", mac->macid, res_code);
		ret = -EFAULT;
		goto out;
	}

	resp = (struct qlink_resp_phy_params *)resp_skb->data;
	ret = qtnf_cmd_resp_proc_phy_params(mac, resp->info, response_size);

out:
	qtnf_bus_unlock(mac->bus);
	consume_skb(resp_skb);

	return ret;
}