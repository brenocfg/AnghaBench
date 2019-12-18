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
typedef  int /*<<< orphan*/  u8 ;
struct mgmt_ev_discovering {int /*<<< orphan*/  discovering; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct hci_dev {TYPE_1__ discovery; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGMT_EV_DISCOVERING ; 
 int /*<<< orphan*/  memset (struct mgmt_ev_discovering*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mgmt_event (int /*<<< orphan*/ ,struct hci_dev*,struct mgmt_ev_discovering*,int,int /*<<< orphan*/ *) ; 

void mgmt_discovering(struct hci_dev *hdev, u8 discovering)
{
	struct mgmt_ev_discovering ev;

	BT_DBG("%s discovering %u", hdev->name, discovering);

	memset(&ev, 0, sizeof(ev));
	ev.type = hdev->discovery.type;
	ev.discovering = discovering;

	mgmt_event(MGMT_EV_DISCOVERING, hdev, &ev, sizeof(ev), NULL);
}