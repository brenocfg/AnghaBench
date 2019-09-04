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
struct sk_buff {int len; scalar_t__ data; } ;
struct hci_rp_read_clock {int /*<<< orphan*/  accuracy; int /*<<< orphan*/  clock; int /*<<< orphan*/  handle; scalar_t__ status; } ;
struct hci_dev {void* clock; int /*<<< orphan*/  name; } ;
struct hci_cp_read_clock {int which; } ;
struct hci_conn {int /*<<< orphan*/  clock_accuracy; void* clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_OP_READ_CLOCK ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct hci_cp_read_clock* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_read_clock(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_rp_read_clock *rp = (void *) skb->data;
	struct hci_cp_read_clock *cp;
	struct hci_conn *conn;

	BT_DBG("%s", hdev->name);

	if (skb->len < sizeof(*rp))
		return;

	if (rp->status)
		return;

	hci_dev_lock(hdev);

	cp = hci_sent_cmd_data(hdev, HCI_OP_READ_CLOCK);
	if (!cp)
		goto unlock;

	if (cp->which == 0x00) {
		hdev->clock = le32_to_cpu(rp->clock);
		goto unlock;
	}

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(rp->handle));
	if (conn) {
		conn->clock = le32_to_cpu(rp->clock);
		conn->clock_accuracy = le16_to_cpu(rp->accuracy);
	}

unlock:
	hci_dev_unlock(hdev);
}