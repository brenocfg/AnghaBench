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
struct sk_buff {int dummy; } ;
struct nfc_hci_dev {int /*<<< orphan*/  msg_tx_work; TYPE_1__* cmd_pending_msg; int /*<<< orphan*/  cmd_timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  cb_context; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,struct sk_buff*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sk_buff*,int) ; 

__attribute__((used)) static void __nfc_hci_cmd_completion(struct nfc_hci_dev *hdev, int err,
				     struct sk_buff *skb)
{
	del_timer_sync(&hdev->cmd_timer);

	if (hdev->cmd_pending_msg->cb)
		hdev->cmd_pending_msg->cb(hdev->cmd_pending_msg->cb_context,
					  skb, err);
	else
		kfree_skb(skb);

	kfree(hdev->cmd_pending_msg);
	hdev->cmd_pending_msg = NULL;

	schedule_work(&hdev->msg_tx_work);
}