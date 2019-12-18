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
struct sk_buff {scalar_t__ data; } ;
struct hci_dev {int /*<<< orphan*/  dev_name; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_MAX_NAME_LENGTH ; 
 int /*<<< orphan*/  HCI_MGMT ; 
 int /*<<< orphan*/  HCI_OP_WRITE_LOCAL_NAME ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 void* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_set_local_name_complete (struct hci_dev*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_write_local_name(struct hci_dev *hdev, struct sk_buff *skb)
{
	__u8 status = *((__u8 *) skb->data);
	void *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_LOCAL_NAME);
	if (!sent)
		return;

	hci_dev_lock(hdev);

	if (hci_dev_test_flag(hdev, HCI_MGMT))
		mgmt_set_local_name_complete(hdev, sent, status);
	else if (!status)
		memcpy(hdev->dev_name, sent, HCI_MAX_NAME_LENGTH);

	hci_dev_unlock(hdev);
}