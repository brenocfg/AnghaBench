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
struct hci_dev {int dummy; } ;
struct hci_cp_disconnect {int /*<<< orphan*/  handle; } ;
struct hci_conn {int /*<<< orphan*/  dst_type; int /*<<< orphan*/  type; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_OP_DISCONNECT ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct hci_cp_disconnect* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_disconnect_failed (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cs_disconnect(struct hci_dev *hdev, u8 status)
{
	struct hci_cp_disconnect *cp;
	struct hci_conn *conn;

	if (!status)
		return;

	cp = hci_sent_cmd_data(hdev, HCI_OP_DISCONNECT);
	if (!cp)
		return;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(cp->handle));
	if (conn)
		mgmt_disconnect_failed(hdev, &conn->dst, conn->type,
				       conn->dst_type, status);

	hci_dev_unlock(hdev);
}