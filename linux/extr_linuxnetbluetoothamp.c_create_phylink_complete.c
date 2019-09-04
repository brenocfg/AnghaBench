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
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_cp_create_phy_link {int /*<<< orphan*/  phy_handle; } ;
struct hci_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_OP_CREATE_PHY_LINK ; 
 int /*<<< orphan*/  amp_write_remote_assoc (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_del (struct hci_conn*) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct hci_cp_create_phy_link* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void create_phylink_complete(struct hci_dev *hdev, u8 status,
				    u16 opcode)
{
	struct hci_cp_create_phy_link *cp;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	cp = hci_sent_cmd_data(hdev, HCI_OP_CREATE_PHY_LINK);
	if (!cp)
		return;

	hci_dev_lock(hdev);

	if (status) {
		struct hci_conn *hcon;

		hcon = hci_conn_hash_lookup_handle(hdev, cp->phy_handle);
		if (hcon)
			hci_conn_del(hcon);
	} else {
		amp_write_remote_assoc(hdev, cp->phy_handle);
	}

	hci_dev_unlock(hdev);
}