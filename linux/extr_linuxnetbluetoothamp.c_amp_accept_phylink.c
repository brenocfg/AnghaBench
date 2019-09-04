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
struct hci_request {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_cp_accept_phy_link {int /*<<< orphan*/  key_type; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  phy_handle; } ;
struct hci_conn {int /*<<< orphan*/  handle; } ;
struct amp_mgr {TYPE_1__* l2cap_conn; } ;
typedef  int /*<<< orphan*/  cp ;
struct TYPE_2__ {int /*<<< orphan*/  hcon; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  HCI_OP_ACCEPT_PHY_LINK ; 
 int /*<<< orphan*/  accept_phylink_complete ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,struct hci_cp_accept_phy_link*) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_run (struct hci_request*,int /*<<< orphan*/ ) ; 
 scalar_t__ phylink_gen_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void amp_accept_phylink(struct hci_dev *hdev, struct amp_mgr *mgr,
			struct hci_conn *hcon)
{
	struct hci_cp_accept_phy_link cp;
	struct hci_request req;

	cp.phy_handle = hcon->handle;

	BT_DBG("%s hcon %p phy handle 0x%2.2x", hdev->name, hcon,
	       hcon->handle);

	if (phylink_gen_key(mgr->l2cap_conn->hcon, cp.key, &cp.key_len,
			    &cp.key_type)) {
		BT_DBG("Cannot create link key");
		return;
	}

	hci_req_init(&req, hdev);
	hci_req_add(&req, HCI_OP_ACCEPT_PHY_LINK, sizeof(cp), &cp);
	hci_req_run(&req, accept_phylink_complete);
}