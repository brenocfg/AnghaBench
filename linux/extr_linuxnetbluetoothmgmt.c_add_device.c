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
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  bdaddr; } ;
struct mgmt_cp_add_device {int action; TYPE_1__ addr; } ;
struct hci_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  whitelist; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDADDR_ANY ; 
 scalar_t__ BDADDR_BREDR ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_AUTO_CONN_ALWAYS ; 
 int /*<<< orphan*/  HCI_AUTO_CONN_DIRECT ; 
 int /*<<< orphan*/  HCI_AUTO_CONN_REPORT ; 
 int /*<<< orphan*/  MGMT_OP_ADD_DEVICE ; 
 int /*<<< orphan*/  MGMT_STATUS_FAILED ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  bacmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdaddr_type_is_valid (scalar_t__) ; 
 int /*<<< orphan*/  device_added (struct sock*,struct hci_dev*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int hci_bdaddr_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ hci_conn_params_set (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_is_identity_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_update_scan (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_update_background_scan (struct hci_dev*) ; 
 int /*<<< orphan*/  le_addr_type (scalar_t__) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static int add_device(struct sock *sk, struct hci_dev *hdev,
		      void *data, u16 len)
{
	struct mgmt_cp_add_device *cp = data;
	u8 auto_conn, addr_type;
	int err;

	BT_DBG("%s", hdev->name);

	if (!bdaddr_type_is_valid(cp->addr.type) ||
	    !bacmp(&cp->addr.bdaddr, BDADDR_ANY))
		return mgmt_cmd_complete(sk, hdev->id, MGMT_OP_ADD_DEVICE,
					 MGMT_STATUS_INVALID_PARAMS,
					 &cp->addr, sizeof(cp->addr));

	if (cp->action != 0x00 && cp->action != 0x01 && cp->action != 0x02)
		return mgmt_cmd_complete(sk, hdev->id, MGMT_OP_ADD_DEVICE,
					 MGMT_STATUS_INVALID_PARAMS,
					 &cp->addr, sizeof(cp->addr));

	hci_dev_lock(hdev);

	if (cp->addr.type == BDADDR_BREDR) {
		/* Only incoming connections action is supported for now */
		if (cp->action != 0x01) {
			err = mgmt_cmd_complete(sk, hdev->id,
						MGMT_OP_ADD_DEVICE,
						MGMT_STATUS_INVALID_PARAMS,
						&cp->addr, sizeof(cp->addr));
			goto unlock;
		}

		err = hci_bdaddr_list_add(&hdev->whitelist, &cp->addr.bdaddr,
					  cp->addr.type);
		if (err)
			goto unlock;

		hci_req_update_scan(hdev);

		goto added;
	}

	addr_type = le_addr_type(cp->addr.type);

	if (cp->action == 0x02)
		auto_conn = HCI_AUTO_CONN_ALWAYS;
	else if (cp->action == 0x01)
		auto_conn = HCI_AUTO_CONN_DIRECT;
	else
		auto_conn = HCI_AUTO_CONN_REPORT;

	/* Kernel internally uses conn_params with resolvable private
	 * address, but Add Device allows only identity addresses.
	 * Make sure it is enforced before calling
	 * hci_conn_params_lookup.
	 */
	if (!hci_is_identity_address(&cp->addr.bdaddr, addr_type)) {
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_ADD_DEVICE,
					MGMT_STATUS_INVALID_PARAMS,
					&cp->addr, sizeof(cp->addr));
		goto unlock;
	}

	/* If the connection parameters don't exist for this device,
	 * they will be created and configured with defaults.
	 */
	if (hci_conn_params_set(hdev, &cp->addr.bdaddr, addr_type,
				auto_conn) < 0) {
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_ADD_DEVICE,
					MGMT_STATUS_FAILED, &cp->addr,
					sizeof(cp->addr));
		goto unlock;
	}

	hci_update_background_scan(hdev);

added:
	device_added(sk, hdev, &cp->addr.bdaddr, cp->addr.type, cp->action);

	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_ADD_DEVICE,
				MGMT_STATUS_SUCCESS, &cp->addr,
				sizeof(cp->addr));

unlock:
	hci_dev_unlock(hdev);
	return err;
}