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
typedef  int /*<<< orphan*/  u8 ;
struct hci_dev {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct hci_conn {int /*<<< orphan*/  remote_id; } ;
struct amp_mgr {int /*<<< orphan*/  ident; } ;
struct a2mp_physlink_rsp {int /*<<< orphan*/  local_id; int /*<<< orphan*/  status; int /*<<< orphan*/  remote_id; } ;
typedef  int /*<<< orphan*/  rsp ;

/* Variables and functions */
 int /*<<< orphan*/  A2MP_CREATEPHYSLINK_RSP ; 
 int /*<<< orphan*/  A2MP_STATUS_SUCCESS ; 
 int /*<<< orphan*/  A2MP_STATUS_UNABLE_START_LINK_CREATION ; 
 int /*<<< orphan*/  AMP_LINK ; 
 int /*<<< orphan*/  BT_CONNECT ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,struct amp_mgr*,struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_REMOTE_AMP_ASSOC ; 
 int /*<<< orphan*/  a2mp_send (struct amp_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct a2mp_physlink_rsp*) ; 
 struct amp_mgr* amp_mgr_lookup_by_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amp_mgr_put (struct amp_mgr*) ; 
 struct hci_conn* hci_conn_hash_lookup_state (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void a2mp_send_create_phy_link_rsp(struct hci_dev *hdev, u8 status)
{
	struct amp_mgr *mgr;
	struct a2mp_physlink_rsp rsp;
	struct hci_conn *hs_hcon;

	mgr = amp_mgr_lookup_by_state(WRITE_REMOTE_AMP_ASSOC);
	if (!mgr)
		return;

	hs_hcon = hci_conn_hash_lookup_state(hdev, AMP_LINK, BT_CONNECT);
	if (!hs_hcon) {
		rsp.status = A2MP_STATUS_UNABLE_START_LINK_CREATION;
	} else {
		rsp.remote_id = hs_hcon->remote_id;
		rsp.status = A2MP_STATUS_SUCCESS;
	}

	BT_DBG("%s mgr %p hs_hcon %p status %u", hdev->name, mgr, hs_hcon,
	       status);

	rsp.local_id = hdev->id;
	a2mp_send(mgr, A2MP_CREATEPHYSLINK_RSP, mgr->ident, sizeof(rsp), &rsp);
	amp_mgr_put(mgr);
}