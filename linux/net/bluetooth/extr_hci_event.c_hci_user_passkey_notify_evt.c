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
struct hci_ev_user_passkey_notify {int /*<<< orphan*/  passkey; int /*<<< orphan*/  bdaddr; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_conn {scalar_t__ passkey_entered; int /*<<< orphan*/  passkey_notify; int /*<<< orphan*/  dst_type; int /*<<< orphan*/  type; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_MGMT ; 
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_user_passkey_notify (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hci_user_passkey_notify_evt(struct hci_dev *hdev,
					struct sk_buff *skb)
{
	struct hci_ev_user_passkey_notify *ev = (void *) skb->data;
	struct hci_conn *conn;

	BT_DBG("%s", hdev->name);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &ev->bdaddr);
	if (!conn)
		return;

	conn->passkey_notify = __le32_to_cpu(ev->passkey);
	conn->passkey_entered = 0;

	if (hci_dev_test_flag(hdev, HCI_MGMT))
		mgmt_user_passkey_notify(hdev, &conn->dst, conn->type,
					 conn->dst_type, conn->passkey_notify,
					 conn->passkey_entered);
}