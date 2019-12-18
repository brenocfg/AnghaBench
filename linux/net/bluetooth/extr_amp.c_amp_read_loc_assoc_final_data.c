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
struct hci_request {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  amp_assoc_size; } ;
struct hci_cp_read_local_amp_assoc {void* max_len; void* len_so_far; int /*<<< orphan*/  phy_handle; } ;
struct hci_conn {int /*<<< orphan*/  handle; struct amp_mgr* amp_mgr; } ;
struct amp_mgr {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 int /*<<< orphan*/  A2MP_STATUS_INVALID_CTRL_ID ; 
 int /*<<< orphan*/  HCI_OP_READ_LOCAL_AMP_ASSOC ; 
 int /*<<< orphan*/  READ_LOC_AMP_ASSOC_FINAL ; 
 int /*<<< orphan*/  a2mp_send_getampassoc_rsp (struct hci_dev*,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_add (struct hci_request*,int /*<<< orphan*/ ,int,struct hci_cp_read_local_amp_assoc*) ; 
 int /*<<< orphan*/  hci_req_init (struct hci_request*,struct hci_dev*) ; 
 int hci_req_run_skb (struct hci_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_local_amp_assoc_complete ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void amp_read_loc_assoc_final_data(struct hci_dev *hdev,
				   struct hci_conn *hcon)
{
	struct hci_cp_read_local_amp_assoc cp;
	struct amp_mgr *mgr = hcon->amp_mgr;
	struct hci_request req;
	int err;

	cp.phy_handle = hcon->handle;
	cp.len_so_far = cpu_to_le16(0);
	cp.max_len = cpu_to_le16(hdev->amp_assoc_size);

	set_bit(READ_LOC_AMP_ASSOC_FINAL, &mgr->state);

	/* Read Local AMP Assoc final link information data */
	hci_req_init(&req, hdev);
	hci_req_add(&req, HCI_OP_READ_LOCAL_AMP_ASSOC, sizeof(cp), &cp);
	err = hci_req_run_skb(&req, read_local_amp_assoc_complete);
	if (err < 0)
		a2mp_send_getampassoc_rsp(hdev, A2MP_STATUS_INVALID_CTRL_ID);
}