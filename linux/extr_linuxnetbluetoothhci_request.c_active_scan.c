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
typedef  unsigned long uint16_t ;
typedef  int /*<<< orphan*/  u8 ;
struct hci_request {struct hci_dev* hdev; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_LE_DEV_PUBLIC ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DISCOV_LE_SCAN_WIN ; 
 int EBUSY ; 
 int /*<<< orphan*/  HCI_LE_ADV ; 
 int /*<<< orphan*/  HCI_LE_SCAN ; 
 int /*<<< orphan*/  LE_SCAN_ACTIVE ; 
 int /*<<< orphan*/  __hci_req_disable_advertising (struct hci_request*) ; 
 int /*<<< orphan*/  cancel_adv_timeout (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 scalar_t__ hci_lookup_le_connect (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_add_le_scan_disable (struct hci_request*) ; 
 int /*<<< orphan*/  hci_req_start_scan (struct hci_request*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hci_update_random_address (struct hci_request*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_use_rpa (struct hci_dev*) ; 

__attribute__((used)) static int active_scan(struct hci_request *req, unsigned long opt)
{
	uint16_t interval = opt;
	struct hci_dev *hdev = req->hdev;
	u8 own_addr_type;
	int err;

	BT_DBG("%s", hdev->name);

	if (hci_dev_test_flag(hdev, HCI_LE_ADV)) {
		hci_dev_lock(hdev);

		/* Don't let discovery abort an outgoing connection attempt
		 * that's using directed advertising.
		 */
		if (hci_lookup_le_connect(hdev)) {
			hci_dev_unlock(hdev);
			return -EBUSY;
		}

		cancel_adv_timeout(hdev);
		hci_dev_unlock(hdev);

		__hci_req_disable_advertising(req);
	}

	/* If controller is scanning, it means the background scanning is
	 * running. Thus, we should temporarily stop it in order to set the
	 * discovery scanning parameters.
	 */
	if (hci_dev_test_flag(hdev, HCI_LE_SCAN))
		hci_req_add_le_scan_disable(req);

	/* All active scans will be done with either a resolvable private
	 * address (when privacy feature has been enabled) or non-resolvable
	 * private address.
	 */
	err = hci_update_random_address(req, true, scan_use_rpa(hdev),
					&own_addr_type);
	if (err < 0)
		own_addr_type = ADDR_LE_DEV_PUBLIC;

	hci_req_start_scan(req, LE_SCAN_ACTIVE, interval, DISCOV_LE_SCAN_WIN,
			   own_addr_type, 0);
	return 0;
}