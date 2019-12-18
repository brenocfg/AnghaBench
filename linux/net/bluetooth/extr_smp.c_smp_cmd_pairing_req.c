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
typedef  int u8 ;
struct smp_cmd_pairing {int auth_req; scalar_t__ oob_flag; int /*<<< orphan*/  io_capability; int /*<<< orphan*/  max_key_size; } ;
struct smp_chan {int /*<<< orphan*/  remote_key_dist; int /*<<< orphan*/  flags; void** prsp; int /*<<< orphan*/  prnd; void** preq; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct l2cap_conn {TYPE_1__* hcon; struct l2cap_chan* smp; } ;
struct l2cap_chan {struct smp_chan* data; } ;
struct hci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  rsp ;
struct TYPE_4__ {scalar_t__ local_oob; } ;
struct TYPE_3__ {scalar_t__ role; scalar_t__ type; int pending_sec_level; int /*<<< orphan*/  io_capability; int /*<<< orphan*/  flags; struct hci_dev* hdev; } ;

/* Variables and functions */
 scalar_t__ ACL_LINK ; 
 int AUTH_REQ_MASK (struct hci_dev*) ; 
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_conn*) ; 
 scalar_t__ BT_SECURITY_HIGH ; 
 int BT_SECURITY_MEDIUM ; 
 int /*<<< orphan*/  HCI_BONDABLE ; 
 int /*<<< orphan*/  HCI_CONN_AES_CCM ; 
 int /*<<< orphan*/  HCI_FORCE_BREDR_SMP ; 
 int /*<<< orphan*/  HCI_IO_NO_INPUT_OUTPUT ; 
 scalar_t__ HCI_ROLE_SLAVE ; 
 int /*<<< orphan*/  HCI_SC_ONLY ; 
 int JUST_CFM ; 
 int JUST_WORKS ; 
 int /*<<< orphan*/  SMP_ALLOW_CMD (struct smp_chan*,int /*<<< orphan*/ ) ; 
 int SMP_AUTH_BONDING ; 
 int SMP_AUTH_CT2 ; 
 int SMP_AUTH_REQUIREMENTS ; 
 int SMP_AUTH_SC ; 
 int SMP_CMD_NOTSUPP ; 
 int /*<<< orphan*/  SMP_CMD_PAIRING_CONFIRM ; 
 void* SMP_CMD_PAIRING_REQ ; 
 void* SMP_CMD_PAIRING_RSP ; 
 int /*<<< orphan*/  SMP_CMD_PUBLIC_KEY ; 
 int SMP_CROSS_TRANSP_NOT_ALLOWED ; 
 TYPE_2__* SMP_DEV (struct hci_dev*) ; 
 int SMP_ENC_KEY_SIZE ; 
 int /*<<< orphan*/  SMP_FLAG_CT2 ; 
 int /*<<< orphan*/  SMP_FLAG_INITIATOR ; 
 int /*<<< orphan*/  SMP_FLAG_LOCAL_OOB ; 
 int /*<<< orphan*/  SMP_FLAG_SC ; 
 int SMP_INVALID_PARAMS ; 
 scalar_t__ SMP_OOB_PRESENT ; 
 int SMP_PAIRING_NOTSUPP ; 
 int /*<<< orphan*/  SMP_SC_NO_DIST ; 
 int SMP_UNSPECIFIED ; 
 int authreq_to_seclevel (int) ; 
 int /*<<< orphan*/  build_bredr_pairing_cmd (struct smp_chan*,struct smp_cmd_pairing*,struct smp_cmd_pairing*) ; 
 int /*<<< orphan*/  build_pairing_cmd (struct l2cap_conn*,struct smp_cmd_pairing*,struct smp_cmd_pairing*,int) ; 
 scalar_t__ check_enc_key_size (struct l2cap_conn*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int get_auth_method (struct smp_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void**,struct smp_cmd_pairing*,int) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 struct smp_chan* smp_chan_create (struct l2cap_conn*) ; 
 int /*<<< orphan*/  smp_distribute_keys (struct smp_chan*) ; 
 int /*<<< orphan*/  smp_send_cmd (struct l2cap_conn*,void*,int,struct smp_cmd_pairing*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tk_request (struct l2cap_conn*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 smp_cmd_pairing_req(struct l2cap_conn *conn, struct sk_buff *skb)
{
	struct smp_cmd_pairing rsp, *req = (void *) skb->data;
	struct l2cap_chan *chan = conn->smp;
	struct hci_dev *hdev = conn->hcon->hdev;
	struct smp_chan *smp;
	u8 key_size, auth, sec_level;
	int ret;

	BT_DBG("conn %p", conn);

	if (skb->len < sizeof(*req))
		return SMP_INVALID_PARAMS;

	if (conn->hcon->role != HCI_ROLE_SLAVE)
		return SMP_CMD_NOTSUPP;

	if (!chan->data)
		smp = smp_chan_create(conn);
	else
		smp = chan->data;

	if (!smp)
		return SMP_UNSPECIFIED;

	/* We didn't start the pairing, so match remote */
	auth = req->auth_req & AUTH_REQ_MASK(hdev);

	if (!hci_dev_test_flag(hdev, HCI_BONDABLE) &&
	    (auth & SMP_AUTH_BONDING))
		return SMP_PAIRING_NOTSUPP;

	if (hci_dev_test_flag(hdev, HCI_SC_ONLY) && !(auth & SMP_AUTH_SC))
		return SMP_AUTH_REQUIREMENTS;

	smp->preq[0] = SMP_CMD_PAIRING_REQ;
	memcpy(&smp->preq[1], req, sizeof(*req));
	skb_pull(skb, sizeof(*req));

	/* If the remote side's OOB flag is set it means it has
	 * successfully received our local OOB data - therefore set the
	 * flag to indicate that local OOB is in use.
	 */
	if (req->oob_flag == SMP_OOB_PRESENT && SMP_DEV(hdev)->local_oob)
		set_bit(SMP_FLAG_LOCAL_OOB, &smp->flags);

	/* SMP over BR/EDR requires special treatment */
	if (conn->hcon->type == ACL_LINK) {
		/* We must have a BR/EDR SC link */
		if (!test_bit(HCI_CONN_AES_CCM, &conn->hcon->flags) &&
		    !hci_dev_test_flag(hdev, HCI_FORCE_BREDR_SMP))
			return SMP_CROSS_TRANSP_NOT_ALLOWED;

		set_bit(SMP_FLAG_SC, &smp->flags);

		build_bredr_pairing_cmd(smp, req, &rsp);

		if (req->auth_req & SMP_AUTH_CT2)
			set_bit(SMP_FLAG_CT2, &smp->flags);

		key_size = min(req->max_key_size, rsp.max_key_size);
		if (check_enc_key_size(conn, key_size))
			return SMP_ENC_KEY_SIZE;

		/* Clear bits which are generated but not distributed */
		smp->remote_key_dist &= ~SMP_SC_NO_DIST;

		smp->prsp[0] = SMP_CMD_PAIRING_RSP;
		memcpy(&smp->prsp[1], &rsp, sizeof(rsp));
		smp_send_cmd(conn, SMP_CMD_PAIRING_RSP, sizeof(rsp), &rsp);

		smp_distribute_keys(smp);
		return 0;
	}

	build_pairing_cmd(conn, req, &rsp, auth);

	if (rsp.auth_req & SMP_AUTH_SC) {
		set_bit(SMP_FLAG_SC, &smp->flags);

		if (rsp.auth_req & SMP_AUTH_CT2)
			set_bit(SMP_FLAG_CT2, &smp->flags);
	}

	if (conn->hcon->io_capability == HCI_IO_NO_INPUT_OUTPUT)
		sec_level = BT_SECURITY_MEDIUM;
	else
		sec_level = authreq_to_seclevel(auth);

	if (sec_level > conn->hcon->pending_sec_level)
		conn->hcon->pending_sec_level = sec_level;

	/* If we need MITM check that it can be achieved */
	if (conn->hcon->pending_sec_level >= BT_SECURITY_HIGH) {
		u8 method;

		method = get_auth_method(smp, conn->hcon->io_capability,
					 req->io_capability);
		if (method == JUST_WORKS || method == JUST_CFM)
			return SMP_AUTH_REQUIREMENTS;
	}

	key_size = min(req->max_key_size, rsp.max_key_size);
	if (check_enc_key_size(conn, key_size))
		return SMP_ENC_KEY_SIZE;

	get_random_bytes(smp->prnd, sizeof(smp->prnd));

	smp->prsp[0] = SMP_CMD_PAIRING_RSP;
	memcpy(&smp->prsp[1], &rsp, sizeof(rsp));

	smp_send_cmd(conn, SMP_CMD_PAIRING_RSP, sizeof(rsp), &rsp);

	clear_bit(SMP_FLAG_INITIATOR, &smp->flags);

	/* Strictly speaking we shouldn't allow Pairing Confirm for the
	 * SC case, however some implementations incorrectly copy RFU auth
	 * req bits from our security request, which may create a false
	 * positive SC enablement.
	 */
	SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_CONFIRM);

	if (test_bit(SMP_FLAG_SC, &smp->flags)) {
		SMP_ALLOW_CMD(smp, SMP_CMD_PUBLIC_KEY);
		/* Clear bits which are generated but not distributed */
		smp->remote_key_dist &= ~SMP_SC_NO_DIST;
		/* Wait for Public Key from Initiating Device */
		return 0;
	}

	/* Request setup of TK */
	ret = tk_request(conn, 0, auth, rsp.io_capability, req->io_capability);
	if (ret)
		return SMP_UNSPECIFIED;

	return 0;
}