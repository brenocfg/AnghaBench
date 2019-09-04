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
struct mgmt_pending_cmd {int /*<<< orphan*/  (* cmd_complete ) (struct mgmt_pending_cmd*,int /*<<< orphan*/ ) ;} ;
struct hci_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_STATUS_FAILED ; 
 int /*<<< orphan*/  MGMT_STATUS_SUCCESS ; 
 struct mgmt_pending_cmd* find_pairing (struct hci_conn*) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int /*<<< orphan*/  stub1 (struct mgmt_pending_cmd*,int /*<<< orphan*/ ) ; 

void mgmt_smp_complete(struct hci_conn *conn, bool complete)
{
	u8 status = complete ? MGMT_STATUS_SUCCESS : MGMT_STATUS_FAILED;
	struct mgmt_pending_cmd *cmd;

	cmd = find_pairing(conn);
	if (cmd) {
		cmd->cmd_complete(cmd, status);
		mgmt_pending_remove(cmd);
	}
}