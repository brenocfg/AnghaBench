#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct hci_request {TYPE_1__* hdev; } ;
struct hci_cp_reject_sync_conn_req {void* reason; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  handle; int /*<<< orphan*/  phy_handle; } ;
struct hci_cp_reject_conn_req {void* reason; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  handle; int /*<<< orphan*/  phy_handle; } ;
struct hci_cp_disconnect {void* reason; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  handle; int /*<<< orphan*/  phy_handle; } ;
struct hci_cp_disconn_phy_link {void* reason; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  handle; int /*<<< orphan*/  phy_handle; } ;
struct hci_conn {int state; struct hci_cp_reject_sync_conn_req dst; int /*<<< orphan*/  type; int /*<<< orphan*/  flags; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  rej ;
typedef  int /*<<< orphan*/  dc ;
typedef  int /*<<< orphan*/  cp ;
struct TYPE_2__ {int /*<<< orphan*/  hci_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 int /*<<< orphan*/  AMP_LINK ; 
 int /*<<< orphan*/  BLUETOOTH_VER_1_2 ; 
 int BT_CLOSED ; 
#define  BT_CONFIG 131 
#define  BT_CONNECT 130 
#define  BT_CONNECT2 129 
#define  BT_CONNECTED 128 
 int BT_DISCONN ; 
 int /*<<< orphan*/  ESCO_LINK ; 
 int /*<<< orphan*/  HCI_CONN_SCANNING ; 
 void* HCI_ERROR_REJ_LIMITED_RESOURCES ; 
 int /*<<< orphan*/  HCI_OP_CREATE_CONN_CANCEL ; 
 int /*<<< orphan*/  HCI_OP_DISCONNECT ; 
 int /*<<< orphan*/  HCI_OP_DISCONN_PHY_LINK ; 
 int /*<<< orphan*/  HCI_OP_LE_CREATE_CONN_CANCEL ; 
 int /*<<< orphan*/  HCI_OP_REJECT_CONN_REQ ; 
 int /*<<< orphan*/  HCI_OP_REJECT_SYNC_CONN_REQ ; 
 int /*<<< orphan*/  HCI_PHY_HANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LE_LINK ; 
 int /*<<< orphan*/  SCO_LINK ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,struct hci_cp_reject_sync_conn_req*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,struct hci_cp_reject_sync_conn_req*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __hci_abort_conn(struct hci_request *req, struct hci_conn *conn,
		      u8 reason)
{
	switch (conn->state) {
	case BT_CONNECTED:
	case BT_CONFIG:
		if (conn->type == AMP_LINK) {
			struct hci_cp_disconn_phy_link cp;

			cp.phy_handle = HCI_PHY_HANDLE(conn->handle);
			cp.reason = reason;
			hci_req_add(req, HCI_OP_DISCONN_PHY_LINK, sizeof(cp),
				    &cp);
		} else {
			struct hci_cp_disconnect dc;

			dc.handle = cpu_to_le16(conn->handle);
			dc.reason = reason;
			hci_req_add(req, HCI_OP_DISCONNECT, sizeof(dc), &dc);
		}

		conn->state = BT_DISCONN;

		break;
	case BT_CONNECT:
		if (conn->type == LE_LINK) {
			if (test_bit(HCI_CONN_SCANNING, &conn->flags))
				break;
			hci_req_add(req, HCI_OP_LE_CREATE_CONN_CANCEL,
				    0, NULL);
		} else if (conn->type == ACL_LINK) {
			if (req->hdev->hci_ver < BLUETOOTH_VER_1_2)
				break;
			hci_req_add(req, HCI_OP_CREATE_CONN_CANCEL,
				    6, &conn->dst);
		}
		break;
	case BT_CONNECT2:
		if (conn->type == ACL_LINK) {
			struct hci_cp_reject_conn_req rej;

			bacpy(&rej.bdaddr, &conn->dst);
			rej.reason = reason;

			hci_req_add(req, HCI_OP_REJECT_CONN_REQ,
				    sizeof(rej), &rej);
		} else if (conn->type == SCO_LINK || conn->type == ESCO_LINK) {
			struct hci_cp_reject_sync_conn_req rej;

			bacpy(&rej.bdaddr, &conn->dst);

			/* SCO rejection has its own limited set of
			 * allowed error values (0x0D-0x0F) which isn't
			 * compatible with most values passed to this
			 * function. To be safe hard-code one of the
			 * values that's suitable for SCO.
			 */
			rej.reason = HCI_ERROR_REJ_LIMITED_RESOURCES;

			hci_req_add(req, HCI_OP_REJECT_SYNC_CONN_REQ,
				    sizeof(rej), &rej);
		}
		break;
	default:
		conn->state = BT_CLOSED;
		break;
	}
}