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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_cp_accept_phy_link {int /*<<< orphan*/  phy_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HCI_OP_ACCEPT_PHY_LINK ; 
 int /*<<< orphan*/  amp_write_remote_assoc (struct hci_dev*,int /*<<< orphan*/ ) ; 
 struct hci_cp_accept_phy_link* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void accept_phylink_complete(struct hci_dev *hdev, u8 status,
				    u16 opcode)
{
	struct hci_cp_accept_phy_link *cp;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	if (status)
		return;

	cp = hci_sent_cmd_data(hdev, HCI_OP_ACCEPT_PHY_LINK);
	if (!cp)
		return;

	amp_write_remote_assoc(hdev, cp->phy_handle);
}