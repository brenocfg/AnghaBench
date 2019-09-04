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
struct mgmt_cp_set_device_id {int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  source; } ;
struct hci_request {int dummy; } ;
struct hci_dev {int devid_source; int /*<<< orphan*/  id; void* devid_version; void* devid_product; void* devid_vendor; int /*<<< orphan*/  name; } ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGMT_OP_SET_DEVICE_ID ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  __hci_req_update_eir (struct hci_request*) ; 
 void* __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_run (struct hci_request*,int /*<<< orphan*/ *) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mgmt_cmd_status (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_device_id(struct sock *sk, struct hci_dev *hdev, void *data,
			 u16 len)
{
	struct mgmt_cp_set_device_id *cp = data;
	struct hci_request req;
	int err;
	__u16 source;

	BT_DBG("%s", hdev->name);

	source = __le16_to_cpu(cp->source);

	if (source > 0x0002)
		return mgmt_cmd_status(sk, hdev->id, MGMT_OP_SET_DEVICE_ID,
				       MGMT_STATUS_INVALID_PARAMS);

	hci_dev_lock(hdev);

	hdev->devid_source = source;
	hdev->devid_vendor = __le16_to_cpu(cp->vendor);
	hdev->devid_product = __le16_to_cpu(cp->product);
	hdev->devid_version = __le16_to_cpu(cp->version);

	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_SET_DEVICE_ID, 0,
				NULL, 0);

	hci_req_init(&req, hdev);
	__hci_req_update_eir(&req);
	hci_req_run(&req, NULL);

	hci_dev_unlock(hdev);

	return err;
}