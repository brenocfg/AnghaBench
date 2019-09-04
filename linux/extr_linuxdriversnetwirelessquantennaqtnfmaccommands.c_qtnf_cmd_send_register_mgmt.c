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
struct sk_buff {scalar_t__ data; } ;
struct qtnf_vif {TYPE_1__* mac; int /*<<< orphan*/  vifid; } ;
struct qlink_cmd_mgmt_frame_register {int do_register; int /*<<< orphan*/  frame_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QLINK_CMD_REGISTER_MGMT ; 
 scalar_t__ QLINK_CMD_RESULT_OK ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  qtnf_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (int /*<<< orphan*/ ) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_send (int /*<<< orphan*/ ,struct sk_buff*,scalar_t__*) ; 
 scalar_t__ unlikely (int) ; 

int qtnf_cmd_send_register_mgmt(struct qtnf_vif *vif, u16 frame_type, bool reg)
{
	struct sk_buff *cmd_skb;
	struct qlink_cmd_mgmt_frame_register *cmd;
	u16 res_code = QLINK_CMD_RESULT_OK;
	int ret;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QLINK_CMD_REGISTER_MGMT,
					    sizeof(*cmd));
	if (!cmd_skb)
		return -ENOMEM;

	qtnf_bus_lock(vif->mac->bus);

	cmd = (struct qlink_cmd_mgmt_frame_register *)cmd_skb->data;
	cmd->frame_type = cpu_to_le16(frame_type);
	cmd->do_register = reg;

	ret = qtnf_cmd_send(vif->mac->bus, cmd_skb, &res_code);

	if (unlikely(ret))
		goto out;

	if (unlikely(res_code != QLINK_CMD_RESULT_OK)) {
		pr_err("VIF%u.%u: CMD failed: %u\n", vif->mac->macid,
		       vif->vifid, res_code);
		ret = -EFAULT;
		goto out;
	}

out:
	qtnf_bus_unlock(vif->mac->bus);
	return ret;
}