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
struct mgmt_cp_add_uuid {int /*<<< orphan*/  uuid; int /*<<< orphan*/  svc_hint; } ;
struct hci_request {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  dev_class; int /*<<< orphan*/  id; int /*<<< orphan*/  uuids; int /*<<< orphan*/  name; } ;
struct bt_uuid {int /*<<< orphan*/  list; int /*<<< orphan*/  size; int /*<<< orphan*/  svc_hint; int /*<<< orphan*/  uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int ENODATA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MGMT_OP_ADD_UUID ; 
 int /*<<< orphan*/  MGMT_STATUS_BUSY ; 
 int /*<<< orphan*/  __hci_req_update_class (struct hci_request*) ; 
 int /*<<< orphan*/  __hci_req_update_eir (struct hci_request*) ; 
 int /*<<< orphan*/  add_uuid_complete ; 
 int /*<<< orphan*/  get_uuid_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 int hci_req_run (struct hci_request*,int /*<<< orphan*/ ) ; 
 struct bt_uuid* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ pending_eir_or_class (struct hci_dev*) ; 

__attribute__((used)) static int add_uuid(struct sock *sk, struct hci_dev *hdev, void *data, u16 len)
{
	struct mgmt_cp_add_uuid *cp = data;
	struct mgmt_pending_cmd *cmd;
	struct hci_request req;
	struct bt_uuid *uuid;
	int err;

	BT_DBG("request for %s", hdev->name);

	hci_dev_lock(hdev);

	if (pending_eir_or_class(hdev)) {
		err = mgmt_cmd_status(sk, hdev->id, MGMT_OP_ADD_UUID,
				      MGMT_STATUS_BUSY);
		goto failed;
	}

	uuid = kmalloc(sizeof(*uuid), GFP_KERNEL);
	if (!uuid) {
		err = -ENOMEM;
		goto failed;
	}

	memcpy(uuid->uuid, cp->uuid, 16);
	uuid->svc_hint = cp->svc_hint;
	uuid->size = get_uuid_size(cp->uuid);

	list_add_tail(&uuid->list, &hdev->uuids);

	hci_req_init(&req, hdev);

	__hci_req_update_class(&req);
	__hci_req_update_eir(&req);

	err = hci_req_run(&req, add_uuid_complete);
	if (err < 0) {
		if (err != -ENODATA)
			goto failed;

		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_ADD_UUID, 0,
					hdev->dev_class, 3);
		goto failed;
	}

	cmd = mgmt_pending_add(sk, MGMT_OP_ADD_UUID, hdev, data, len);
	if (!cmd) {
		err = -ENOMEM;
		goto failed;
	}

	err = 0;

failed:
	hci_dev_unlock(hdev);
	return err;
}