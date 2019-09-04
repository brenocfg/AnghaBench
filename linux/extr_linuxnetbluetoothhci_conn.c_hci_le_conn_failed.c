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
struct hci_dev {int /*<<< orphan*/  pend_le_conns; } ;
struct hci_conn_params {scalar_t__ explicit_connect; int /*<<< orphan*/ * conn; } ;
struct hci_conn {int /*<<< orphan*/  dst_type; int /*<<< orphan*/  type; int /*<<< orphan*/  dst; int /*<<< orphan*/  state; struct hci_dev* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CLOSED ; 
 int /*<<< orphan*/  HCI_ERROR_UNKNOWN_CONN_ID ; 
 int /*<<< orphan*/  hci_conn_del (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_conn_drop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_conn_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_connect_cfm (struct hci_conn*,int /*<<< orphan*/ ) ; 
 struct hci_conn_params* hci_pend_le_action_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_reenable_advertising (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_update_background_scan (struct hci_dev*) ; 
 int /*<<< orphan*/  mgmt_connect_failed (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hci_le_conn_failed(struct hci_conn *conn, u8 status)
{
	struct hci_dev *hdev = conn->hdev;
	struct hci_conn_params *params;

	params = hci_pend_le_action_lookup(&hdev->pend_le_conns, &conn->dst,
					   conn->dst_type);
	if (params && params->conn) {
		hci_conn_drop(params->conn);
		hci_conn_put(params->conn);
		params->conn = NULL;
	}

	conn->state = BT_CLOSED;

	/* If the status indicates successful cancellation of
	 * the attempt (i.e. Unkown Connection Id) there's no point of
	 * notifying failure since we'll go back to keep trying to
	 * connect. The only exception is explicit connect requests
	 * where a timeout + cancel does indicate an actual failure.
	 */
	if (status != HCI_ERROR_UNKNOWN_CONN_ID ||
	    (params && params->explicit_connect))
		mgmt_connect_failed(hdev, &conn->dst, conn->type,
				    conn->dst_type, status);

	hci_connect_cfm(conn, status);

	hci_conn_del(conn);

	/* Since we may have temporarily stopped the background scanning in
	 * favor of connection establishment, we should restart it.
	 */
	hci_update_background_scan(hdev);

	/* Re-enable advertising in case this was a failed connection
	 * attempt as a peripheral.
	 */
	hci_req_reenable_advertising(hdev);
}