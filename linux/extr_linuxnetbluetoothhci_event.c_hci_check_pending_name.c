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
struct TYPE_2__ {int /*<<< orphan*/  rssi; } ;
struct inquiry_entry {int /*<<< orphan*/  name_state; TYPE_1__ data; int /*<<< orphan*/  list; } ;
struct discovery_state {scalar_t__ state; } ;
struct hci_dev {struct discovery_state discovery; } ;
struct hci_conn {scalar_t__ state; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 scalar_t__ BT_CONFIG ; 
 scalar_t__ BT_CONNECTED ; 
 scalar_t__ DISCOVERY_RESOLVING ; 
 scalar_t__ DISCOVERY_STOPPED ; 
 scalar_t__ DISCOVERY_STOPPING ; 
 int /*<<< orphan*/  HCI_CONN_MGMT_CONNECTED ; 
 int /*<<< orphan*/  NAME_KNOWN ; 
 int /*<<< orphan*/  NAME_NOT_KNOWN ; 
 int /*<<< orphan*/  NAME_PENDING ; 
 int /*<<< orphan*/  hci_discovery_set_state (struct hci_dev*,scalar_t__) ; 
 struct inquiry_entry* hci_inquiry_cache_lookup_resolve (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hci_resolve_next_name (struct hci_dev*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mgmt_device_connected (struct hci_dev*,struct hci_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgmt_remote_name (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_check_pending_name(struct hci_dev *hdev, struct hci_conn *conn,
				   bdaddr_t *bdaddr, u8 *name, u8 name_len)
{
	struct discovery_state *discov = &hdev->discovery;
	struct inquiry_entry *e;

	/* Update the mgmt connected state if necessary. Be careful with
	 * conn objects that exist but are not (yet) connected however.
	 * Only those in BT_CONFIG or BT_CONNECTED states can be
	 * considered connected.
	 */
	if (conn &&
	    (conn->state == BT_CONFIG || conn->state == BT_CONNECTED) &&
	    !test_and_set_bit(HCI_CONN_MGMT_CONNECTED, &conn->flags))
		mgmt_device_connected(hdev, conn, 0, name, name_len);

	if (discov->state == DISCOVERY_STOPPED)
		return;

	if (discov->state == DISCOVERY_STOPPING)
		goto discov_complete;

	if (discov->state != DISCOVERY_RESOLVING)
		return;

	e = hci_inquiry_cache_lookup_resolve(hdev, bdaddr, NAME_PENDING);
	/* If the device was not found in a list of found devices names of which
	 * are pending. there is no need to continue resolving a next name as it
	 * will be done upon receiving another Remote Name Request Complete
	 * Event */
	if (!e)
		return;

	list_del(&e->list);
	if (name) {
		e->name_state = NAME_KNOWN;
		mgmt_remote_name(hdev, bdaddr, ACL_LINK, 0x00,
				 e->data.rssi, name, name_len);
	} else {
		e->name_state = NAME_NOT_KNOWN;
	}

	if (hci_resolve_next_name(hdev))
		return;

discov_complete:
	hci_discovery_set_state(hdev, DISCOVERY_STOPPED);
}