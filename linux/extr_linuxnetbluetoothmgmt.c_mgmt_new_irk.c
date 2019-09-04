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
struct smp_irk {int /*<<< orphan*/  val; int /*<<< orphan*/  addr_type; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  rpa; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  bdaddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  val; TYPE_1__ addr; } ;
struct mgmt_ev_new_irk {int store_hint; TYPE_2__ irk; int /*<<< orphan*/  rpa; } ;
struct hci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  ev ;

/* Variables and functions */
 int /*<<< orphan*/  LE_LINK ; 
 int /*<<< orphan*/  MGMT_EV_NEW_IRK ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_to_bdaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct mgmt_ev_new_irk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mgmt_event (int /*<<< orphan*/ ,struct hci_dev*,struct mgmt_ev_new_irk*,int,int /*<<< orphan*/ *) ; 

void mgmt_new_irk(struct hci_dev *hdev, struct smp_irk *irk, bool persistent)
{
	struct mgmt_ev_new_irk ev;

	memset(&ev, 0, sizeof(ev));

	ev.store_hint = persistent;

	bacpy(&ev.rpa, &irk->rpa);
	bacpy(&ev.irk.addr.bdaddr, &irk->bdaddr);
	ev.irk.addr.type = link_to_bdaddr(LE_LINK, irk->addr_type);
	memcpy(ev.irk.val, irk->val, sizeof(irk->val));

	mgmt_event(MGMT_EV_NEW_IRK, hdev, &ev, sizeof(ev), NULL);
}