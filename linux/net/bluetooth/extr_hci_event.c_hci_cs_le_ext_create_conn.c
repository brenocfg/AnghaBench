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
struct hci_cp_le_ext_create_conn {int /*<<< orphan*/  filter_policy; int /*<<< orphan*/  own_addr_type; int /*<<< orphan*/  peer_addr_type; int /*<<< orphan*/  peer_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_OP_LE_EXT_CREATE_CONN ; 
 int /*<<< orphan*/  cs_le_create_conn (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct hci_cp_le_ext_create_conn* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cs_le_ext_create_conn(struct hci_dev *hdev, u8 status)
{
	struct hci_cp_le_ext_create_conn *cp;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	/* All connection failure handling is taken care of by the
	 * hci_le_conn_failed function which is triggered by the HCI
	 * request completion callbacks used for connecting.
	 */
	if (status)
		return;

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_EXT_CREATE_CONN);
	if (!cp)
		return;

	hci_dev_lock(hdev);

	cs_le_create_conn(hdev, &cp->peer_addr, cp->peer_addr_type,
			  cp->own_addr_type, cp->filter_policy);

	hci_dev_unlock(hdev);
}