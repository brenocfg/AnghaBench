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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ data; } ;
struct qtnf_vif {int /*<<< orphan*/  vifid; TYPE_1__* mac; } ;
struct qtnf_bus {int dummy; } ;
struct qlink_cmd_pm_set {int /*<<< orphan*/  pm_standby_timer; int /*<<< orphan*/  pm_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  macid; struct qtnf_bus* bus; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QLINK_CMD_PM_SET ; 
 scalar_t__ QLINK_CMD_RESULT_OK ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  qtnf_bus_lock (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (struct qtnf_bus*) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_send (struct qtnf_bus*,struct sk_buff*,scalar_t__*) ; 
 scalar_t__ unlikely (int) ; 

int qtnf_cmd_send_pm_set(const struct qtnf_vif *vif, u8 pm_mode, int timeout)
{
	struct qtnf_bus *bus = vif->mac->bus;
	struct sk_buff *cmd_skb;
	u16 res_code = QLINK_CMD_RESULT_OK;
	struct qlink_cmd_pm_set *cmd;
	int ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QLINK_CMD_PM_SET, sizeof(*cmd));
	if (!cmd_skb)
		return -ENOMEM;

	cmd = (struct qlink_cmd_pm_set *)cmd_skb->data;
	cmd->pm_mode = pm_mode;
	cmd->pm_standby_timer = cpu_to_le32(timeout);

	qtnf_bus_lock(bus);

	ret = qtnf_cmd_send(bus, cmd_skb, &res_code);

	if (unlikely(ret))
		goto out;

	if (unlikely(res_code != QLINK_CMD_RESULT_OK)) {
		pr_err("cmd exec failed: 0x%.4X\n", res_code);
		ret = -EFAULT;
	}

out:
	qtnf_bus_unlock(bus);
	return ret;
}