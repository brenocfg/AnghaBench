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
struct qtnf_cmd_ctl_node {int waiting_for_resp; scalar_t__ const seq_num; int /*<<< orphan*/  resp_lock; int /*<<< orphan*/  cmd_resp_completion; struct sk_buff* resp_skb; } ;
struct TYPE_2__ {struct qtnf_cmd_ctl_node curr_cmd; } ;
struct qtnf_bus {TYPE_1__ trans; } ;
struct qlink_resp {int /*<<< orphan*/  seq_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void qtnf_trans_signal_cmdresp(struct qtnf_bus *bus, struct sk_buff *skb)
{
	struct qtnf_cmd_ctl_node *ctl_node = &bus->trans.curr_cmd;
	const struct qlink_resp *resp = (const struct qlink_resp *)skb->data;
	const u16 recvd_seq_num = le16_to_cpu(resp->seq_num);

	spin_lock(&ctl_node->resp_lock);

	if (unlikely(!ctl_node->waiting_for_resp)) {
		pr_err("unexpected response\n");
		goto out_err;
	}

	if (unlikely(recvd_seq_num != ctl_node->seq_num)) {
		pr_err("seq num mismatch\n");
		goto out_err;
	}

	ctl_node->resp_skb = skb;
	ctl_node->waiting_for_resp = false;

	spin_unlock(&ctl_node->resp_lock);

	complete(&ctl_node->cmd_resp_completion);
	return;

out_err:
	spin_unlock(&ctl_node->resp_lock);
	dev_kfree_skb(skb);
}