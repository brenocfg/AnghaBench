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
struct qtnf_bus {int dummy; } ;
struct qlink_resp_get_hw_info {int dummy; } ;
struct qlink_cmd {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QLINK_CMD_GET_HW_INFO ; 
 scalar_t__ QLINK_CMD_RESULT_OK ; 
 int /*<<< orphan*/  QLINK_MACID_RSVD ; 
 int /*<<< orphan*/  QLINK_VIFID_RSVD ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  qtnf_bus_lock (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (struct qtnf_bus*) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_resp_proc_hw_info (struct qtnf_bus*,struct qlink_resp_get_hw_info const*,size_t) ; 
 int qtnf_cmd_send_with_reply (struct qtnf_bus*,struct sk_buff*,struct sk_buff**,scalar_t__*,int,size_t*) ; 
 scalar_t__ unlikely (int) ; 

int qtnf_cmd_get_hw_info(struct qtnf_bus *bus)
{
	struct sk_buff *cmd_skb, *resp_skb = NULL;
	const struct qlink_resp_get_hw_info *resp;
	u16 res_code = QLINK_CMD_RESULT_OK;
	int ret = 0;
	size_t info_len;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(QLINK_MACID_RSVD, QLINK_VIFID_RSVD,
					    QLINK_CMD_GET_HW_INFO,
					    sizeof(struct qlink_cmd));
	if (!cmd_skb)
		return -ENOMEM;

	qtnf_bus_lock(bus);

	ret = qtnf_cmd_send_with_reply(bus, cmd_skb, &resp_skb, &res_code,
				       sizeof(*resp), &info_len);

	if (unlikely(ret))
		goto out;

	if (unlikely(res_code != QLINK_CMD_RESULT_OK)) {
		pr_err("cmd exec failed: 0x%.4X\n", res_code);
		ret = -EFAULT;
		goto out;
	}

	resp = (const struct qlink_resp_get_hw_info *)resp_skb->data;
	ret = qtnf_cmd_resp_proc_hw_info(bus, resp, info_len);

out:
	qtnf_bus_unlock(bus);
	consume_skb(resp_skb);

	return ret;
}