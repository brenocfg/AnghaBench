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
struct sk_buff {scalar_t__ data; } ;
struct hci_dev {int /*<<< orphan*/  workqueue; int /*<<< orphan*/  name; } ;
struct hci_cp_le_set_ext_adv_enable {scalar_t__ enable; } ;
struct hci_conn {int /*<<< orphan*/  conn_timeout; int /*<<< orphan*/  le_conn_timeout; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HCI_LE_ADV ; 
 int /*<<< orphan*/  HCI_OP_LE_SET_EXT_ADV_ENABLE ; 
 int /*<<< orphan*/  hci_dev_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct hci_conn* hci_lookup_le_connect (struct hci_dev*) ; 
 struct hci_cp_le_set_ext_adv_enable* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_le_set_ext_adv_enable(struct hci_dev *hdev,
					 struct sk_buff *skb)
{
	struct hci_cp_le_set_ext_adv_enable *cp;
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	if (status)
		return;

	cp = hci_sent_cmd_data(hdev, HCI_OP_LE_SET_EXT_ADV_ENABLE);
	if (!cp)
		return;

	hci_dev_lock(hdev);

	if (cp->enable) {
		struct hci_conn *conn;

		hci_dev_set_flag(hdev, HCI_LE_ADV);

		conn = hci_lookup_le_connect(hdev);
		if (conn)
			queue_delayed_work(hdev->workqueue,
					   &conn->le_conn_timeout,
					   conn->conn_timeout);
	} else {
		hci_dev_clear_flag(hdev, HCI_LE_ADV);
	}

	hci_dev_unlock(hdev);
}