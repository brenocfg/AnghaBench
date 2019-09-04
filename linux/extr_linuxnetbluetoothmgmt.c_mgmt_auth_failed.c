#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mgmt_pending_cmd {int /*<<< orphan*/  (* cmd_complete ) (struct mgmt_pending_cmd*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * sk; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/  bdaddr; } ;
struct mgmt_ev_auth_failed {int /*<<< orphan*/  status; TYPE_1__ addr; } ;
struct hci_conn {int /*<<< orphan*/  hdev; int /*<<< orphan*/  dst_type; int /*<<< orphan*/  type; int /*<<< orphan*/  dst; } ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
 int /*<<< orphan*/  MGMT_EV_AUTH_FAILED ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mgmt_pending_cmd* find_pairing (struct hci_conn*) ; 
 int /*<<< orphan*/  link_to_bdaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mgmt_ev_auth_failed*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int /*<<< orphan*/  mgmt_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mgmt_pending_cmd*,int /*<<< orphan*/ ) ; 

void mgmt_auth_failed(struct hci_conn *conn, u8 hci_status)
{
	struct mgmt_ev_auth_failed ev;
	struct mgmt_pending_cmd *cmd;
	u8 status = mgmt_status(hci_status);

	bacpy(&ev.addr.bdaddr, &conn->dst);
	ev.addr.type = link_to_bdaddr(conn->type, conn->dst_type);
	ev.status = status;

	cmd = find_pairing(conn);

	mgmt_event(MGMT_EV_AUTH_FAILED, conn->hdev, &ev, sizeof(ev),
		    cmd ? cmd->sk : NULL);

	if (cmd) {
		cmd->cmd_complete(cmd, status);
		mgmt_pending_remove(cmd);
	}
}