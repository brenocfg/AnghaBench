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

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_BREDR_ENABLED ; 
 int /*<<< orphan*/  HCI_LE_ENABLED ; 
 int /*<<< orphan*/  HCI_OP_WRITE_SC_SUPPORT ; 
 int /*<<< orphan*/  HCI_SC_ENABLED ; 
 int /*<<< orphan*/  HCI_SC_ONLY ; 
 int /*<<< orphan*/  HCI_SSP_ENABLED ; 
 int /*<<< orphan*/  MGMT_OP_SET_SECURE_CONN ; 
 int /*<<< orphan*/  MGMT_STATUS_BUSY ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  MGMT_STATUS_REJECTED ; 
 int /*<<< orphan*/  hci_dev_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int hci_dev_test_and_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_test_and_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 int hci_req_run (struct hci_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdev_is_powered (struct hci_dev*) ; 
 scalar_t__ lmp_sc_capable (struct hci_dev*) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int new_settings (struct hci_dev*,struct sock*) ; 
 scalar_t__ pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 
 int /*<<< orphan*/  sc_enable_complete ; 
 int send_settings_rsp (struct sock*,int /*<<< orphan*/ ,struct hci_dev*) ; 

__attribute__((used)) static int set_secure_conn(struct sock *sk, struct hci_dev *hdev,
			   void *data, u16 len)
{
	struct mgmt_mode *cp = data;
	struct mgmt_pending_cmd *cmd;
	struct hci_request req;
	u8 val;
	int err;

	BT_DBG("request for %s", hdev->name);

	if (!lmp_sc_capable(hdev) &&
	    !hci_dev_test_flag(hdev, HCI_LE_ENABLED))
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SECURE_CONN,
				       MGMT_STATUS_NOT_SUPPORTED);

	if (hci_dev_test_flag(hdev, HCI_BREDR_ENABLED) &&
	    lmp_sc_capable(hdev) &&
	    !hci_dev_test_flag(hdev, HCI_SSP_ENABLED))
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SECURE_CONN,
				       MGMT_STATUS_REJECTED);

	if (cp->val != 0x00 && cp->val != 0x01 && cp->val != 0x02)
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SECURE_CONN,
				  MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	if (!hdev_is_powered(hdev) || !lmp_sc_capable(hdev) ||
	    !hci_dev_test_flag(hdev, HCI_BREDR_ENABLED)) {
		bool changed;

		if (cp->val) {
			changed = !hci_dev_test_and_set_flag(hdev,
							     HCI_SC_ENABLED);
			if (cp->val == 0x02)
				hci_dev_set_flag(hdev, HCI_SC_ONLY);
			else
				hci_dev_clear_flag(hdev, HCI_SC_ONLY);
		} else {
			changed = hci_dev_test_and_clear_flag(hdev,
							      HCI_SC_ENABLED);
			hci_dev_clear_flag(hdev, HCI_SC_ONLY);
		}

		err = send_settings_rsp(sk, MGMT_OP_SET_SECURE_CONN, hdev);
		if (err < 0)
			goto failed;

		if (changed)
			err = new_settings(hdev, sk);

		goto failed;
	}

	if (pending_find(MGMT_OP_SET_SECURE_CONN, hdev)) {
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_SECURE_CONN,
				      MGMT_STATUS_BUSY);
		goto failed;
	}

	val = !!cp->val;

	if (val == hci_dev_test_flag(hdev, HCI_SC_ENABLED) &&
	    (cp->val == 0x02) == hci_dev_test_flag(hdev, HCI_SC_ONLY)) {
		err = send_settings_rsp(sk, MGMT_OP_SET_SECURE_CONN, hdev);
		goto failed;
	}

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_SECURE_CONN, hdev, data, len);
	if (!cmd) {
		err = -ENOMEM;
		goto failed;
	}

	hci_req_init(&req, hdev);
	hci_req_add(&req, HCI_OP_WRITE_SC_SUPPORT, 1, &val);
	err = hci_req_run(&req, sc_enable_complete);
	if (err < 0) {
		mgmt_pending_remove(cmd);
		goto failed;
	}

failed:
	hci_dev_unlock(hdev);
	return err;
}