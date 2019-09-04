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
struct TYPE_2__ {int state; } ;
struct hci_dev {TYPE_1__ discovery; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int,int) ; 
#define  DISCOVERY_FINDING 132 
#define  DISCOVERY_RESOLVING 131 
#define  DISCOVERY_STARTING 130 
#define  DISCOVERY_STOPPED 129 
#define  DISCOVERY_STOPPING 128 
 int /*<<< orphan*/  hci_update_background_scan (struct hci_dev*) ; 
 int /*<<< orphan*/  mgmt_discovering (struct hci_dev*,int) ; 

void hci_discovery_set_state(struct hci_dev *hdev, int state)
{
	int old_state = hdev->discovery.state;

	BT_DBG("%s state %u -> %u", hdev->name, hdev->discovery.state, state);

	if (old_state == state)
		return;

	hdev->discovery.state = state;

	switch (state) {
	case DISCOVERY_STOPPED:
		hci_update_background_scan(hdev);

		if (old_state != DISCOVERY_STARTING)
			mgmt_discovering(hdev, 0);
		break;
	case DISCOVERY_STARTING:
		break;
	case DISCOVERY_FINDING:
		mgmt_discovering(hdev, 1);
		break;
	case DISCOVERY_RESOLVING:
		break;
	case DISCOVERY_STOPPING:
		break;
	}
}