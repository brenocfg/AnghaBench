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
typedef  int /*<<< orphan*/  u8 ;
struct hci_dev {int dummy; } ;
struct hci_conn {int /*<<< orphan*/  amp_mgr; int /*<<< orphan*/  remote_id; int /*<<< orphan*/  handle; int /*<<< orphan*/  attempt; int /*<<< orphan*/  state; } ;
struct amp_mgr {TYPE_2__* l2cap_conn; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_4__ {TYPE_1__* hcon; } ;
struct TYPE_3__ {int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMP_LINK ; 
 int /*<<< orphan*/  BT_CONNECT ; 
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HCI_ROLE_MASTER ; 
 int /*<<< orphan*/  HCI_ROLE_SLAVE ; 
 int /*<<< orphan*/  __next_handle (struct amp_mgr*) ; 
 int /*<<< orphan*/  amp_mgr_get (struct amp_mgr*) ; 
 struct hci_conn* hci_conn_add (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct hci_conn *phylink_add(struct hci_dev *hdev, struct amp_mgr *mgr,
			     u8 remote_id, bool out)
{
	bdaddr_t *dst = &mgr->l2cap_conn->hcon->dst;
	struct hci_conn *hcon;
	u8 role = out ? HCI_ROLE_MASTER : HCI_ROLE_SLAVE;

	hcon = hci_conn_add(hdev, AMP_LINK, dst, role);
	if (!hcon)
		return NULL;

	BT_DBG("hcon %p dst %pMR", hcon, dst);

	hcon->state = BT_CONNECT;
	hcon->attempt++;
	hcon->handle = __next_handle(mgr);
	hcon->remote_id = remote_id;
	hcon->amp_mgr = amp_mgr_get(mgr);

	return hcon;
}