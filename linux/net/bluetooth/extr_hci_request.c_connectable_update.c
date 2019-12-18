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
struct hci_request {struct hci_dev* hdev; } ;
struct hci_dev {int /*<<< orphan*/  cur_adv_instance; int /*<<< orphan*/  adv_instances; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_ADVERTISING ; 
 int /*<<< orphan*/  HCI_BREDR_ENABLED ; 
 int /*<<< orphan*/  __hci_req_enable_advertising (struct hci_request*) ; 
 int /*<<< orphan*/  __hci_req_start_ext_adv (struct hci_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __hci_req_update_adv_data (struct hci_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __hci_req_update_scan (struct hci_request*) ; 
 int /*<<< orphan*/  __hci_update_background_scan (struct hci_request*) ; 
 scalar_t__ ext_adv_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int connectable_update(struct hci_request *req, unsigned long opt)
{
	struct hci_dev *hdev = req->hdev;

	hci_dev_lock(hdev);

	__hci_req_update_scan(req);

	/* If BR/EDR is not enabled and we disable advertising as a
	 * by-product of disabling connectable, we need to update the
	 * advertising flags.
	 */
	if (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		__hci_req_update_adv_data(req, hdev->cur_adv_instance);

	/* Update the advertising parameters if necessary */
	if (hci_dev_test_flag(hdev, HCI_ADVERTISING) ||
	    !list_empty(&hdev->adv_instances)) {
		if (ext_adv_capable(hdev))
			__hci_req_start_ext_adv(req, hdev->cur_adv_instance);
		else
			__hci_req_enable_advertising(req);
	}

	__hci_update_background_scan(req);

	hci_dev_unlock(hdev);

	return 0;
}