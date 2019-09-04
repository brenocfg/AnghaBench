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
typedef  int u8 ;
struct hci_request {struct hci_dev* hdev; } ;
struct hci_dev {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_BREDR_ENABLED ; 
 int /*<<< orphan*/  HCI_CONNECTABLE ; 
 int /*<<< orphan*/  HCI_DISCOVERABLE ; 
 int /*<<< orphan*/  HCI_ISCAN ; 
 int /*<<< orphan*/  HCI_OP_WRITE_SCAN_ENABLE ; 
 int /*<<< orphan*/  HCI_PSCAN ; 
 int SCAN_DISABLED ; 
 int SCAN_INQUIRY ; 
 int SCAN_PAGE ; 
 scalar_t__ disconnected_whitelist_entries (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  hdev_is_powered (struct hci_dev*) ; 
 scalar_t__ mgmt_powering_down (struct hci_dev*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __hci_req_update_scan(struct hci_request *req)
{
	struct hci_dev *hdev = req->hdev;
	u8 scan;

	if (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		return;

	if (!hdev_is_powered(hdev))
		return;

	if (mgmt_powering_down(hdev))
		return;

	if (hci_dev_test_flag(hdev, HCI_CONNECTABLE) ||
	    disconnected_whitelist_entries(hdev))
		scan = SCAN_PAGE;
	else
		scan = SCAN_DISABLED;

	if (hci_dev_test_flag(hdev, HCI_DISCOVERABLE))
		scan |= SCAN_INQUIRY;

	if (test_bit(HCI_PSCAN, &hdev->flags) == !!(scan & SCAN_PAGE) &&
	    test_bit(HCI_ISCAN, &hdev->flags) == !!(scan & SCAN_INQUIRY))
		return;

	hci_req_add(req, HCI_OP_WRITE_SCAN_ENABLE, 1, &scan);
}