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
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_cp_remote_name_req {int /*<<< orphan*/  bdaddr; } ;
struct hci_cp_auth_requested {int /*<<< orphan*/  handle; } ;
struct hci_conn {int /*<<< orphan*/  handle; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  auth_cp ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_CONN_AUTH_INITIATOR ; 
 int /*<<< orphan*/  HCI_CONN_AUTH_PEND ; 
 int /*<<< orphan*/  HCI_MGMT ; 
 int /*<<< orphan*/  HCI_OP_AUTH_REQUESTED ; 
 int /*<<< orphan*/  HCI_OP_REMOTE_NAME_REQ ; 
 int /*<<< orphan*/  __cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_check_pending_name (struct hci_dev*,struct hci_conn*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_outgoing_auth_needed (struct hci_dev*,struct hci_conn*) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_auth_requested*) ; 
 struct hci_cp_remote_name_req* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_cs_remote_name_req(struct hci_dev *hdev, __u8 status)
{
	struct hci_cp_remote_name_req *cp;
	struct hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	/* If successful wait for the name req complete event before
	 * checking for the need to do authentication */
	if (!status)
		return;

	cp = hci_sent_cmd_data(hdev, HCI_OP_REMOTE_NAME_REQ);
	if (!cp)
		return;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &cp->bdaddr);

	if (hci_dev_test_flag(hdev, HCI_MGMT))
		hci_check_pending_name(hdev, conn, &cp->bdaddr, NULL, 0);

	if (!conn)
		goto unlock;

	if (!hci_outgoing_auth_needed(hdev, conn))
		goto unlock;

	if (!test_and_set_bit(HCI_CONN_AUTH_PEND, &conn->flags)) {
		struct hci_cp_auth_requested auth_cp;

		set_bit(HCI_CONN_AUTH_INITIATOR, &conn->flags);

		auth_cp.handle = __cpu_to_le16(conn->handle);
		hci_send_cmd(hdev, HCI_OP_AUTH_REQUESTED,
			     sizeof(auth_cp), &auth_cp);
	}

unlock:
	hci_dev_unlock(hdev);
}