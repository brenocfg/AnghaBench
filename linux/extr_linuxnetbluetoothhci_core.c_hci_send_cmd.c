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
struct sk_buff {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  cmd_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_3__ {int /*<<< orphan*/  req_flags; } ;
struct TYPE_4__ {TYPE_1__ hci; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_REQ_START ; 
 TYPE_2__* bt_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*) ; 
 struct sk_buff* hci_prepare_cmd (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

int hci_send_cmd(struct hci_dev *hdev, __u16 opcode, __u32 plen,
		 const void *param)
{
	struct sk_buff *skb;

	BT_DBG("%s opcode 0x%4.4x plen %d", hdev->name, opcode, plen);

	skb = hci_prepare_cmd(hdev, opcode, plen, param);
	if (!skb) {
		bt_dev_err(hdev, "no memory for command");
		return -ENOMEM;
	}

	/* Stand-alone HCI commands must be flagged as
	 * single-command requests.
	 */
	bt_cb(skb)->hci.req_flags |= HCI_REQ_START;

	skb_queue_tail(&hdev->cmd_q, skb);
	queue_work(hdev->workqueue, &hdev->cmd_work);

	return 0;
}