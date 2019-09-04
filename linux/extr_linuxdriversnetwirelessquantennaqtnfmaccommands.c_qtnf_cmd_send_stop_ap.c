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
struct qtnf_vif {TYPE_1__* mac; int /*<<< orphan*/  netdev; int /*<<< orphan*/  vifid; } ;
struct qlink_cmd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 scalar_t__ QLINK_CMD_RESULT_OK ; 
 int /*<<< orphan*/  QLINK_CMD_STOP_AP ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  qtnf_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (int /*<<< orphan*/ ) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_send (int /*<<< orphan*/ ,struct sk_buff*,scalar_t__*) ; 
 scalar_t__ unlikely (int) ; 

int qtnf_cmd_send_stop_ap(struct qtnf_vif *vif)
{
	struct sk_buff *cmd_skb;
	u16 res_code = QLINK_CMD_RESULT_OK;
	int ret;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QLINK_CMD_STOP_AP,
					    sizeof(struct qlink_cmd));
	if (!cmd_skb)
		return -ENOMEM;

	qtnf_bus_lock(vif->mac->bus);

	ret = qtnf_cmd_send(vif->mac->bus, cmd_skb, &res_code);

	if (unlikely(ret))
		goto out;

	if (unlikely(res_code != QLINK_CMD_RESULT_OK)) {
		pr_err("VIF%u.%u: CMD failed: %u\n", vif->mac->macid,
		       vif->vifid, res_code);
		ret = -EFAULT;
		goto out;
	}

	netif_carrier_off(vif->netdev);

out:
	qtnf_bus_unlock(vif->mac->bus);
	return ret;
}