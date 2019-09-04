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
typedef  int /*<<< orphan*/  val ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct mgmt_pending_cmd {int dummy; } ;
struct mgmt_mode {int val; } ;
struct hci_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_AUTH ; 
 int /*<<< orphan*/  HCI_LINK_SECURITY ; 
 int /*<<< orphan*/  HCI_OP_WRITE_AUTH_ENABLE ; 
 int /*<<< orphan*/  MGMT_OP_SET_LINK_SECURITY ; 
 int MGMT_STATUS_BUSY ; 
 int MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  hci_dev_change_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  hdev_is_powered (struct hci_dev*) ; 
 int mgmt_bredr_support (struct hci_dev*) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int new_settings (struct hci_dev*,struct sock*) ; 
 scalar_t__ pending_find (int /*<<< orphan*/ ,struct hci_dev*) ; 
 int send_settings_rsp (struct sock*,int /*<<< orphan*/ ,struct hci_dev*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_link_security(struct sock *sk, struct hci_dev *hdev, void *data,
			     u16 len)
{
	struct mgmt_mode *cp = data;
	struct mgmt_pending_cmd *cmd;
	u8 val, status;
	int err;

	BT_DBG("request for %s", hdev->name);

	status = mgmt_bredr_support(hdev);
	if (status)
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_LINK_SECURITY,
				       status);

	if (cp->val != 0x00 && cp->val != 0x01)
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_LINK_SECURITY,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	if (!hdev_is_powered(hdev)) {
		bool changed = false;

		if (!!cp->val != hci_dev_test_flag(hdev, HCI_LINK_SECURITY)) {
			hci_dev_change_flag(hdev, HCI_LINK_SECURITY);
			changed = true;
		}

		err = send_settings_rsp(sk, MGMT_OP_SET_LINK_SECURITY, hdev);
		if (err < 0)
			goto failed;

		if (changed)
			err = new_settings(hdev, sk);

		goto failed;
	}

	if (pending_find(MGMT_OP_SET_LINK_SECURITY, hdev)) {
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_LINK_SECURITY,
				      MGMT_STATUS_BUSY);
		goto failed;
	}

	val = !!cp->val;

	if (test_bit(HCI_AUTH, &hdev->flags) == val) {
		err = send_settings_rsp(sk, MGMT_OP_SET_LINK_SECURITY, hdev);
		goto failed;
	}

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_LINK_SECURITY, hdev, data, len);
	if (!cmd) {
		err = -ENOMEM;
		goto failed;
	}

	err = hci_send_cmd(hdev, HCI_OP_WRITE_AUTH_ENABLE, sizeof(val), &val);
	if (err < 0) {
		mgmt_pending_remove(cmd);
		goto failed;
	}

failed:
	hci_dev_unlock(hdev);
	return err;
}