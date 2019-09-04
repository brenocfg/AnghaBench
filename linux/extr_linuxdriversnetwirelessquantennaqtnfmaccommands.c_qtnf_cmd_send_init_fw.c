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
struct sk_buff {int dummy; } ;
struct qtnf_bus {int dummy; } ;
struct qlink_cmd {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QLINK_CMD_FW_INIT ; 
 scalar_t__ QLINK_CMD_RESULT_OK ; 
 int /*<<< orphan*/  QLINK_MACID_RSVD ; 
 int /*<<< orphan*/  QLINK_VIFID_RSVD ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  qtnf_bus_lock (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (struct qtnf_bus*) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_send (struct qtnf_bus*,struct sk_buff*,scalar_t__*) ; 
 scalar_t__ unlikely (int) ; 

int qtnf_cmd_send_init_fw(struct qtnf_bus *bus)
{
	struct sk_buff *cmd_skb;
	u16 res_code = QLINK_CMD_RESULT_OK;
	int ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(QLINK_MACID_RSVD, QLINK_VIFID_RSVD,
					    QLINK_CMD_FW_INIT,
					    sizeof(struct qlink_cmd));
	if (!cmd_skb)
		return -ENOMEM;

	qtnf_bus_lock(bus);

	ret = qtnf_cmd_send(bus, cmd_skb, &res_code);

	if (unlikely(ret))
		goto out;

	if (unlikely(res_code != QLINK_CMD_RESULT_OK)) {
		pr_err("cmd exec failed: 0x%.4X\n", res_code);
		ret = -EFAULT;
		goto out;
	}

out:
	qtnf_bus_unlock(bus);
	return ret;
}