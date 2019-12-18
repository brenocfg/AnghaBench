#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hci_request {struct hci_dev* hdev; } ;
struct TYPE_2__ {scalar_t__ state; } ;
struct hci_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  pend_le_reports; int /*<<< orphan*/  pend_le_conns; TYPE_1__ discovery; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ DISCOVERY_STOPPED ; 
 int /*<<< orphan*/  HCI_AUTO_OFF ; 
 int /*<<< orphan*/  HCI_CONFIG ; 
 int /*<<< orphan*/  HCI_INIT ; 
 int /*<<< orphan*/  HCI_LE_ENABLED ; 
 int /*<<< orphan*/  HCI_LE_SCAN ; 
 int /*<<< orphan*/  HCI_SETUP ; 
 int /*<<< orphan*/  HCI_UNREGISTER ; 
 int /*<<< orphan*/  HCI_UP ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_discovery_filter_clear (struct hci_dev*) ; 
 scalar_t__ hci_lookup_le_connect (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_add_le_passive_scan (struct hci_request*) ; 
 int /*<<< orphan*/  hci_req_add_le_scan_disable (struct hci_request*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __hci_update_background_scan(struct hci_request *req)
{
	struct hci_dev *hdev = req->hdev;

	if (!test_bit(HCI_UP, &hdev->flags) ||
	    test_bit(HCI_INIT, &hdev->flags) ||
	    hci_dev_test_flag(hdev, HCI_SETUP) ||
	    hci_dev_test_flag(hdev, HCI_CONFIG) ||
	    hci_dev_test_flag(hdev, HCI_AUTO_OFF) ||
	    hci_dev_test_flag(hdev, HCI_UNREGISTER))
		return;

	/* No point in doing scanning if LE support hasn't been enabled */
	if (!hci_dev_test_flag(hdev, HCI_LE_ENABLED))
		return;

	/* If discovery is active don't interfere with it */
	if (hdev->discovery.state != DISCOVERY_STOPPED)
		return;

	/* Reset RSSI and UUID filters when starting background scanning
	 * since these filters are meant for service discovery only.
	 *
	 * The Start Discovery and Start Service Discovery operations
	 * ensure to set proper values for RSSI threshold and UUID
	 * filter list. So it is safe to just reset them here.
	 */
	hci_discovery_filter_clear(hdev);

	if (list_empty(&hdev->pend_le_conns) &&
	    list_empty(&hdev->pend_le_reports)) {
		/* If there is no pending LE connections or devices
		 * to be scanned for, we should stop the background
		 * scanning.
		 */

		/* If controller is not scanning we are done. */
		if (!hci_dev_test_flag(hdev, HCI_LE_SCAN))
			return;

		hci_req_add_le_scan_disable(req);

		BT_DBG("%s stopping background scanning", hdev->name);
	} else {
		/* If there is at least one pending LE connection, we should
		 * keep the background scan running.
		 */

		/* If controller is connecting, we should not start scanning
		 * since some controllers are not able to scan and connect at
		 * the same time.
		 */
		if (hci_lookup_le_connect(hdev))
			return;

		/* If controller is currently scanning, we stop it to ensure we
		 * don't miss any advertising (due to duplicates filter).
		 */
		if (hci_dev_test_flag(hdev, HCI_LE_SCAN))
			hci_req_add_le_scan_disable(req);

		hci_req_add_le_passive_scan(req);

		BT_DBG("%s starting background scanning", hdev->name);
	}
}