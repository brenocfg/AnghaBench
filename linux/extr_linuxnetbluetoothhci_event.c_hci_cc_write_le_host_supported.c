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
struct hci_dev {int /*<<< orphan*/ ** features; int /*<<< orphan*/  name; } ;
struct hci_cp_write_le_host_supported {scalar_t__ simul; scalar_t__ le; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HCI_ADVERTISING ; 
 int /*<<< orphan*/  HCI_LE_ENABLED ; 
 int /*<<< orphan*/  HCI_OP_WRITE_LE_HOST_SUPPORTED ; 
 int /*<<< orphan*/  LMP_HOST_LE ; 
 int /*<<< orphan*/  LMP_HOST_LE_BREDR ; 
 int /*<<< orphan*/  hci_dev_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct hci_cp_write_le_host_supported* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_write_le_host_supported(struct hci_dev *hdev,
					   struct sk_buff *skb)
{
	struct hci_cp_write_le_host_supported *sent;
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	if (status)
		return;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_LE_HOST_SUPPORTED);
	if (!sent)
		return;

	hci_dev_lock(hdev);

	if (sent->le) {
		hdev->features[1][0] |= LMP_HOST_LE;
		hci_dev_set_flag(hdev, HCI_LE_ENABLED);
	} else {
		hdev->features[1][0] &= ~LMP_HOST_LE;
		hci_dev_clear_flag(hdev, HCI_LE_ENABLED);
		hci_dev_clear_flag(hdev, HCI_ADVERTISING);
	}

	if (sent->simul)
		hdev->features[1][0] |= LMP_HOST_LE_BREDR;
	else
		hdev->features[1][0] &= ~LMP_HOST_LE_BREDR;

	hci_dev_unlock(hdev);
}