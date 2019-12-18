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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct mgmt_pending_cmd {int dummy; } ;
struct mgmt_mode {int val; } ;
struct hci_request {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct hci_cp_write_le_host_supported {int le; int simul; } ;
typedef  int /*<<< orphan*/  hci_cp ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_ADVERTISING ; 
 int /*<<< orphan*/  HCI_BREDR_ENABLED ; 
 int /*<<< orphan*/  HCI_LE_ADV ; 
 int /*<<< orphan*/  HCI_LE_ENABLED ; 
 int /*<<< orphan*/  HCI_OP_WRITE_LE_HOST_SUPPORTED ; 
 int /*<<< orphan*/  MGMT_OP_SET_ADVERTISING ; 
 int /*<<< orphan*/  MGMT_OP_SET_LE ; 
 int /*<<< orphan*/  MGMT_STATUS_BUSY ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  MGMT_STATUS_REJECTED ; 
 int /*<<< orphan*/  __hci_req_clear_ext_adv_sets (struct hci_request*) ; 
 int /*<<< orphan*/  __hci_req_disable_advertising (struct hci_request*) ; 
 scalar_t__ ext_adv_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_change_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,struct hci_cp_write_le_host_supported*) ; 
 int /*<<< orphan*/  hci_req_clear_adv_instance (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 int hci_req_run (struct hci_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdev_is_powered (struct hci_dev*) ; 
 int /*<<< orphan*/  le_enable_complete ; 
 int lmp_host_le_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  lmp_le_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  memset (struct hci_cp_write_le_host_supported*,int /*<<< orphan*/ ,int) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int new_settings (struct hci_dev*,struct sock*) ; 
 scalar_t__ pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 
 int send_settings_rsp (struct sock*,int /*<<< orphan*/ ,struct hci_dev*) ; 

__attribute__((used)) static int set_le(struct sock *sk, struct hci_dev *hdev, void *data, u16 len)
{
	struct mgmt_mode *cp = data;
	struct hci_cp_write_le_host_supported hci_cp;
	struct mgmt_pending_cmd *cmd;
	struct hci_request req;
	int err;
	u8 val, enabled;

	BT_DBG("request for %s", hdev->name);

	if (!lmp_le_capable(hdev))
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_LE,
				       MGMT_STATUS_NOT_SUPPORTED);

	if (cp->val != 0x00 && cp->val != 0x01)
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_LE,
				       MGMT_STATUS_INVALID_PARAMS);

	/* Bluetooth single mode LE only controllers or dual-mode
	 * controllers configured as LE only devices, do not allow
	 * switching LE off. These have either LE enabled explicitly
	 * or BR/EDR has been previously switched off.
	 *
	 * When trying to enable an already enabled LE, then gracefully
	 * send a positive response. Trying to disable it however will
	 * result into rejection.
	 */
	if (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED)) {
		if (cp->val == 0x01)
			return send_settings_rsp(sk, MGMT_OP_SET_LE, hdev);

		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_LE,
				       MGMT_STATUS_REJECTED);
	}

	hci_dev_lock(hdev);

	val = !!cp->val;
	enabled = lmp_host_le_capable(hdev);

	if (!val)
		hci_req_clear_adv_instance(hdev, NULL, NULL, 0x00, true);

	if (!hdev_is_powered(hdev) || val == enabled) {
		bool changed = false;

		if (val != hci_dev_test_flag(hdev, HCI_LE_ENABLED)) {
			hci_dev_change_flag(hdev, HCI_LE_ENABLED);
			changed = true;
		}

		if (!val && hci_dev_test_flag(hdev, HCI_ADVERTISING)) {
			hci_dev_clear_flag(hdev, HCI_ADVERTISING);
			changed = true;
		}

		err = send_settings_rsp(sk, MGMT_OP_SET_LE, hdev);
		if (err < 0)
			goto unlock;

		if (changed)
			err = new_settings(hdev, sk);

		goto unlock;
	}

	if (pending_find(MGMT_OP_SET_LE, hdev) ||
	    pending_find(MGMT_OP_SET_ADVERTISING, hdev)) {
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_LE,
				      MGMT_STATUS_BUSY);
		goto unlock;
	}

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_LE, hdev, data, len);
	if (!cmd) {
		err = -ENOMEM;
		goto unlock;
	}

	hci_req_init(&req, hdev);

	memset(&hci_cp, 0, sizeof(hci_cp));

	if (val) {
		hci_cp.le = val;
		hci_cp.simul = 0x00;
	} else {
		if (hci_dev_test_flag(hdev, HCI_LE_ADV))
			__hci_req_disable_advertising(&req);

		if (ext_adv_capable(hdev))
			__hci_req_clear_ext_adv_sets(&req);
	}

	hci_req_add(&req, HCI_OP_WRITE_LE_HOST_SUPPORTED, sizeof(hci_cp),
		    &hci_cp);

	err = hci_req_run(&req, le_enable_complete);
	if (err < 0)
		mgmt_pending_remove(cmd);

unlock:
	hci_dev_unlock(hdev);
	return err;
}