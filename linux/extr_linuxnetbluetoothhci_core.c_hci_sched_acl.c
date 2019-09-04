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
struct hci_dev {scalar_t__ dev_type; int flow_ctl_mode; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 int /*<<< orphan*/  AMP_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ HCI_AMP ; 
#define  HCI_FLOW_CTL_MODE_BLOCK_BASED 129 
#define  HCI_FLOW_CTL_MODE_PACKET_BASED 128 
 scalar_t__ HCI_PRIMARY ; 
 int /*<<< orphan*/  hci_conn_num (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_sched_acl_blk (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_sched_acl_pkt (struct hci_dev*) ; 

__attribute__((used)) static void hci_sched_acl(struct hci_dev *hdev)
{
	BT_DBG("%s", hdev->name);

	/* No ACL link over BR/EDR controller */
	if (!hci_conn_num(hdev, ACL_LINK) && hdev->dev_type == HCI_PRIMARY)
		return;

	/* No AMP link over AMP controller */
	if (!hci_conn_num(hdev, AMP_LINK) && hdev->dev_type == HCI_AMP)
		return;

	switch (hdev->flow_ctl_mode) {
	case HCI_FLOW_CTL_MODE_PACKET_BASED:
		hci_sched_acl_pkt(hdev);
		break;

	case HCI_FLOW_CTL_MODE_BLOCK_BASED:
		hci_sched_acl_blk(hdev);
		break;
	}
}