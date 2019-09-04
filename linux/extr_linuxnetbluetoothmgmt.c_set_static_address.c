#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct TYPE_3__ {int* b; } ;
struct mgmt_cp_set_static_address {TYPE_1__ bdaddr; } ;
struct hci_dev {int /*<<< orphan*/  static_addr; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDADDR_ANY ; 
 int /*<<< orphan*/  BDADDR_NONE ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGMT_OP_SET_STATIC_ADDRESS ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  MGMT_STATUS_REJECTED ; 
 scalar_t__ bacmp (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 scalar_t__ hdev_is_powered (struct hci_dev*) ; 
 int /*<<< orphan*/  lmp_le_capable (struct hci_dev*) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int new_settings (struct hci_dev*,struct sock*) ; 
 int send_settings_rsp (struct sock*,int /*<<< orphan*/ ,struct hci_dev*) ; 

__attribute__((used)) static int set_static_address(struct sock *sk, struct hci_dev *hdev,
			      void *data, u16 len)
{
	struct mgmt_cp_set_static_address *cp = data;
	int err;

	BT_DBG("%s", hdev->name);

	if (!lmp_le_capable(hdev))
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_STATIC_ADDRESS,
				       MGMT_STATUS_NOT_SUPPORTED);

	if (hdev_is_powered(hdev))
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_STATIC_ADDRESS,
				       MGMT_STATUS_REJECTED);

	if (bacmp(&cp->bdaddr, BDADDR_ANY)) {
		if (!bacmp(&cp->bdaddr, BDADDR_NONE))
			return mgmt_cmd_status(sk, hdev->id,
					       MGMT_OP_SET_STATIC_ADDRESS,
					       MGMT_STATUS_INVALID_PARAMS);

		/* Two most significant bits shall be set */
		if ((cp->bdaddr.b[5] & 0xc0) != 0xc0)
			return mgmt_cmd_status(sk, hdev->id,
					       MGMT_OP_SET_STATIC_ADDRESS,
					       MGMT_STATUS_INVALID_PARAMS);
	}

	hci_dev_lock(hdev);

	bacpy(&hdev->static_addr, &cp->bdaddr);

	err = send_settings_rsp(sk, MGMT_OP_SET_STATIC_ADDRESS, hdev);
	if (err < 0)
		goto unlock;

	err = new_settings(hdev, sk);

unlock:
	hci_dev_unlock(hdev);
	return err;
}