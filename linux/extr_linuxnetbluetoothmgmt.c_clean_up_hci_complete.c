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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct hci_dev {TYPE_1__ power_off; int /*<<< orphan*/  req_workqueue; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (TYPE_1__*) ; 
 scalar_t__ hci_conn_count (struct hci_dev*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clean_up_hci_complete(struct hci_dev *hdev, u8 status, u16 opcode)
{
	BT_DBG("%s status 0x%02x", hdev->name, status);

	if (hci_conn_count(hdev) == 0) {
		cancel_delayed_work(&hdev->power_off);
		queue_work(hdev->req_workqueue, &hdev->power_off.work);
	}
}