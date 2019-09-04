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
struct smp_cmd_pairing {int dummy; } ;
struct smp_chan {int /*<<< orphan*/ * preq; int /*<<< orphan*/  flags; } ;
struct l2cap_conn {int remote_fixed_chan; struct hci_conn* hcon; } ;
struct l2cap_chan {scalar_t__ data; struct l2cap_conn* conn; } ;
struct hci_dev {struct l2cap_chan* name; } ;
struct hci_conn {scalar_t__ role; int /*<<< orphan*/  flags; struct hci_dev* hdev; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*) ; 
 int /*<<< orphan*/  HCI_CONN_AES_CCM ; 
 int /*<<< orphan*/  HCI_CONN_ENCRYPT ; 
 int /*<<< orphan*/  HCI_CONN_NEW_LINK_KEY ; 
 int /*<<< orphan*/  HCI_FORCE_BREDR_SMP ; 
 int /*<<< orphan*/  HCI_LE_ENABLED ; 
 scalar_t__ HCI_ROLE_MASTER ; 
 int /*<<< orphan*/  HCI_SC_ENABLED ; 
 int L2CAP_FC_SMP_BREDR ; 
 int /*<<< orphan*/  SMP_ALLOW_CMD (struct smp_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_CMD_PAIRING_REQ ; 
 int /*<<< orphan*/  SMP_CMD_PAIRING_RSP ; 
 int /*<<< orphan*/  SMP_FLAG_SC ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*) ; 
 int /*<<< orphan*/  build_bredr_pairing_cmd (struct smp_chan*,struct smp_cmd_pairing*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lmp_host_le_capable (struct hci_conn*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct smp_cmd_pairing*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct smp_chan* smp_chan_create (struct l2cap_conn*) ; 
 int /*<<< orphan*/  smp_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int,struct smp_cmd_pairing*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bredr_pairing(struct l2cap_chan *chan)
{
	struct l2cap_conn *conn = chan->conn;
	struct hci_conn *hcon = conn->hcon;
	struct hci_dev *hdev = hcon->hdev;
	struct smp_cmd_pairing req;
	struct smp_chan *smp;

	BT_DBG("chan %p", chan);

	/* Only new pairings are interesting */
	if (!test_bit(HCI_CONN_NEW_LINK_KEY, &hcon->flags))
		return;

	/* Don't bother if we're not encrypted */
	if (!test_bit(HCI_CONN_ENCRYPT, &hcon->flags))
		return;

	/* Only master may initiate SMP over BR/EDR */
	if (hcon->role != HCI_ROLE_MASTER)
		return;

	/* Secure Connections support must be enabled */
	if (!hci_dev_test_flag(hdev, HCI_SC_ENABLED))
		return;

	/* BR/EDR must use Secure Connections for SMP */
	if (!test_bit(HCI_CONN_AES_CCM, &hcon->flags) &&
	    !hci_dev_test_flag(hdev, HCI_FORCE_BREDR_SMP))
		return;

	/* If our LE support is not enabled don't do anything */
	if (!hci_dev_test_flag(hdev, HCI_LE_ENABLED))
		return;

	/* Don't bother if remote LE support is not enabled */
	if (!lmp_host_le_capable(hcon))
		return;

	/* Remote must support SMP fixed chan for BR/EDR */
	if (!(conn->remote_fixed_chan & L2CAP_FC_SMP_BREDR))
		return;

	/* Don't bother if SMP is already ongoing */
	if (chan->data)
		return;

	smp = smp_chan_create(conn);
	if (!smp) {
		bt_dev_err(hdev, "unable to create SMP context for BR/EDR");
		return;
	}

	set_bit(SMP_FLAG_SC, &smp->flags);

	BT_DBG("%s starting SMP over BR/EDR", hdev->name);

	/* Prepare and send the BR/EDR SMP Pairing Request */
	build_bredr_pairing_cmd(smp, &req, NULL);

	smp->preq[0] = SMP_CMD_PAIRING_REQ;
	memcpy(&smp->preq[1], &req, sizeof(req));

	smp_send_cmd(conn, SMP_CMD_PAIRING_REQ, sizeof(req), &req);
	SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_RSP);
}