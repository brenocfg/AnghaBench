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
struct mgmt_rp_get_clock_info {int /*<<< orphan*/  accuracy; void* piconet_clock; void* local_clock; int /*<<< orphan*/  addr; } ;
struct mgmt_pending_cmd {int /*<<< orphan*/  opcode; int /*<<< orphan*/  index; int /*<<< orphan*/  sk; int /*<<< orphan*/  param; struct hci_conn* user_data; } ;
struct hci_dev {int /*<<< orphan*/  clock; } ;
struct hci_conn {int /*<<< orphan*/  clock_accuracy; int /*<<< orphan*/  clock; } ;
typedef  int /*<<< orphan*/  rp ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_drop (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_conn_put (struct hci_conn*) ; 
 struct hci_dev* hci_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct mgmt_rp_get_clock_info*,int /*<<< orphan*/ ,int) ; 
 int mgmt_cmd_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct mgmt_rp_get_clock_info*,int) ; 

__attribute__((used)) static int clock_info_cmd_complete(struct mgmt_pending_cmd *cmd, u8 status)
{
	struct hci_conn *conn = cmd->user_data;
	struct mgmt_rp_get_clock_info rp;
	struct hci_dev *hdev;
	int err;

	memset(&rp, 0, sizeof(rp));
	memcpy(&rp.addr, cmd->param, sizeof(rp.addr));

	if (status)
		goto complete;

	hdev = hci_dev_get(cmd->index);
	if (hdev) {
		rp.local_clock = cpu_to_le32(hdev->clock);
		hci_dev_put(hdev);
	}

	if (conn) {
		rp.piconet_clock = cpu_to_le32(conn->clock);
		rp.accuracy = cpu_to_le16(conn->clock_accuracy);
	}

complete:
	err = mgmt_cmd_complete(cmd->sk, cmd->index, cmd->opcode, status, &rp,
				sizeof(rp));

	if (conn) {
		hci_conn_drop(conn);
		hci_conn_put(conn);
	}

	return err;
}