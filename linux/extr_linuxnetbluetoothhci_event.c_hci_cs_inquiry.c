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
struct hci_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HCI_INQUIRY ; 
 int /*<<< orphan*/  hci_conn_check_pending (struct hci_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_cs_inquiry(struct hci_dev *hdev, __u8 status)
{
	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	if (status) {
		hci_conn_check_pending(hdev);
		return;
	}

	set_bit(HCI_INQUIRY, &hdev->flags);
}