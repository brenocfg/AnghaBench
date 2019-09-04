#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* b; } ;
struct smp_csrk {scalar_t__ bdaddr_type; int /*<<< orphan*/  val; int /*<<< orphan*/  type; TYPE_3__ bdaddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  bdaddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  val; int /*<<< orphan*/  type; TYPE_1__ addr; } ;
struct mgmt_ev_new_csrk {int store_hint; TYPE_2__ key; } ;
struct hci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
 scalar_t__ ADDR_LE_DEV_RANDOM ; 
 int /*<<< orphan*/  LE_LINK ; 
 int /*<<< orphan*/  MGMT_EV_NEW_CSRK ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  link_to_bdaddr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct mgmt_ev_new_csrk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mgmt_event (int /*<<< orphan*/ ,struct hci_dev*,struct mgmt_ev_new_csrk*,int,int /*<<< orphan*/ *) ; 

void mgmt_new_csrk(struct hci_dev *hdev, struct smp_csrk *csrk,
		   bool persistent)
{
	struct mgmt_ev_new_csrk ev;

	memset(&ev, 0, sizeof(ev));

	/* Devices using resolvable or non-resolvable random addresses
	 * without providing an identity resolving key don't require
	 * to store signature resolving keys. Their addresses will change
	 * the next time around.
	 *
	 * Only when a remote device provides an identity address
	 * make sure the signature resolving key is stored. So allow
	 * static random and public addresses here.
	 */
	if (csrk->bdaddr_type == ADDR_LE_DEV_RANDOM &&
	    (csrk->bdaddr.b[5] & 0xc0) != 0xc0)
		ev.store_hint = 0x00;
	else
		ev.store_hint = persistent;

	bacpy(&ev.key.addr.bdaddr, &csrk->bdaddr);
	ev.key.addr.type = link_to_bdaddr(LE_LINK, csrk->bdaddr_type);
	ev.key.type = csrk->type;
	memcpy(ev.key.val, csrk->val, sizeof(csrk->val));

	mgmt_event(MGMT_EV_NEW_CSRK, hdev, &ev, sizeof(ev), NULL);
}