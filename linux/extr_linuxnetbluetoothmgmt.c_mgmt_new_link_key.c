#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  bdaddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  pin_len; int /*<<< orphan*/  val; int /*<<< orphan*/  type; TYPE_1__ addr; } ;
struct mgmt_ev_new_link_key {int store_hint; TYPE_2__ key; } ;
struct link_key {int /*<<< orphan*/  pin_len; int /*<<< orphan*/  val; int /*<<< orphan*/  type; int /*<<< orphan*/  bdaddr; } ;
struct hci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
 int /*<<< orphan*/  BDADDR_BREDR ; 
 int /*<<< orphan*/  HCI_LINK_KEY_SIZE ; 
 int /*<<< orphan*/  MGMT_EV_NEW_LINK_KEY ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mgmt_ev_new_link_key*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mgmt_event (int /*<<< orphan*/ ,struct hci_dev*,struct mgmt_ev_new_link_key*,int,int /*<<< orphan*/ *) ; 

void mgmt_new_link_key(struct hci_dev *hdev, struct link_key *key,
		       bool persistent)
{
	struct mgmt_ev_new_link_key ev;

	memset(&ev, 0, sizeof(ev));

	ev.store_hint = persistent;
	bacpy(&ev.key.addr.bdaddr, &key->bdaddr);
	ev.key.addr.type = BDADDR_BREDR;
	ev.key.type = key->type;
	memcpy(ev.key.val, key->val, HCI_LINK_KEY_SIZE);
	ev.key.pin_len = key->pin_len;

	mgmt_event(MGMT_EV_NEW_LINK_KEY, hdev, &ev, sizeof(ev), NULL);
}