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
struct sk_buff {int dummy; } ;
struct hcp_exec_waiter {int exec_result; int exec_complete; int /*<<< orphan*/  wq; struct sk_buff* result_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfc_hci_execute_cb(void *context, struct sk_buff *skb, int err)
{
	struct hcp_exec_waiter *hcp_ew = (struct hcp_exec_waiter *)context;

	pr_debug("HCI Cmd completed with result=%d\n", err);

	hcp_ew->exec_result = err;
	if (hcp_ew->exec_result == 0)
		hcp_ew->result_skb = skb;
	else
		kfree_skb(skb);
	hcp_ew->exec_complete = true;

	wake_up(hcp_ew->wq);
}