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
struct hci_request {struct hci_dev* hdev; } ;
struct hci_dev {int* le_features; } ;
typedef  int /*<<< orphan*/  events ;

/* Variables and functions */
 int HCI_LE_PING ; 
 int /*<<< orphan*/  HCI_OP_SET_EVENT_MASK_PAGE_2 ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ lmp_csb_master_capable (struct hci_dev*) ; 
 scalar_t__ lmp_csb_slave_capable (struct hci_dev*) ; 
 scalar_t__ lmp_ping_capable (struct hci_dev*) ; 

__attribute__((used)) static void hci_set_event_mask_page_2(struct hci_request *req)
{
	struct hci_dev *hdev = req->hdev;
	u8 events[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	bool changed = false;

	/* If Connectionless Slave Broadcast master role is supported
	 * enable all necessary events for it.
	 */
	if (lmp_csb_master_capable(hdev)) {
		events[1] |= 0x40;	/* Triggered Clock Capture */
		events[1] |= 0x80;	/* Synchronization Train Complete */
		events[2] |= 0x10;	/* Slave Page Response Timeout */
		events[2] |= 0x20;	/* CSB Channel Map Change */
		changed = true;
	}

	/* If Connectionless Slave Broadcast slave role is supported
	 * enable all necessary events for it.
	 */
	if (lmp_csb_slave_capable(hdev)) {
		events[2] |= 0x01;	/* Synchronization Train Received */
		events[2] |= 0x02;	/* CSB Receive */
		events[2] |= 0x04;	/* CSB Timeout */
		events[2] |= 0x08;	/* Truncated Page Complete */
		changed = true;
	}

	/* Enable Authenticated Payload Timeout Expired event if supported */
	if (lmp_ping_capable(hdev) || hdev->le_features[0] & HCI_LE_PING) {
		events[2] |= 0x80;
		changed = true;
	}

	/* Some Broadcom based controllers indicate support for Set Event
	 * Mask Page 2 command, but then actually do not support it. Since
	 * the default value is all bits set to zero, the command is only
	 * required if the event mask has to be changed. In case no change
	 * to the event mask is needed, skip this command.
	 */
	if (changed)
		hci_req_add(req, HCI_OP_SET_EVENT_MASK_PAGE_2,
			    sizeof(events), events);
}