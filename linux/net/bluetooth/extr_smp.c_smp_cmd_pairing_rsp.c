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
typedef  scalar_t__ u8 ;
struct smp_cmd_pairing {scalar_t__ auth_req; scalar_t__ oob_flag; int /*<<< orphan*/  io_capability; int /*<<< orphan*/  resp_key_dist; int /*<<< orphan*/  max_key_size; } ;
struct smp_chan {int /*<<< orphan*/  flags; int /*<<< orphan*/  remote_key_dist; int /*<<< orphan*/  prnd; int /*<<< orphan*/ * prsp; int /*<<< orphan*/ * preq; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct l2cap_conn {TYPE_1__* hcon; struct l2cap_chan* smp; } ;
struct l2cap_chan {struct smp_chan* data; } ;
struct hci_dev {int dummy; } ;
struct TYPE_4__ {scalar_t__ local_oob; } ;
struct TYPE_3__ {scalar_t__ role; scalar_t__ type; scalar_t__ pending_sec_level; struct hci_dev* hdev; } ;

/* Variables and functions */
 scalar_t__ ACL_LINK ; 
 scalar_t__ AUTH_REQ_MASK (struct hci_dev*) ; 
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_conn*) ; 
 scalar_t__ BT_SECURITY_HIGH ; 
 scalar_t__ HCI_ROLE_MASTER ; 
 int /*<<< orphan*/  HCI_SC_ONLY ; 
 scalar_t__ JUST_CFM ; 
 scalar_t__ JUST_WORKS ; 
 int /*<<< orphan*/  SMP_ALLOW_CMD (struct smp_chan*,int /*<<< orphan*/ ) ; 
 scalar_t__ SMP_AUTH_CT2 ; 
 scalar_t__ SMP_AUTH_REQUIREMENTS ; 
 scalar_t__ SMP_AUTH_SC ; 
 scalar_t__ SMP_CMD_NOTSUPP ; 
 int /*<<< orphan*/  SMP_CMD_PAIRING_RSP ; 
 int /*<<< orphan*/  SMP_CMD_PUBLIC_KEY ; 
 TYPE_2__* SMP_DEV (struct hci_dev*) ; 
 scalar_t__ SMP_ENC_KEY_SIZE ; 
 int /*<<< orphan*/  SMP_FLAG_CFM_PENDING ; 
 int /*<<< orphan*/  SMP_FLAG_CT2 ; 
 int /*<<< orphan*/  SMP_FLAG_LOCAL_OOB ; 
 int /*<<< orphan*/  SMP_FLAG_SC ; 
 int /*<<< orphan*/  SMP_FLAG_TK_VALID ; 
 scalar_t__ SMP_INVALID_PARAMS ; 
 scalar_t__ SMP_OOB_PRESENT ; 
 int /*<<< orphan*/  SMP_SC_NO_DIST ; 
 scalar_t__ SMP_UNSPECIFIED ; 
 scalar_t__ check_enc_key_size (struct l2cap_conn*,scalar_t__) ; 
 scalar_t__ get_auth_method (struct smp_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct smp_cmd_pairing*,int) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sc_send_public_key (struct smp_chan*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 scalar_t__ smp_confirm (struct smp_chan*) ; 
 int /*<<< orphan*/  smp_distribute_keys (struct smp_chan*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tk_request (struct l2cap_conn*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 smp_cmd_pairing_rsp(struct l2cap_conn *conn, struct sk_buff *skb)
{
	struct smp_cmd_pairing *req, *rsp = (void *) skb->data;
	struct l2cap_chan *chan = conn->smp;
	struct smp_chan *smp = chan->data;
	struct hci_dev *hdev = conn->hcon->hdev;
	u8 key_size, auth;
	int ret;

	BT_DBG("conn %p", conn);

	if (skb->len < sizeof(*rsp))
		return SMP_INVALID_PARAMS;

	if (conn->hcon->role != HCI_ROLE_MASTER)
		return SMP_CMD_NOTSUPP;

	skb_pull(skb, sizeof(*rsp));

	req = (void *) &smp->preq[1];

	key_size = min(req->max_key_size, rsp->max_key_size);
	if (check_enc_key_size(conn, key_size))
		return SMP_ENC_KEY_SIZE;

	auth = rsp->auth_req & AUTH_REQ_MASK(hdev);

	if (hci_dev_test_flag(hdev, HCI_SC_ONLY) && !(auth & SMP_AUTH_SC))
		return SMP_AUTH_REQUIREMENTS;

	/* If the remote side's OOB flag is set it means it has
	 * successfully received our local OOB data - therefore set the
	 * flag to indicate that local OOB is in use.
	 */
	if (rsp->oob_flag == SMP_OOB_PRESENT && SMP_DEV(hdev)->local_oob)
		set_bit(SMP_FLAG_LOCAL_OOB, &smp->flags);

	smp->prsp[0] = SMP_CMD_PAIRING_RSP;
	memcpy(&smp->prsp[1], rsp, sizeof(*rsp));

	/* Update remote key distribution in case the remote cleared
	 * some bits that we had enabled in our request.
	 */
	smp->remote_key_dist &= rsp->resp_key_dist;

	if ((req->auth_req & SMP_AUTH_CT2) && (auth & SMP_AUTH_CT2))
		set_bit(SMP_FLAG_CT2, &smp->flags);

	/* For BR/EDR this means we're done and can start phase 3 */
	if (conn->hcon->type == ACL_LINK) {
		/* Clear bits which are generated but not distributed */
		smp->remote_key_dist &= ~SMP_SC_NO_DIST;
		smp_distribute_keys(smp);
		return 0;
	}

	if ((req->auth_req & SMP_AUTH_SC) && (auth & SMP_AUTH_SC))
		set_bit(SMP_FLAG_SC, &smp->flags);
	else if (conn->hcon->pending_sec_level > BT_SECURITY_HIGH)
		conn->hcon->pending_sec_level = BT_SECURITY_HIGH;

	/* If we need MITM check that it can be achieved */
	if (conn->hcon->pending_sec_level >= BT_SECURITY_HIGH) {
		u8 method;

		method = get_auth_method(smp, req->io_capability,
					 rsp->io_capability);
		if (method == JUST_WORKS || method == JUST_CFM)
			return SMP_AUTH_REQUIREMENTS;
	}

	get_random_bytes(smp->prnd, sizeof(smp->prnd));

	/* Update remote key distribution in case the remote cleared
	 * some bits that we had enabled in our request.
	 */
	smp->remote_key_dist &= rsp->resp_key_dist;

	if (test_bit(SMP_FLAG_SC, &smp->flags)) {
		/* Clear bits which are generated but not distributed */
		smp->remote_key_dist &= ~SMP_SC_NO_DIST;
		SMP_ALLOW_CMD(smp, SMP_CMD_PUBLIC_KEY);
		return sc_send_public_key(smp);
	}

	auth |= req->auth_req;

	ret = tk_request(conn, 0, auth, req->io_capability, rsp->io_capability);
	if (ret)
		return SMP_UNSPECIFIED;

	set_bit(SMP_FLAG_CFM_PENDING, &smp->flags);

	/* Can't compose response until we have been confirmed */
	if (test_bit(SMP_FLAG_TK_VALID, &smp->flags))
		return smp_confirm(smp);

	return 0;
}