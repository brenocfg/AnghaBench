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
struct hci_rp_read_stored_link_key {int /*<<< orphan*/  num_keys; int /*<<< orphan*/  max_keys; int /*<<< orphan*/  status; } ;
struct hci_dev {int /*<<< orphan*/  stored_num_keys; int /*<<< orphan*/  stored_max_keys; int /*<<< orphan*/  name; } ;
struct hci_cp_read_stored_link_key {int read_all; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_OP_READ_STORED_LINK_KEY ; 
 struct hci_cp_read_stored_link_key* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_read_stored_link_key(struct hci_dev *hdev,
					struct sk_buff *skb)
{
	struct hci_rp_read_stored_link_key *rp = (void *)skb->data;
	struct hci_cp_read_stored_link_key *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	sent = hci_sent_cmd_data(hdev, HCI_OP_READ_STORED_LINK_KEY);
	if (!sent)
		return;

	if (!rp->status && sent->read_all == 0x01) {
		hdev->stored_max_keys = rp->max_keys;
		hdev->stored_num_keys = rp->num_keys;
	}
}