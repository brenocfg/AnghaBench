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
struct hci_dev {int dummy; } ;
struct hci_cp_reject_conn_req {int /*<<< orphan*/  reason; int /*<<< orphan*/  bdaddr; } ;
typedef  int /*<<< orphan*/  cp ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_ERROR_REJ_BAD_ADDR ; 
 int /*<<< orphan*/  HCI_OP_REJECT_CONN_REQ ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_reject_conn_req*) ; 

__attribute__((used)) static void hci_reject_conn(struct hci_dev *hdev, bdaddr_t *bdaddr)
{
	struct hci_cp_reject_conn_req cp;

	bacpy(&cp.bdaddr, bdaddr);
	cp.reason = HCI_ERROR_REJ_BAD_ADDR;
	hci_send_cmd(hdev, HCI_OP_REJECT_CONN_REQ, sizeof(cp), &cp);
}