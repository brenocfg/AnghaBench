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
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_cp_exit_sniff_mode {int /*<<< orphan*/  handle; } ;
struct hci_conn {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_CONN_MODE_CHANGE_PEND ; 
 int /*<<< orphan*/  HCI_CONN_SCO_SETUP_PEND ; 
 int /*<<< orphan*/  HCI_OP_EXIT_SNIFF_MODE ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_sco_setup (struct hci_conn*,int /*<<< orphan*/ ) ; 
 struct hci_cp_exit_sniff_mode* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_cs_exit_sniff_mode(struct hci_dev *hdev, __u8 status)
{
	struct hci_cp_exit_sniff_mode *cp;
	struct hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	if (!status)
		return;

	cp = hci_sent_cmd_data(hdev, HCI_OP_EXIT_SNIFF_MODE);
	if (!cp)
		return;

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(cp->handle));
	if (conn) {
		clear_bit(HCI_CONN_MODE_CHANGE_PEND, &conn->flags);

		if (test_and_clear_bit(HCI_CONN_SCO_SETUP_PEND, &conn->flags))
			hci_sco_setup(conn, status);
	}

	hci_dev_unlock(hdev);
}