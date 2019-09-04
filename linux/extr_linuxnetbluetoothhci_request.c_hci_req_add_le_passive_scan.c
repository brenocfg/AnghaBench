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
struct hci_dev {int* le_features; int /*<<< orphan*/  le_scan_window; int /*<<< orphan*/  le_scan_interval; } ;

/* Variables and functions */
 int HCI_LE_EXT_SCAN_POLICY ; 
 int /*<<< orphan*/  HCI_PRIVACY ; 
 int /*<<< orphan*/  LE_SCAN_PASSIVE ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_start_scan (struct hci_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ hci_update_random_address (struct hci_request*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  scan_use_rpa (struct hci_dev*) ; 
 int update_white_list (struct hci_request*) ; 

void hci_req_add_le_passive_scan(struct hci_request *req)
{
	struct hci_dev *hdev = req->hdev;
	u8 own_addr_type;
	u8 filter_policy;

	/* Set require_privacy to false since no SCAN_REQ are send
	 * during passive scanning. Not using an non-resolvable address
	 * here is important so that peer devices using direct
	 * advertising with our address will be correctly reported
	 * by the controller.
	 */
	if (hci_update_random_address(req, false, scan_use_rpa(hdev),
				      &own_addr_type))
		return;

	/* Adding or removing entries from the white list must
	 * happen before enabling scanning. The controller does
	 * not allow white list modification while scanning.
	 */
	filter_policy = update_white_list(req);

	/* When the controller is using random resolvable addresses and
	 * with that having LE privacy enabled, then controllers with
	 * Extended Scanner Filter Policies support can now enable support
	 * for handling directed advertising.
	 *
	 * So instead of using filter polices 0x00 (no whitelist)
	 * and 0x01 (whitelist enabled) use the new filter policies
	 * 0x02 (no whitelist) and 0x03 (whitelist enabled).
	 */
	if (hci_dev_test_flag(hdev, HCI_PRIVACY) &&
	    (hdev->le_features[0] & HCI_LE_EXT_SCAN_POLICY))
		filter_policy |= 0x02;

	hci_req_start_scan(req, LE_SCAN_PASSIVE, hdev->le_scan_interval,
			   hdev->le_scan_window, own_addr_type, filter_policy);
}