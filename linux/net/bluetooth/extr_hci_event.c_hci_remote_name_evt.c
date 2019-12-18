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
struct hci_ev_remote_name {scalar_t__ status; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/ * name; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_cp_auth_requested {int /*<<< orphan*/  handle; } ;
struct hci_conn {int /*<<< orphan*/  handle; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_CONN_AUTH_INITIATOR ; 
 int /*<<< orphan*/  HCI_CONN_AUTH_PEND ; 
 int /*<<< orphan*/  HCI_MAX_NAME_LENGTH ; 
 int /*<<< orphan*/  HCI_MGMT ; 
 int /*<<< orphan*/  HCI_OP_AUTH_REQUESTED ; 
 int /*<<< orphan*/  __cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_check_pending_name (struct hci_dev*,struct hci_conn*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_check_pending (struct hci_dev*) ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_outgoing_auth_needed (struct hci_dev*,struct hci_conn*) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_auth_requested*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strnlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_remote_name_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_ev_remote_name *ev = (void *) skb->data;
	struct hci_conn *conn;

	BT_DBG("%s", hdev->name);

	hci_conn_check_pending(hdev);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &ev->bdaddr);

	if (!hci_dev_test_flag(hdev, HCI_MGMT))
		goto check_auth;

	if (ev->status == 0)
		hci_check_pending_name(hdev, conn, &ev->bdaddr, ev->name,
				       strnlen(ev->name, HCI_MAX_NAME_LENGTH));
	else
		hci_check_pending_name(hdev, conn, &ev->bdaddr, NULL, 0);

check_auth:
	if (!conn)
		goto unlock;

	if (!hci_outgoing_auth_needed(hdev, conn))
		goto unlock;

	if (!test_and_set_bit(HCI_CONN_AUTH_PEND, &conn->flags)) {
		struct hci_cp_auth_requested cp;

		set_bit(HCI_CONN_AUTH_INITIATOR, &conn->flags);

		cp.handle = __cpu_to_le16(conn->handle);
		hci_send_cmd(hdev, HCI_OP_AUTH_REQUESTED, sizeof(cp), &cp);
	}

unlock:
	hci_dev_unlock(hdev);
}