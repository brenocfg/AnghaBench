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
struct hci_dev {scalar_t__ adv_instance_timeout; int /*<<< orphan*/  adv_instance_expire; int /*<<< orphan*/  le_scan_restart; int /*<<< orphan*/  le_scan_disable; int /*<<< orphan*/  discov_off; int /*<<< orphan*/  discoverable_update; int /*<<< orphan*/  connectable_update; int /*<<< orphan*/  scan_update; int /*<<< orphan*/  bg_scan_update; int /*<<< orphan*/  discov_update; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_req_sync_cancel (struct hci_dev*,int /*<<< orphan*/ ) ; 

void hci_request_cancel_all(struct hci_dev *hdev)
{
	hci_req_sync_cancel(hdev, ENODEV);

	cancel_work_sync(&hdev->discov_update);
	cancel_work_sync(&hdev->bg_scan_update);
	cancel_work_sync(&hdev->scan_update);
	cancel_work_sync(&hdev->connectable_update);
	cancel_work_sync(&hdev->discoverable_update);
	cancel_delayed_work_sync(&hdev->discov_off);
	cancel_delayed_work_sync(&hdev->le_scan_disable);
	cancel_delayed_work_sync(&hdev->le_scan_restart);

	if (hdev->adv_instance_timeout) {
		cancel_delayed_work_sync(&hdev->adv_instance_expire);
		hdev->adv_instance_timeout = 0;
	}
}