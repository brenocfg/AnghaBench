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
struct hci_dev {scalar_t__ hci_ver; int* commands; int* le_features; int /*<<< orphan*/  quirks; } ;
typedef  int /*<<< orphan*/  events ;

/* Variables and functions */
 scalar_t__ BLUETOOTH_VER_1_2 ; 
 int HCI_LE_ENCRYPTION ; 
 int /*<<< orphan*/  HCI_OP_SET_EVENT_MASK ; 
 int /*<<< orphan*/  HCI_QUIRK_FIXUP_INQUIRY_MODE ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ lmp_bredr_capable (struct hci_dev*) ; 
 scalar_t__ lmp_esco_capable (struct hci_dev*) ; 
 scalar_t__ lmp_ext_feat_capable (struct hci_dev*) ; 
 scalar_t__ lmp_ext_inq_capable (struct hci_dev*) ; 
 scalar_t__ lmp_inq_rssi_capable (struct hci_dev*) ; 
 scalar_t__ lmp_le_capable (struct hci_dev*) ; 
 scalar_t__ lmp_lsto_capable (struct hci_dev*) ; 
 scalar_t__ lmp_no_flush_capable (struct hci_dev*) ; 
 scalar_t__ lmp_pause_enc_capable (struct hci_dev*) ; 
 scalar_t__ lmp_sniffsubr_capable (struct hci_dev*) ; 
 scalar_t__ lmp_ssp_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_setup_event_mask(struct hci_request *req)
{
	struct hci_dev *hdev = req->hdev;

	/* The second byte is 0xff instead of 0x9f (two reserved bits
	 * disabled) since a Broadcom 1.2 dongle doesn't respond to the
	 * command otherwise.
	 */
	u8 events[8] = { 0xff, 0xff, 0xfb, 0xff, 0x00, 0x00, 0x00, 0x00 };

	/* CSR 1.1 dongles does not accept any bitfield so don't try to set
	 * any event mask for pre 1.2 devices.
	 */
	if (hdev->hci_ver < BLUETOOTH_VER_1_2)
		return;

	if (lmp_bredr_capable(hdev)) {
		events[4] |= 0x01; /* Flow Specification Complete */
	} else {
		/* Use a different default for LE-only devices */
		memset(events, 0, sizeof(events));
		events[1] |= 0x20; /* Command Complete */
		events[1] |= 0x40; /* Command Status */
		events[1] |= 0x80; /* Hardware Error */

		/* If the controller supports the Disconnect command, enable
		 * the corresponding event. In addition enable packet flow
		 * control related events.
		 */
		if (hdev->commands[0] & 0x20) {
			events[0] |= 0x10; /* Disconnection Complete */
			events[2] |= 0x04; /* Number of Completed Packets */
			events[3] |= 0x02; /* Data Buffer Overflow */
		}

		/* If the controller supports the Read Remote Version
		 * Information command, enable the corresponding event.
		 */
		if (hdev->commands[2] & 0x80)
			events[1] |= 0x08; /* Read Remote Version Information
					    * Complete
					    */

		if (hdev->le_features[0] & HCI_LE_ENCRYPTION) {
			events[0] |= 0x80; /* Encryption Change */
			events[5] |= 0x80; /* Encryption Key Refresh Complete */
		}
	}

	if (lmp_inq_rssi_capable(hdev) ||
	    test_bit(HCI_QUIRK_FIXUP_INQUIRY_MODE, &hdev->quirks))
		events[4] |= 0x02; /* Inquiry Result with RSSI */

	if (lmp_ext_feat_capable(hdev))
		events[4] |= 0x04; /* Read Remote Extended Features Complete */

	if (lmp_esco_capable(hdev)) {
		events[5] |= 0x08; /* Synchronous Connection Complete */
		events[5] |= 0x10; /* Synchronous Connection Changed */
	}

	if (lmp_sniffsubr_capable(hdev))
		events[5] |= 0x20; /* Sniff Subrating */

	if (lmp_pause_enc_capable(hdev))
		events[5] |= 0x80; /* Encryption Key Refresh Complete */

	if (lmp_ext_inq_capable(hdev))
		events[5] |= 0x40; /* Extended Inquiry Result */

	if (lmp_no_flush_capable(hdev))
		events[7] |= 0x01; /* Enhanced Flush Complete */

	if (lmp_lsto_capable(hdev))
		events[6] |= 0x80; /* Link Supervision Timeout Changed */

	if (lmp_ssp_capable(hdev)) {
		events[6] |= 0x01;	/* IO Capability Request */
		events[6] |= 0x02;	/* IO Capability Response */
		events[6] |= 0x04;	/* User Confirmation Request */
		events[6] |= 0x08;	/* User Passkey Request */
		events[6] |= 0x10;	/* Remote OOB Data Request */
		events[6] |= 0x20;	/* Simple Pairing Complete */
		events[7] |= 0x04;	/* User Passkey Notification */
		events[7] |= 0x08;	/* Keypress Notification */
		events[7] |= 0x10;	/* Remote Host Supported
					 * Features Notification
					 */
	}

	if (lmp_le_capable(hdev))
		events[7] |= 0x20;	/* LE Meta-Event */

	hci_req_add(req, HCI_OP_SET_EVENT_MASK, sizeof(events), events);
}