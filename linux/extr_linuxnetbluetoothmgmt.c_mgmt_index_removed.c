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
typedef  int /*<<< orphan*/  u8 ;
struct mgmt_ev_ext_index {int type; int /*<<< orphan*/  bus; } ;
struct hci_dev {int dev_type; int /*<<< orphan*/  bus; int /*<<< orphan*/  quirks; } ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
#define  HCI_AMP 129 
 int /*<<< orphan*/  HCI_MGMT_EXT_INDEX_EVENTS ; 
 int /*<<< orphan*/  HCI_MGMT_INDEX_EVENTS ; 
 int /*<<< orphan*/  HCI_MGMT_UNCONF_INDEX_EVENTS ; 
#define  HCI_PRIMARY 128 
 int /*<<< orphan*/  HCI_QUIRK_RAW_DEVICE ; 
 int /*<<< orphan*/  HCI_UNCONFIGURED ; 
 int /*<<< orphan*/  MGMT_EV_EXT_INDEX_REMOVED ; 
 int /*<<< orphan*/  MGMT_EV_INDEX_REMOVED ; 
 int /*<<< orphan*/  MGMT_EV_UNCONF_INDEX_REMOVED ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_INDEX ; 
 int /*<<< orphan*/  cmd_complete_rsp ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_index_event (int /*<<< orphan*/ ,struct hci_dev*,struct mgmt_ev_ext_index*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_pending_foreach (int /*<<< orphan*/ ,struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mgmt_index_removed(struct hci_dev *hdev)
{
	struct mgmt_ev_ext_index ev;
	u8 status = MGMT_STATUS_INVALID_INDEX;

	if (test_bit(HCI_QUIRK_RAW_DEVICE, &hdev->quirks))
		return;

	switch (hdev->dev_type) {
	case HCI_PRIMARY:
		mgmt_pending_foreach(0, hdev, cmd_complete_rsp, &status);

		if (hci_dev_test_flag(hdev, HCI_UNCONFIGURED)) {
			mgmt_index_event(MGMT_EV_UNCONF_INDEX_REMOVED, hdev,
					 NULL, 0, HCI_MGMT_UNCONF_INDEX_EVENTS);
			ev.type = 0x01;
		} else {
			mgmt_index_event(MGMT_EV_INDEX_REMOVED, hdev, NULL, 0,
					 HCI_MGMT_INDEX_EVENTS);
			ev.type = 0x00;
		}
		break;
	case HCI_AMP:
		ev.type = 0x02;
		break;
	default:
		return;
	}

	ev.bus = hdev->bus;

	mgmt_index_event(MGMT_EV_EXT_INDEX_REMOVED, hdev, &ev, sizeof(ev),
			 HCI_MGMT_EXT_INDEX_EVENTS);
}