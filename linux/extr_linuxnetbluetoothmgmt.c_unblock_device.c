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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  bdaddr; } ;
struct mgmt_cp_unblock_device {TYPE_1__ addr; } ;
struct hci_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  blacklist; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGMT_EV_DEVICE_UNBLOCKED ; 
 int /*<<< orphan*/  MGMT_OP_UNBLOCK_DEVICE ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  MGMT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  bdaddr_type_is_valid (int /*<<< orphan*/ ) ; 
 int hci_bdaddr_list_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mgmt_event (int /*<<< orphan*/ ,struct hci_dev*,TYPE_1__*,int,struct sock*) ; 

__attribute__((used)) static int unblock_device(struct sock *sk, struct hci_dev *hdev, void *data,
			  u16 len)
{
	struct mgmt_cp_unblock_device *cp = data;
	u8 status;
	int err;

	BT_DBG("%s", hdev->name);

	if (!bdaddr_type_is_valid(cp->addr.type))
		return mgmt_cmd_complete(sk, hdev->id, MGMT_OP_UNBLOCK_DEVICE,
					 MGMT_STATUS_INVALID_PARAMS,
					 &cp->addr, sizeof(cp->addr));

	hci_dev_lock(hdev);

	err = hci_bdaddr_list_del(&hdev->blacklist, &cp->addr.bdaddr,
				  cp->addr.type);
	if (err < 0) {
		status = MGMT_STATUS_INVALID_PARAMS;
		goto done;
	}

	mgmt_event(MGMT_EV_DEVICE_UNBLOCKED, hdev, &cp->addr, sizeof(cp->addr),
		   sk);
	status = MGMT_STATUS_SUCCESS;

done:
	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_UNBLOCK_DEVICE, status,
				&cp->addr, sizeof(cp->addr));

	hci_dev_unlock(hdev);

	return err;
}