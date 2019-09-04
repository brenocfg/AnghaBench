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
typedef  int /*<<< orphan*/  u16 ;
struct hci_dev {int dummy; } ;
struct hci_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_connect_le_scan_cleanup (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_le_conn_failed (struct hci_conn*,int /*<<< orphan*/ ) ; 
 struct hci_conn* hci_lookup_le_connect (struct hci_dev*) ; 

__attribute__((used)) static void create_le_conn_complete(struct hci_dev *hdev, u8 status, u16 opcode)
{
	struct hci_conn *conn;

	hci_dev_lock(hdev);

	conn = hci_lookup_le_connect(hdev);

	if (!status) {
		hci_connect_le_scan_cleanup(conn);
		goto done;
	}

	bt_dev_err(hdev, "request failed to create LE connection: "
		   "status 0x%2.2x", status);

	if (!conn)
		goto done;

	hci_le_conn_failed(conn, status);

done:
	hci_dev_unlock(hdev);
}