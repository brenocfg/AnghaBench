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
struct discovery_state {int /*<<< orphan*/  state; int /*<<< orphan*/  last_adv_data_len; int /*<<< orphan*/  last_adv_data; int /*<<< orphan*/  last_adv_flags; int /*<<< orphan*/  last_adv_rssi; int /*<<< orphan*/  last_adv_addr_type; int /*<<< orphan*/  last_adv_addr; } ;
struct hci_dev {struct discovery_state discovery; int /*<<< orphan*/  le_scan_disable; int /*<<< orphan*/  le_scan_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCOVERY_FINDING ; 
 int /*<<< orphan*/  DISCOVERY_STOPPED ; 
 int /*<<< orphan*/  HCI_LE_ADV ; 
 int /*<<< orphan*/  HCI_LE_SCAN ; 
 int /*<<< orphan*/  HCI_LE_SCAN_INTERRUPTED ; 
 int /*<<< orphan*/  LE_LINK ; 
 int /*<<< orphan*/  LE_SCAN_ACTIVE ; 
#define  LE_SCAN_DISABLE 129 
#define  LE_SCAN_ENABLE 128 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,int) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_pending_adv_report (struct hci_dev*) ; 
 int /*<<< orphan*/  has_pending_adv_report (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_set_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_test_and_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_discovery_set_state (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_reenable_advertising (struct hci_dev*) ; 
 int /*<<< orphan*/  mgmt_device_found (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void le_set_scan_enable_complete(struct hci_dev *hdev, u8 enable)
{
	hci_dev_lock(hdev);

	switch (enable) {
	case LE_SCAN_ENABLE:
		hci_dev_set_flag(hdev, HCI_LE_SCAN);
		if (hdev->le_scan_type == LE_SCAN_ACTIVE)
			clear_pending_adv_report(hdev);
		break;

	case LE_SCAN_DISABLE:
		/* We do this here instead of when setting DISCOVERY_STOPPED
		 * since the latter would potentially require waiting for
		 * inquiry to stop too.
		 */
		if (has_pending_adv_report(hdev)) {
			struct discovery_state *d = &hdev->discovery;

			mgmt_device_found(hdev, &d->last_adv_addr, LE_LINK,
					  d->last_adv_addr_type, NULL,
					  d->last_adv_rssi, d->last_adv_flags,
					  d->last_adv_data,
					  d->last_adv_data_len, NULL, 0);
		}

		/* Cancel this timer so that we don't try to disable scanning
		 * when it's already disabled.
		 */
		cancel_delayed_work(&hdev->le_scan_disable);

		hci_dev_clear_flag(hdev, HCI_LE_SCAN);

		/* The HCI_LE_SCAN_INTERRUPTED flag indicates that we
		 * interrupted scanning due to a connect request. Mark
		 * therefore discovery as stopped. If this was not
		 * because of a connect request advertising might have
		 * been disabled because of active scanning, so
		 * re-enable it again if necessary.
		 */
		if (hci_dev_test_and_clear_flag(hdev, HCI_LE_SCAN_INTERRUPTED))
			hci_discovery_set_state(hdev, DISCOVERY_STOPPED);
		else if (!hci_dev_test_flag(hdev, HCI_LE_ADV) &&
			 hdev->discovery.state == DISCOVERY_FINDING)
			hci_req_reenable_advertising(hdev);

		break;

	default:
		bt_dev_err(hdev, "use of reserved LE_Scan_Enable param %d",
			   enable);
		break;
	}

	hci_dev_unlock(hdev);
}