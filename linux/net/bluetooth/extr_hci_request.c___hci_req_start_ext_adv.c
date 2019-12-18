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
typedef  int /*<<< orphan*/  u8 ;
struct hci_request {struct hci_dev* hdev; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_LE_ADV ; 
 int /*<<< orphan*/  __hci_req_disable_advertising (struct hci_request*) ; 
 int /*<<< orphan*/  __hci_req_enable_ext_advertising (struct hci_request*,int /*<<< orphan*/ ) ; 
 int __hci_req_setup_ext_adv_instance (struct hci_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __hci_req_update_scan_rsp_data (struct hci_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 

int __hci_req_start_ext_adv(struct hci_request *req, u8 instance)
{
	struct hci_dev *hdev = req->hdev;
	int err;

	if (hci_dev_test_flag(hdev, HCI_LE_ADV))
		__hci_req_disable_advertising(req);

	err = __hci_req_setup_ext_adv_instance(req, instance);
	if (err < 0)
		return err;

	__hci_req_update_scan_rsp_data(req, instance);
	__hci_req_enable_ext_advertising(req, instance);

	return 0;
}