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
struct mgmt_cp_set_local_name {int /*<<< orphan*/  name; int /*<<< orphan*/  short_name; } ;
struct hci_request {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  cur_adv_instance; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  id; int /*<<< orphan*/  short_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCI_ADVERTISING ; 
 int /*<<< orphan*/  HCI_MGMT_LOCAL_NAME_EVENTS ; 
 int /*<<< orphan*/  MGMT_EV_LOCAL_NAME_CHANGED ; 
 int /*<<< orphan*/  MGMT_OP_SET_LOCAL_NAME ; 
 int /*<<< orphan*/  __hci_req_update_eir (struct hci_request*) ; 
 int /*<<< orphan*/  __hci_req_update_name (struct hci_request*) ; 
 int /*<<< orphan*/  __hci_req_update_scan_rsp_data (struct hci_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext_info_changed (struct hci_dev*,struct sock*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 int hci_req_run (struct hci_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdev_is_powered (struct hci_dev*) ; 
 scalar_t__ lmp_bredr_capable (struct hci_dev*) ; 
 scalar_t__ lmp_le_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int mgmt_limited_event (int /*<<< orphan*/ ,struct hci_dev*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sock*) ; 
 struct mgmt_pending_cmd* mgmt_pending_add (struct sock*,int /*<<< orphan*/ ,struct hci_dev*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_pending_remove (struct mgmt_pending_cmd*) ; 
 int /*<<< orphan*/  set_name_complete ; 

__attribute__((used)) static int set_local_name(struct sock *sk, struct hci_dev *hdev, void *data,
			  u16 len)
{
	struct mgmt_cp_set_local_name *cp = data;
	struct mgmt_pending_cmd *cmd;
	struct hci_request req;
	int err;

	BT_DBG("");

	hci_dev_lock(hdev);

	/* If the old values are the same as the new ones just return a
	 * direct command complete event.
	 */
	if (!memcmp(hdev->dev_name, cp->name, sizeof(hdev->dev_name)) &&
	    !memcmp(hdev->short_name, cp->short_name,
		    sizeof(hdev->short_name))) {
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_SET_LOCAL_NAME, 0,
					data, len);
		goto failed;
	}

	memcpy(hdev->short_name, cp->short_name, sizeof(hdev->short_name));

	if (!hdev_is_powered(hdev)) {
		memcpy(hdev->dev_name, cp->name, sizeof(hdev->dev_name));

		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_SET_LOCAL_NAME, 0,
					data, len);
		if (err < 0)
			goto failed;

		err = mgmt_limited_event(MGMT_EV_LOCAL_NAME_CHANGED, hdev, data,
					 len, HCI_MGMT_LOCAL_NAME_EVENTS, sk);
		ext_info_changed(hdev, sk);

		goto failed;
	}

	cmd = mgmt_pending_add(sk, MGMT_OP_SET_LOCAL_NAME, hdev, data, len);
	if (!cmd) {
		err = -ENOMEM;
		goto failed;
	}

	memcpy(hdev->dev_name, cp->name, sizeof(hdev->dev_name));

	hci_req_init(&req, hdev);

	if (lmp_bredr_capable(hdev)) {
		__hci_req_update_name(&req);
		__hci_req_update_eir(&req);
	}

	/* The name is stored in the scan response data and so
	 * no need to udpate the advertising data here.
	 */
	if (lmp_le_capable(hdev) && hci_dev_test_flag(hdev, HCI_ADVERTISING))
		__hci_req_update_scan_rsp_data(&req, hdev->cur_adv_instance);

	err = hci_req_run(&req, set_name_complete);
	if (err < 0)
		mgmt_pending_remove(cmd);

failed:
	hci_dev_unlock(hdev);
	return err;
}