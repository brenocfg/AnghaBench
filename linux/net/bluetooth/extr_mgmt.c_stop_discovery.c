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
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct mgmt_pending_cmd {int /*<<< orphan*/  cmd_complete; } ;
struct mgmt_cp_stop_discovery {scalar_t__ type; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct hci_dev {int /*<<< orphan*/  discov_update; int /*<<< orphan*/  req_workqueue; int /*<<< orphan*/  id; TYPE_1__ discovery; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DISCOVERY_STOPPING ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MGMT_OP_STOP_DISCOVERY ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_REJECTED ; 
 int /*<<< orphan*/  generic_cmd_complete ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_discovery_active (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_discovery_set_state (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stop_discovery(struct sock *sk, struct hci_dev *hdev, void *data,
			  u16 len)
{
	struct mgmt_cp_stop_discovery *mgmt_cp = data;
	struct mgmt_pending_cmd *cmd;
	int err;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	if (!hci_discovery_active(hdev)) {
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_STOP_DISCOVERY,
					MGMT_STATUS_REJECTED, &mgmt_cp->type,
					sizeof(mgmt_cp->type));
		goto unlock;
	}

	if (hdev->discovery.type != mgmt_cp->type) {
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_STOP_DISCOVERY,
					MGMT_STATUS_INVALID_PARAMS,
					&mgmt_cp->type, sizeof(mgmt_cp->type));
		goto unlock;
	}

	cmd = mgmt_pending_add(sk, MGMT_OP_STOP_DISCOVERY, hdev, data, len);
	if (!cmd) {
		err = -ENOMEM;
		goto unlock;
	}

	cmd->cmd_complete = generic_cmd_complete;

	hci_discovery_set_state(hdev, DISCOVERY_STOPPING);
	queue_work(hdev->req_workqueue, &hdev->discov_update);
	err = 0;

unlock:
	hci_dev_unlock(hdev);
	return err;
}