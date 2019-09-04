#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct sk_buff {scalar_t__ data; int /*<<< orphan*/  len; } ;
struct qtnf_bus {int /*<<< orphan*/  fw_state; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct qlink_resp {TYPE_2__ mhdr; int /*<<< orphan*/  result; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; } ;
struct qlink_cmd {int /*<<< orphan*/  cmd_id; TYPE_1__ mhdr; int /*<<< orphan*/  vifid; int /*<<< orphan*/  macid; } ;

/* Variables and functions */
 int ENODEV ; 
 size_t QLINK_CMD_FW_INIT ; 
 int /*<<< orphan*/  QTNF_FW_STATE_ACTIVE ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (size_t*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int qtnf_cmd_check_reply_header (struct qlink_resp const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int qtnf_trans_send_cmd_with_resp (struct qtnf_bus*,struct sk_buff*,struct sk_buff**) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int qtnf_cmd_send_with_reply(struct qtnf_bus *bus,
				    struct sk_buff *cmd_skb,
				    struct sk_buff **response_skb,
				    u16 *result_code,
				    size_t const_resp_size,
				    size_t *var_resp_size)
{
	struct qlink_cmd *cmd;
	const struct qlink_resp *resp;
	struct sk_buff *resp_skb = NULL;
	u16 cmd_id;
	u8 mac_id, vif_id;
	int ret;

	cmd = (struct qlink_cmd *)cmd_skb->data;
	cmd_id = le16_to_cpu(cmd->cmd_id);
	mac_id = cmd->macid;
	vif_id = cmd->vifid;
	cmd->mhdr.len = cpu_to_le16(cmd_skb->len);

	if (unlikely(bus->fw_state != QTNF_FW_STATE_ACTIVE &&
		     le16_to_cpu(cmd->cmd_id) != QLINK_CMD_FW_INIT)) {
		pr_warn("VIF%u.%u: drop cmd 0x%.4X in fw state %d\n",
			mac_id, vif_id, le16_to_cpu(cmd->cmd_id),
			bus->fw_state);
		dev_kfree_skb(cmd_skb);
		return -ENODEV;
	}

	pr_debug("VIF%u.%u cmd=0x%.4X\n", mac_id, vif_id,
		 le16_to_cpu(cmd->cmd_id));

	ret = qtnf_trans_send_cmd_with_resp(bus, cmd_skb, &resp_skb);

	if (unlikely(ret))
		goto out;

	resp = (const struct qlink_resp *)resp_skb->data;
	ret = qtnf_cmd_check_reply_header(resp, cmd_id, mac_id, vif_id,
					  const_resp_size);

	if (unlikely(ret))
		goto out;

	if (likely(result_code))
		*result_code = le16_to_cpu(resp->result);

	/* Return length of variable part of response */
	if (response_skb && var_resp_size)
		*var_resp_size = le16_to_cpu(resp->mhdr.len) - const_resp_size;

out:
	if (response_skb)
		*response_skb = resp_skb;
	else
		consume_skb(resp_skb);

	return ret;
}