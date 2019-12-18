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
typedef  int /*<<< orphan*/  u8 ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_cp_le_start_enc {int /*<<< orphan*/  handle; } ;
struct hci_conn {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_ERROR_AUTH_FAILURE ; 
 int /*<<< orphan*/  HCI_OP_LE_START_ENC ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_drop (struct hci_conn*) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_disconnect (struct hci_conn*,int /*<<< orphan*/ ) ; 
 struct hci_cp_le_start_enc* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cs_le_start_enc(struct hci_dev *hdev, u8 status)
{
	struct hci_cp_le_start_enc *cp;
	struct hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	if (!status)
		return;

	hci_dev_lock(hdev);

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_START_ENC);
	if (!cp)
		goto unlock;

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(cp->handle));
	if (!conn)
		goto unlock;

	if (conn->state != BT_CONNECTED)
		goto unlock;

	hci_disconnect(conn, HCI_ERROR_AUTH_FAILURE);
	hci_conn_drop(conn);

unlock:
	hci_dev_unlock(hdev);
}