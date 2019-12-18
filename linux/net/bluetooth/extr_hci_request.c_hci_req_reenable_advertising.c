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
struct hci_request {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  cur_adv_instance; int /*<<< orphan*/  adv_instances; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_ADVERTISING ; 
 int /*<<< orphan*/  __hci_req_enable_advertising (struct hci_request*) ; 
 int /*<<< orphan*/  __hci_req_schedule_adv_instance (struct hci_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __hci_req_start_ext_adv (struct hci_request*,int) ; 
 int /*<<< orphan*/  __hci_req_update_adv_data (struct hci_request*,int) ; 
 int /*<<< orphan*/  __hci_req_update_scan_rsp_data (struct hci_request*,int) ; 
 int /*<<< orphan*/  adv_enable_complete ; 
 scalar_t__ ext_adv_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_run (struct hci_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

void hci_req_reenable_advertising(struct hci_dev *hdev)
{
	struct hci_request req;

	if (!hci_dev_test_flag(hdev, HCI_ADVERTISING) &&
	    list_empty(&hdev->adv_instances))
		return;

	hci_req_init(&req, hdev);

	if (hdev->cur_adv_instance) {
		__hci_req_schedule_adv_instance(&req, hdev->cur_adv_instance,
						true);
	} else {
		if (ext_adv_capable(hdev)) {
			__hci_req_start_ext_adv(&req, 0x00);
		} else {
			__hci_req_update_adv_data(&req, 0x00);
			__hci_req_update_scan_rsp_data(&req, 0x00);
			__hci_req_enable_advertising(&req);
		}
	}

	hci_req_run(&req, adv_enable_complete);
}