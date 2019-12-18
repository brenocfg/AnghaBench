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
struct sk_buff {scalar_t__ data; } ;
struct inquiry_entry {int /*<<< orphan*/  name_state; } ;
struct discovery_state {scalar_t__ state; int /*<<< orphan*/  resolve; } ;
struct hci_dev {int /*<<< orphan*/  quirks; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; struct discovery_state discovery; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BDADDR_ANY ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DISCOVERY_FINDING ; 
 int /*<<< orphan*/  DISCOVERY_RESOLVING ; 
 int /*<<< orphan*/  DISCOVERY_STOPPED ; 
 int /*<<< orphan*/  HCI_INQUIRY ; 
 int /*<<< orphan*/  HCI_LE_SCAN ; 
 int /*<<< orphan*/  HCI_MGMT ; 
 int /*<<< orphan*/  HCI_QUIRK_SIMULTANEOUS_DISCOVERY ; 
 int /*<<< orphan*/  NAME_NEEDED ; 
 int /*<<< orphan*/  NAME_PENDING ; 
 int /*<<< orphan*/  hci_conn_check_pending (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_discovery_set_state (struct hci_dev*,int /*<<< orphan*/ ) ; 
 struct inquiry_entry* hci_inquiry_cache_lookup_resolve (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hci_resolve_name (struct hci_dev*,struct inquiry_entry*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_inquiry_complete_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	__u8 status = *((__u8 *) skb->data);
	struct discovery_state *discov = &hdev->discovery;
	struct inquiry_entry *e;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	hci_conn_check_pending(hdev);

	if (!test_and_clear_bit(HCI_INQUIRY, &hdev->flags))
		return;

	smp_mb__after_atomic(); /* wake_up_bit advises about this barrier */
	wake_up_bit(&hdev->flags, HCI_INQUIRY);

	if (!hci_dev_test_flag(hdev, HCI_MGMT))
		return;

	hci_dev_lock(hdev);

	if (discov->state != DISCOVERY_FINDING)
		goto unlock;

	if (list_empty(&discov->resolve)) {
		/* When BR/EDR inquiry is active and no LE scanning is in
		 * progress, then change discovery state to indicate completion.
		 *
		 * When running LE scanning and BR/EDR inquiry simultaneously
		 * and the LE scan already finished, then change the discovery
		 * state to indicate completion.
		 */
		if (!hci_dev_test_flag(hdev, HCI_LE_SCAN) ||
		    !test_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks))
			hci_discovery_set_state(hdev, DISCOVERY_STOPPED);
		goto unlock;
	}

	e = hci_inquiry_cache_lookup_resolve(hdev, BDADDR_ANY, NAME_NEEDED);
	if (e && hci_resolve_name(hdev, e) == 0) {
		e->name_state = NAME_PENDING;
		hci_discovery_set_state(hdev, DISCOVERY_RESOLVING);
	} else {
		/* When BR/EDR inquiry is active and no LE scanning is in
		 * progress, then change discovery state to indicate completion.
		 *
		 * When running LE scanning and BR/EDR inquiry simultaneously
		 * and the LE scan already finished, then change the discovery
		 * state to indicate completion.
		 */
		if (!hci_dev_test_flag(hdev, HCI_LE_SCAN) ||
		    !test_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks))
			hci_discovery_set_state(hdev, DISCOVERY_STOPPED);
	}

unlock:
	hci_dev_unlock(hdev);
}