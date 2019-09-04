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
struct hci_cp_switch_role {scalar_t__ role; int /*<<< orphan*/  bdaddr; } ;
struct hci_conn {scalar_t__ role; int /*<<< orphan*/  hdev; int /*<<< orphan*/  dst; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  cp ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*) ; 
 int /*<<< orphan*/  HCI_CONN_RSWITCH_PEND ; 
 int /*<<< orphan*/  HCI_OP_SWITCH_ROLE ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_send_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct hci_cp_switch_role*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hci_conn_switch_role(struct hci_conn *conn, __u8 role)
{
	BT_DBG("hcon %p", conn);

	if (role == conn->role)
		return 1;

	if (!test_and_set_bit(HCI_CONN_RSWITCH_PEND, &conn->flags)) {
		struct hci_cp_switch_role cp;
		bacpy(&cp.bdaddr, &conn->dst);
		cp.role = role;
		hci_send_cmd(conn->hdev, HCI_OP_SWITCH_ROLE, sizeof(cp), &cp);
	}

	return 0;
}