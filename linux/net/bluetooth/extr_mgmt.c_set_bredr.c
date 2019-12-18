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
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct mgmt_pending_cmd {int dummy; } ;
struct mgmt_mode {int val; } ;
struct hci_request {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  cur_adv_instance; int /*<<< orphan*/  id; int /*<<< orphan*/  static_addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDADDR_ANY ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_BREDR_ENABLED ; 
 int /*<<< orphan*/  HCI_DISCOVERABLE ; 
 int /*<<< orphan*/  HCI_FAST_CONNECTABLE ; 
 int /*<<< orphan*/  HCI_HS_ENABLED ; 
 int /*<<< orphan*/  HCI_LE_ENABLED ; 
 int /*<<< orphan*/  HCI_LINK_SECURITY ; 
 int /*<<< orphan*/  HCI_SC_ENABLED ; 
 int /*<<< orphan*/  HCI_SSP_ENABLED ; 
 int /*<<< orphan*/  MGMT_OP_SET_BREDR ; 
 int /*<<< orphan*/  MGMT_STATUS_BUSY ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  MGMT_STATUS_REJECTED ; 
 int /*<<< orphan*/  __hci_req_update_adv_data (struct hci_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __hci_req_update_scan (struct hci_request*) ; 
 int /*<<< orphan*/  __hci_req_write_fast_connectable (struct hci_request*,int) ; 
 scalar_t__ bacmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_change_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 int hci_req_run (struct hci_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdev_is_powered (struct hci_dev*) ; 
 int /*<<< orphan*/  lmp_bredr_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  lmp_le_capable (struct hci_dev*) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int new_settings (struct hci_dev*,struct sock*) ; 
 scalar_t__ pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 
 int send_settings_rsp (struct sock*,int /*<<< orphan*/ ,struct hci_dev*) ; 
 int /*<<< orphan*/  set_bredr_complete ; 

__attribute__((used)) static int set_bredr(struct sock *sk, struct hci_dev *hdev, void *data, u16 len)
{
	struct mgmt_mode *cp = data;
	struct mgmt_pending_cmd *cmd;
	struct hci_request req;
	int err;

	BT_DBG("request for %s", hdev->name);

	if (!lmp_bredr_capable(hdev) || !lmp_le_capable(hdev))
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_BREDR,
				       MGMT_STATUS_NOT_SUPPORTED);

	if (!hci_dev_test_flag(hdev, HCI_LE_ENABLED))
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_BREDR,
				       MGMT_STATUS_REJECTED);

	if (cp->val != 0x00 && cp->val != 0x01)
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_BREDR,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	if (cp->val == hci_dev_test_flag(hdev, HCI_BREDR_ENABLED)) {
		err = send_settings_rsp(sk, MGMT_OP_SET_BREDR, hdev);
		goto unlock;
	}

	if (!hdev_is_powered(hdev)) {
		if (!cp->val) {
			hci_dev_clear_flag(hdev, HCI_DISCOVERABLE);
			hci_dev_clear_flag(hdev, HCI_SSP_ENABLED);
			hci_dev_clear_flag(hdev, HCI_LINK_SECURITY);
			hci_dev_clear_flag(hdev, HCI_FAST_CONNECTABLE);
			hci_dev_clear_flag(hdev, HCI_HS_ENABLED);
		}

		hci_dev_change_flag(hdev, HCI_BREDR_ENABLED);

		err = send_settings_rsp(sk, MGMT_OP_SET_BREDR, hdev);
		if (err < 0)
			goto unlock;

		err = new_settings(hdev, sk);
		goto unlock;
	}

	/* Reject disabling when powered on */
	if (!cp->val) {
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_BREDR,
				      MGMT_STATUS_REJECTED);
		goto unlock;
	} else {
		/* When configuring a dual-mode controller to operate
		 * with LE only and using a static address, then switching
		 * BR/EDR back on is not allowed.
		 *
		 * Dual-mode controllers shall operate with the public
		 * address as its identity address for BR/EDR and LE. So
		 * reject the attempt to create an invalid configuration.
		 *
		 * The same restrictions applies when secure connections
		 * has been enabled. For BR/EDR this is a controller feature
		 * while for LE it is a host stack feature. This means that
		 * switching BR/EDR back on when secure connections has been
		 * enabled is not a supported transaction.
		 */
		if (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED) &&
		    (bacmp(&hdev->static_addr, BDADDR_ANY) ||
		     hci_dev_test_flag(hdev, HCI_SC_ENABLED))) {
			err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_BREDR,
					      MGMT_STATUS_REJECTED);
			goto unlock;
		}
	}

	if (pending_find(MGMT_OP_SET_BREDR, hdev)) {
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_BREDR,
				      MGMT_STATUS_BUSY);
		goto unlock;
	}

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_BREDR, hdev, data, len);
	if (!cmd) {
		err = -ENOMEM;
		goto unlock;
	}

	/* We need to flip the bit already here so that
	 * hci_req_update_adv_data generates the correct flags.
	 */
	hci_dev_set_flag(hdev, HCI_BREDR_ENABLED);

	hci_req_init(&req, hdev);

	__hci_req_write_fast_connectable(&req, false);
	__hci_req_update_scan(&req);

	/* Since only the advertising data flags will change, there
	 * is no need to update the scan response data.
	 */
	__hci_req_update_adv_data(&req, hdev->cur_adv_instance);

	err = hci_req_run(&req, set_bredr_complete);
	if (err < 0)
		mgmt_pending_remove(cmd);

unlock:
	hci_dev_unlock(hdev);
	return err;
}