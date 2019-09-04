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
typedef  int /*<<< orphan*/  u16 ;
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdaddr; } ;
struct mgmt_cp_confirm_name {TYPE_1__ addr; scalar_t__ name_known; } ;
struct inquiry_entry {int /*<<< orphan*/  name_state; int /*<<< orphan*/  list; } ;
struct hci_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGMT_OP_CONFIRM_NAME ; 
 int /*<<< orphan*/  MGMT_STATUS_FAILED ; 
 int /*<<< orphan*/  MGMT_STATUS_INVALID_PARAMS ; 
 int /*<<< orphan*/  NAME_KNOWN ; 
 int /*<<< orphan*/  NAME_NEEDED ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_discovery_active (struct hci_dev*) ; 
 struct inquiry_entry* hci_inquiry_cache_lookup_unknown (struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_inquiry_cache_update_resolve (struct hci_dev*,struct inquiry_entry*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int mgmt_cmd_complete (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static int confirm_name(struct sock *sk, struct hci_dev *hdev, void *data,
			u16 len)
{
	struct mgmt_cp_confirm_name *cp = data;
	struct inquiry_entry *e;
	int err;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	if (!hci_discovery_active(hdev)) {
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_CONFIRM_NAME,
					MGMT_STATUS_FAILED, &cp->addr,
					sizeof(cp->addr));
		goto failed;
	}

	e = hci_inquiry_cache_lookup_unknown(hdev, &cp->addr.bdaddr);
	if (!e) {
		err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_CONFIRM_NAME,
					MGMT_STATUS_INVALID_PARAMS, &cp->addr,
					sizeof(cp->addr));
		goto failed;
	}

	if (cp->name_known) {
		e->name_state = NAME_KNOWN;
		list_del(&e->list);
	} else {
		e->name_state = NAME_NEEDED;
		hci_inquiry_cache_update_resolve(hdev, e);
	}

	err = mgmt_cmd_complete(sk, hdev->id, MGMT_OP_CONFIRM_NAME, 0,
				&cp->addr, sizeof(cp->addr));

failed:
	hci_dev_unlock(hdev);
	return err;
}