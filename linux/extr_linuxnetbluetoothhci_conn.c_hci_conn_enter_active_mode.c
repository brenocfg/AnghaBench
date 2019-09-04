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
struct hci_dev {scalar_t__ idle_timeout; int /*<<< orphan*/  workqueue; } ;
struct hci_cp_exit_sniff_mode {int /*<<< orphan*/  handle; } ;
struct hci_conn {scalar_t__ mode; int /*<<< orphan*/  idle_work; int /*<<< orphan*/  handle; int /*<<< orphan*/  flags; struct hci_dev* hdev; } ;
typedef  int /*<<< orphan*/  cp ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*,scalar_t__) ; 
 scalar_t__ HCI_CM_SNIFF ; 
 int /*<<< orphan*/  HCI_CONN_MODE_CHANGE_PEND ; 
 int /*<<< orphan*/  HCI_CONN_POWER_SAVE ; 
 int /*<<< orphan*/  HCI_OP_EXIT_SNIFF_MODE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_exit_sniff_mode*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void hci_conn_enter_active_mode(struct hci_conn *conn, __u8 force_active)
{
	struct hci_dev *hdev = conn->hdev;

	BT_DBG("hcon %p mode %d", conn, conn->mode);

	if (conn->mode != HCI_CM_SNIFF)
		goto timer;

	if (!test_bit(HCI_CONN_POWER_SAVE, &conn->flags) && !force_active)
		goto timer;

	if (!test_and_set_bit(HCI_CONN_MODE_CHANGE_PEND, &conn->flags)) {
		struct hci_cp_exit_sniff_mode cp;
		cp.handle = cpu_to_le16(conn->handle);
		hci_send_cmd(hdev, HCI_OP_EXIT_SNIFF_MODE, sizeof(cp), &cp);
	}

timer:
	if (hdev->idle_timeout > 0)
		queue_delayed_work(hdev->workqueue, &conn->idle_work,
				   msecs_to_jiffies(hdev->idle_timeout));
}