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
typedef  int u16 ;
struct l2cap_conn_req {int dummy; } ;
struct l2cap_conn {struct hci_conn* hcon; } ;
struct l2cap_cmd_hdr {int dummy; } ;
struct hci_dev {int dummy; } ;
struct hci_conn {int /*<<< orphan*/  flags; struct hci_dev* hdev; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  HCI_CONN_MGMT_CONNECTED ; 
 int /*<<< orphan*/  HCI_MGMT ; 
 int /*<<< orphan*/  L2CAP_CONN_RSP ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  l2cap_connect (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_device_connected (struct hci_dev*,struct hci_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2cap_connect_req(struct l2cap_conn *conn,
			     struct l2cap_cmd_hdr *cmd, u16 cmd_len, u8 *data)
{
	struct hci_dev *hdev = conn->hcon->hdev;
	struct hci_conn *hcon = conn->hcon;

	if (cmd_len < sizeof(struct l2cap_conn_req))
		return -EPROTO;

	hci_dev_lock(hdev);
	if (hci_dev_test_flag(hdev, HCI_MGMT) &&
	    !test_and_set_bit(HCI_CONN_MGMT_CONNECTED, &hcon->flags))
		mgmt_device_connected(hdev, hcon, 0, NULL, 0);
	hci_dev_unlock(hdev);

	l2cap_connect(conn, cmd, data, L2CAP_CONN_RSP, 0);
	return 0;
}