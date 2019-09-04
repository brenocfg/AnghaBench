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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int type; unsigned long scan_duration; int /*<<< orphan*/  scan_start; scalar_t__ result_filtering; } ;
struct hci_dev {int /*<<< orphan*/  le_scan_disable; int /*<<< orphan*/  req_workqueue; TYPE_1__ discovery; int /*<<< orphan*/  quirks; int /*<<< orphan*/  name; int /*<<< orphan*/  discov_interleaved_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int) ; 
 int DISCOV_BREDR_INQUIRY_LEN ; 
 int DISCOV_LE_SCAN_INT ; 
 int /*<<< orphan*/  DISCOV_LE_TIMEOUT ; 
#define  DISCOV_TYPE_BREDR 130 
#define  DISCOV_TYPE_INTERLEAVED 129 
#define  DISCOV_TYPE_LE 128 
 int /*<<< orphan*/  HCI_CMD_TIMEOUT ; 
 scalar_t__ HCI_ERROR_UNSPECIFIED ; 
 int /*<<< orphan*/  HCI_INQUIRY ; 
 int /*<<< orphan*/  HCI_QUIRK_SIMULTANEOUS_DISCOVERY ; 
 int /*<<< orphan*/  HCI_QUIRK_STRICT_DUPLICATE_FILTER ; 
 int /*<<< orphan*/  active_scan ; 
 int /*<<< orphan*/  bredr_inquiry ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_sync (struct hci_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  interleaved_discov ; 
 int /*<<< orphan*/  jiffies ; 
 int jiffies_to_msecs (unsigned long) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void start_discovery(struct hci_dev *hdev, u8 *status)
{
	unsigned long timeout;

	BT_DBG("%s type %u", hdev->name, hdev->discovery.type);

	switch (hdev->discovery.type) {
	case DISCOV_TYPE_BREDR:
		if (!hci_dev_test_flag(hdev, HCI_INQUIRY))
			hci_req_sync(hdev, bredr_inquiry,
				     DISCOV_BREDR_INQUIRY_LEN, HCI_CMD_TIMEOUT,
				     status);
		return;
	case DISCOV_TYPE_INTERLEAVED:
		/* When running simultaneous discovery, the LE scanning time
		 * should occupy the whole discovery time sine BR/EDR inquiry
		 * and LE scanning are scheduled by the controller.
		 *
		 * For interleaving discovery in comparison, BR/EDR inquiry
		 * and LE scanning are done sequentially with separate
		 * timeouts.
		 */
		if (test_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY,
			     &hdev->quirks)) {
			timeout = msecs_to_jiffies(DISCOV_LE_TIMEOUT);
			/* During simultaneous discovery, we double LE scan
			 * interval. We must leave some time for the controller
			 * to do BR/EDR inquiry.
			 */
			hci_req_sync(hdev, interleaved_discov,
				     DISCOV_LE_SCAN_INT * 2, HCI_CMD_TIMEOUT,
				     status);
			break;
		}

		timeout = msecs_to_jiffies(hdev->discov_interleaved_timeout);
		hci_req_sync(hdev, active_scan, DISCOV_LE_SCAN_INT,
			     HCI_CMD_TIMEOUT, status);
		break;
	case DISCOV_TYPE_LE:
		timeout = msecs_to_jiffies(DISCOV_LE_TIMEOUT);
		hci_req_sync(hdev, active_scan, DISCOV_LE_SCAN_INT,
			     HCI_CMD_TIMEOUT, status);
		break;
	default:
		*status = HCI_ERROR_UNSPECIFIED;
		return;
	}

	if (*status)
		return;

	BT_DBG("%s timeout %u ms", hdev->name, jiffies_to_msecs(timeout));

	/* When service discovery is used and the controller has a
	 * strict duplicate filter, it is important to remember the
	 * start and duration of the scan. This is required for
	 * restarting scanning during the discovery phase.
	 */
	if (test_bit(HCI_QUIRK_STRICT_DUPLICATE_FILTER, &hdev->quirks) &&
		     hdev->discovery.result_filtering) {
		hdev->discovery.scan_start = jiffies;
		hdev->discovery.scan_duration = timeout;
	}

	queue_delayed_work(hdev->req_workqueue, &hdev->le_scan_disable,
			   timeout);
}