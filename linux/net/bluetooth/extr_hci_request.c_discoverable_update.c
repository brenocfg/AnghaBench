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
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_ADVERTISING ; 
 int /*<<< orphan*/  HCI_BREDR_ENABLED ; 
 int /*<<< orphan*/  HCI_LIMITED_PRIVACY ; 
 int /*<<< orphan*/  __hci_req_enable_advertising (struct hci_request*) ; 
 int /*<<< orphan*/  __hci_req_start_ext_adv (struct hci_request*,int) ; 
 int /*<<< orphan*/  __hci_req_update_adv_data (struct hci_request*,int) ; 
 int /*<<< orphan*/  __hci_req_update_class (struct hci_request*) ; 
 int /*<<< orphan*/  __hci_req_update_scan (struct hci_request*) ; 
 scalar_t__ ext_adv_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  write_iac (struct hci_request*) ; 

__attribute__((used)) static int discoverable_update(struct hci_request *req, unsigned long opt)
{
	struct hci_dev *hdev = req->hdev;

	hci_dev_lock(hdev);

	if (hci_dev_test_flag(hdev, HCI_BREDR_ENABLED)) {
		write_iac(req);
		__hci_req_update_scan(req);
		__hci_req_update_class(req);
	}

	/* Advertising instances don't use the global discoverable setting, so
	 * only update AD if advertising was enabled using Set Advertising.
	 */
	if (hci_dev_test_flag(hdev, HCI_ADVERTISING)) {
		__hci_req_update_adv_data(req, 0x00);

		/* Discoverable mode affects the local advertising
		 * address in limited privacy mode.
		 */
		if (hci_dev_test_flag(hdev, HCI_LIMITED_PRIVACY)) {
			if (ext_adv_capable(hdev))
				__hci_req_start_ext_adv(req, 0x00);
			else
				__hci_req_enable_advertising(req);
		}
	}

	hci_dev_unlock(hdev);

	return 0;
}