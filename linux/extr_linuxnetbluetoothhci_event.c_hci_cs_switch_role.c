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
struct hci_cp_switch_role {int /*<<< orphan*/  bdaddr; } ;
struct hci_conn {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_CONN_RSWITCH_PEND ; 
 int /*<<< orphan*/  HCI_OP_SWITCH_ROLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct hci_cp_switch_role* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cs_switch_role(struct hci_dev *hdev, u8 status)
{
	struct hci_cp_switch_role *cp;
	struct hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	if (!status)
		return;

	cp = hci_sent_cmd_data(hdev, HCI_OP_SWITCH_ROLE);
	if (!cp)
		return;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ACL_LINK, &cp->bdaddr);
	if (conn)
		clear_bit(HCI_CONN_RSWITCH_PEND, &conn->flags);

	hci_dev_unlock(hdev);
}