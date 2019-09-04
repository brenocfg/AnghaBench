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
struct hci_rp_write_link_policy {int /*<<< orphan*/  handle; scalar_t__ status; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_conn {int /*<<< orphan*/  link_policy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HCI_OP_WRITE_LINK_POLICY ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_unaligned_le16 (void*) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 void* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_write_link_policy(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_rp_write_link_policy *rp = (void *) skb->data;
	struct hci_conn *conn;
	void *sent;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	if (rp->status)
		return;

	sent = hci_sent_cmd_data(hdev, HCI_OP_WRITE_LINK_POLICY);
	if (!sent)
		return;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(rp->handle));
	if (conn)
		conn->link_policy = get_unaligned_le16(sent + 2);

	hci_dev_unlock(hdev);
}