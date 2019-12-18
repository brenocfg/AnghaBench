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
struct hci_cp_read_clock_offset {int /*<<< orphan*/  handle; } ;
struct hci_conn {scalar_t__ type; scalar_t__ role; scalar_t__ state; int /*<<< orphan*/  handle; struct hci_dev* hdev; } ;
typedef  int /*<<< orphan*/  clkoff_cp ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 scalar_t__ ACL_LINK ; 
 scalar_t__ BT_CONFIG ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*) ; 
 int /*<<< orphan*/  HCI_OP_READ_CLOCK_OFFSET ; 
 scalar_t__ HCI_ROLE_MASTER ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int hci_abort_conn (struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_read_clock_offset*) ; 

int hci_disconnect(struct hci_conn *conn, __u8 reason)
{
	BT_DBG("hcon %p", conn);

	/* When we are master of an established connection and it enters
	 * the disconnect timeout, then go ahead and try to read the
	 * current clock offset.  Processing of the result is done
	 * within the event handling and hci_clock_offset_evt function.
	 */
	if (conn->type == ACL_LINK && conn->role == HCI_ROLE_MASTER &&
	    (conn->state == BT_CONNECTED || conn->state == BT_CONFIG)) {
		struct hci_dev *hdev = conn->hdev;
		struct hci_cp_read_clock_offset clkoff_cp;

		clkoff_cp.handle = cpu_to_le16(conn->handle);
		hci_send_cmd(hdev, HCI_OP_READ_CLOCK_OFFSET, sizeof(clkoff_cp),
			     &clkoff_cp);
	}

	return hci_abort_conn(conn, reason);
}