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
struct hci_request {int dummy; } ;
struct hci_conn {int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  __hci_abort_conn (struct hci_request*,struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort_conn_complete ; 
 int /*<<< orphan*/  bt_dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,int /*<<< orphan*/ ) ; 
 int hci_req_run (struct hci_request*,int /*<<< orphan*/ ) ; 

int hci_abort_conn(struct hci_conn *conn, u8 reason)
{
	struct hci_request req;
	int err;

	hci_req_init(&req, conn->hdev);

	__hci_abort_conn(&req, conn, reason);

	err = hci_req_run(&req, abort_conn_complete);
	if (err && err != -ENODATA) {
		bt_dev_err(conn->hdev, "failed to run HCI request: err %d", err);
		return err;
	}

	return 0;
}