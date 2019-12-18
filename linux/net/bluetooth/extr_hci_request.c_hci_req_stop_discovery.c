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
struct TYPE_2__ {int /*<<< orphan*/  bdaddr; } ;
struct inquiry_entry {TYPE_1__ data; } ;
struct hci_request {struct hci_dev* hdev; } ;
struct discovery_state {scalar_t__ state; scalar_t__ type; } ;
struct hci_dev {int /*<<< orphan*/  le_scan_disable; int /*<<< orphan*/  flags; struct discovery_state discovery; int /*<<< orphan*/  name; } ;
struct hci_cp_remote_name_req_cancel {int /*<<< orphan*/  bdaddr; } ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 int /*<<< orphan*/  BDADDR_ANY ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ DISCOVERY_FINDING ; 
 scalar_t__ DISCOVERY_RESOLVING ; 
 scalar_t__ DISCOVERY_STOPPING ; 
 scalar_t__ DISCOV_TYPE_LE ; 
 int /*<<< orphan*/  HCI_INQUIRY ; 
 int /*<<< orphan*/  HCI_LE_SCAN ; 
 int /*<<< orphan*/  HCI_OP_INQUIRY_CANCEL ; 
 int /*<<< orphan*/  HCI_OP_REMOTE_NAME_REQ_CANCEL ; 
 int /*<<< orphan*/  NAME_PENDING ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 struct inquiry_entry* hci_inquiry_cache_lookup_resolve (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,struct hci_cp_remote_name_req_cancel*) ; 
 int /*<<< orphan*/  hci_req_add_le_scan_disable (struct hci_request*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool hci_req_stop_discovery(struct hci_request *req)
{
	struct hci_dev *hdev = req->hdev;
	struct discovery_state *d = &hdev->discovery;
	struct hci_cp_remote_name_req_cancel cp;
	struct inquiry_entry *e;
	bool ret = false;

	BT_DBG("%s state %u", hdev->name, hdev->discovery.state);

	if (d->state == DISCOVERY_FINDING || d->state == DISCOVERY_STOPPING) {
		if (test_bit(HCI_INQUIRY, &hdev->flags))
			hci_req_add(req, HCI_OP_INQUIRY_CANCEL, 0, NULL);

		if (hci_dev_test_flag(hdev, HCI_LE_SCAN)) {
			cancel_delayed_work(&hdev->le_scan_disable);
			hci_req_add_le_scan_disable(req);
		}

		ret = true;
	} else {
		/* Passive scanning */
		if (hci_dev_test_flag(hdev, HCI_LE_SCAN)) {
			hci_req_add_le_scan_disable(req);
			ret = true;
		}
	}

	/* No further actions needed for LE-only discovery */
	if (d->type == DISCOV_TYPE_LE)
		return ret;

	if (d->state == DISCOVERY_RESOLVING || d->state == DISCOVERY_STOPPING) {
		e = hci_inquiry_cache_lookup_resolve(hdev, BDADDR_ANY,
						     NAME_PENDING);
		if (!e)
			return ret;

		bacpy(&cp.bdaddr, &e->data.bdaddr);
		hci_req_add(req, HCI_OP_REMOTE_NAME_REQ_CANCEL, sizeof(cp),
			    &cp);
		ret = true;
	}

	return ret;
}