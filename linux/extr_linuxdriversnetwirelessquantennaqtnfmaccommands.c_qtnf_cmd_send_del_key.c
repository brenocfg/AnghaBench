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
struct qtnf_vif {TYPE_1__* mac; int /*<<< orphan*/  vifid; } ;
struct qlink_cmd_del_key {int pairwise; int /*<<< orphan*/  key_index; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QLINK_CMD_DEL_KEY ; 
 scalar_t__ QLINK_CMD_RESULT_OK ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  qtnf_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (int /*<<< orphan*/ ) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_send (int /*<<< orphan*/ ,struct sk_buff*,scalar_t__*) ; 
 scalar_t__ unlikely (int) ; 

int qtnf_cmd_send_del_key(struct qtnf_vif *vif, u8 key_index, bool pairwise,
			  const u8 *mac_addr)
{
	struct sk_buff *cmd_skb;
	struct qlink_cmd_del_key *cmd;
	u16 res_code = QLINK_CMD_RESULT_OK;
	int ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(vif->mac->macid, vif->vifid,
					    QLINK_CMD_DEL_KEY,
					    sizeof(*cmd));
	if (!cmd_skb)
		return -ENOMEM;

	qtnf_bus_lock(vif->mac->bus);

	cmd = (struct qlink_cmd_del_key *)cmd_skb->data;

	if (mac_addr)
		ether_addr_copy(cmd->addr, mac_addr);
	else
		eth_broadcast_addr(cmd->addr);

	cmd->key_index = key_index;
	cmd->pairwise = pairwise;
	ret = qtnf_cmd_send(vif->mac->bus, cmd_skb, &res_code);
	if (unlikely(ret))
		goto out;

	if (unlikely(res_code != QLINK_CMD_RESULT_OK)) {
		pr_err("VIF%u.%u: CMD failed: %u\n",
		       vif->mac->macid, vif->vifid, res_code);
		ret = -EFAULT;
		goto out;
	}

out:
	qtnf_bus_unlock(vif->mac->bus);
	return ret;
}