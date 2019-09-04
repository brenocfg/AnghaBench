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
struct mgmt_cp_set_scan_params {int /*<<< orphan*/  window; int /*<<< orphan*/  interval; } ;
struct hci_request {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; } ;
struct hci_dev {int le_scan_interval; int le_scan_window; TYPE_1__ discovery; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ DISCOVERY_STOPPED ; 
 int /*<<< orphan*/  HCI_LE_SCAN ; 
 int /*<<< orphan*/  MGMT_OP_SET_SCAN_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_SUPPORTED ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_add_le_passive_scan (struct hci_request*) ; 
 int /*<<< orphan*/  hci_req_add_le_scan_disable (struct hci_request*) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_run (struct hci_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lmp_le_capable (struct hci_dev*) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_scan_params(struct sock *sk, struct hci_dev *hdev,
			   void *data, u16 len)
{
	struct mgmt_cp_set_scan_params *cp = data;
	__u16 interval, window;
	int err;

	BT_DBG("%s", hdev->name);

	if (!lmp_le_capable(hdev))
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SCAN_PARAMS,
				       MGMT_STATUS_NOT_SUPPORTED);

	interval = __le16_to_cpu(cp->interval);

	if (interval < 0x0004 || interval > 0x4000)
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SCAN_PARAMS,
				       MGMT_STATUS_INVALID_PARAMS);

	window = __le16_to_cpu(cp->window);

	if (window < 0x0004 || window > 0x4000)
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SCAN_PARAMS,
				       MGMT_STATUS_INVALID_PARAMS);

	if (window > interval)
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SCAN_PARAMS,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	hdev->le_scan_interval = interval;
	hdev->le_scan_window = window;

	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_SET_SCAN_PARAMS, 0,
				NULL, 0);

	/* If background scan is running, restart it so new parameters are
	 * loaded.
	 */
	if (hci_dev_test_flag(hdev, HCI_LE_SCAN) &&
	    hdev->discovery.state == DISCOVERY_STOPPED) {
		struct hci_request req;

		hci_req_init(&req, hdev);

		hci_req_add_le_scan_disable(&req);
		hci_req_add_le_passive_scan(&req);

		hci_req_run(&req, NULL);
	}

	hci_dev_unlock(hdev);

	return err;
}