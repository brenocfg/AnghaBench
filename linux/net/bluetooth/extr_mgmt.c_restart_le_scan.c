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
struct TYPE_2__ {scalar_t__ scan_duration; scalar_t__ scan_start; } ;
struct hci_dev {int /*<<< orphan*/  le_scan_restart; int /*<<< orphan*/  req_workqueue; TYPE_1__ discovery; } ;

/* Variables and functions */
 scalar_t__ DISCOV_LE_RESTART_DELAY ; 
 int /*<<< orphan*/  HCI_LE_SCAN ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void restart_le_scan(struct hci_dev *hdev)
{
	/* If controller is not scanning we are done. */
	if (!hci_dev_test_flag(hdev, HCI_LE_SCAN))
		return;

	if (time_after(jiffies + DISCOV_LE_RESTART_DELAY,
		       hdev->discovery.scan_start +
		       hdev->discovery.scan_duration))
		return;

	queue_delayed_work(hdev->req_workqueue, &hdev->le_scan_restart,
			   DISCOV_LE_RESTART_DELAY);
}