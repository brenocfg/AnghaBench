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
typedef  int u8 ;
struct smp_cmd_pairing {int init_key_dist; int resp_key_dist; int auth_req; int /*<<< orphan*/  io_capability; } ;
struct smp_chan {int remote_key_dist; int /*<<< orphan*/  flags; int /*<<< orphan*/ * prsp; int /*<<< orphan*/ * preq; struct l2cap_conn* conn; } ;
struct l2cap_conn {struct hci_conn* hcon; } ;
struct hci_dev {int dummy; } ;
struct hci_conn {scalar_t__ out; struct hci_dev* hdev; } ;

/* Variables and functions */
 int AUTH_REQ_MASK (struct hci_dev*) ; 
 int /*<<< orphan*/  HCI_SC_ONLY ; 
 int /*<<< orphan*/  SMP_FLAG_SC ; 
 int SMP_UNSPECIFIED ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ tk_request (struct l2cap_conn*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fixup_sc_false_positive(struct smp_chan *smp)
{
	struct l2cap_conn *conn = smp->conn;
	struct hci_conn *hcon = conn->hcon;
	struct hci_dev *hdev = hcon->hdev;
	struct smp_cmd_pairing *req, *rsp;
	u8 auth;

	/* The issue is only observed when we're in slave role */
	if (hcon->out)
		return SMP_UNSPECIFIED;

	if (hci_dev_test_flag(hdev, HCI_SC_ONLY)) {
		bt_dev_err(hdev, "refusing legacy fallback in SC-only mode");
		return SMP_UNSPECIFIED;
	}

	bt_dev_err(hdev, "trying to fall back to legacy SMP");

	req = (void *) &smp->preq[1];
	rsp = (void *) &smp->prsp[1];

	/* Rebuild key dist flags which may have been cleared for SC */
	smp->remote_key_dist = (req->init_key_dist & rsp->resp_key_dist);

	auth = req->auth_req & AUTH_REQ_MASK(hdev);

	if (tk_request(conn, 0, auth, rsp->io_capability, req->io_capability)) {
		bt_dev_err(hdev, "failed to fall back to legacy SMP");
		return SMP_UNSPECIFIED;
	}

	clear_bit(SMP_FLAG_SC, &smp->flags);

	return 0;
}