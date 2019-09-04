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
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct mgmt_pending_cmd {int /*<<< orphan*/  cmd_complete; } ;
struct mgmt_cp_start_discovery {int /*<<< orphan*/  type; } ;
struct TYPE_2__ {scalar_t__ state; int report_invalid_rssi; int limited; int /*<<< orphan*/  type; } ;
struct hci_dev {int /*<<< orphan*/  discov_update; int /*<<< orphan*/  req_workqueue; TYPE_1__ discovery; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DISCOVERY_STARTING ; 
 scalar_t__ DISCOVERY_STOPPED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_PERIODIC_INQ ; 
 int /*<<< orphan*/  MGMT_OP_START_LIMITED_DISCOVERY ; 
 int /*<<< orphan*/  MGMT_STATUS_BUSY ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_POWERED ; 
 int /*<<< orphan*/  discovery_type_is_valid (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generic_cmd_complete ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_discovery_filter_clear (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_discovery_set_state (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdev_is_powered (struct hci_dev*) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int start_discovery_internal(struct sock *sk, struct hci_dev *hdev,
				    u16 op, void *data, u16 len)
{
	struct mgmt_cp_start_discovery *cp = data;
	struct mgmt_pending_cmd *cmd;
	u8 status;
	int err;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	if (!hdev_is_powered(hdev)) {
		err = mgmt_cmd_complete(sk, hdev->id, op,
					MGMT_STATUS_NOT_POWERED,
					&cp->type, sizeof(cp->type));
		goto failed;
	}

	if (hdev->discovery.state != DISCOVERY_STOPPED ||
	    hci_dev_test_flag(hdev, HCI_PERIODIC_INQ)) {
		err = mgmt_cmd_complete(sk, hdev->id, op, MGMT_STATUS_BUSY,
					&cp->type, sizeof(cp->type));
		goto failed;
	}

	if (!discovery_type_is_valid(hdev, cp->type, &status)) {
		err = mgmt_cmd_complete(sk, hdev->id, op, status,
					&cp->type, sizeof(cp->type));
		goto failed;
	}

	/* Clear the discovery filter first to free any previously
	 * allocated memory for the UUID list.
	 */
	hci_discovery_filter_clear(hdev);

	hdev->discovery.type = cp->type;
	hdev->discovery.report_invalid_rssi = false;
	if (op == MGMT_OP_START_LIMITED_DISCOVERY)
		hdev->discovery.limited = true;
	else
		hdev->discovery.limited = false;

	cmd = mgmt_pending_add(sk, op, hdev, data, len);
	if (!cmd) {
		err = -ENOMEM;
		goto failed;
	}

	cmd->cmd_complete = generic_cmd_complete;

	hci_discovery_set_state(hdev, DISCOVERY_STARTING);
	queue_work(hdev->req_workqueue, &hdev->discov_update);
	err = 0;

failed:
	hci_dev_unlock(hdev);
	return err;
}