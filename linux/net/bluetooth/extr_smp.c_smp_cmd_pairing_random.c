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
typedef  int /*<<< orphan*/  u32 ;
struct smp_chan {scalar_t__ method; int /*<<< orphan*/  flags; int /*<<< orphan*/  tfm_cmac; int /*<<< orphan*/  tk; int /*<<< orphan*/  mackey; int /*<<< orphan*/ * prnd; int /*<<< orphan*/  pcnf; int /*<<< orphan*/ * rrnd; int /*<<< orphan*/ * local_pk; int /*<<< orphan*/ * remote_pk; } ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct l2cap_conn {struct hci_conn* hcon; struct l2cap_chan* smp; } ;
struct l2cap_chan {struct smp_chan* data; } ;
struct hci_conn {int /*<<< orphan*/  dst_type; int /*<<< orphan*/  type; int /*<<< orphan*/  dst; int /*<<< orphan*/  hdev; scalar_t__ out; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_conn*) ; 
 scalar_t__ DSP_PASSKEY ; 
 scalar_t__ JUST_WORKS ; 
 scalar_t__ REQ_OOB ; 
 scalar_t__ REQ_PASSKEY ; 
 int /*<<< orphan*/  SMP_ALLOW_CMD (struct smp_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_CMD_DHKEY_CHECK ; 
 int /*<<< orphan*/  SMP_CMD_PAIRING_RANDOM ; 
 int /*<<< orphan*/  SMP_CONFIRM_FAILED ; 
 int /*<<< orphan*/  SMP_FLAG_SC ; 
 int /*<<< orphan*/  SMP_FLAG_WAIT_USER ; 
 int /*<<< orphan*/  SMP_INVALID_PARAMS ; 
 int /*<<< orphan*/  SMP_UNSPECIFIED ; 
 scalar_t__ crypto_memneq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mgmt_user_confirm_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_dhkey_check (struct smp_chan*) ; 
 int sc_mackey_and_ltk (struct smp_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_passkey_round (struct smp_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int smp_f4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int smp_g2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_random (struct smp_chan*) ; 
 int /*<<< orphan*/  smp_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 smp_cmd_pairing_random(struct l2cap_conn *conn, struct sk_buff *skb)
{
	struct l2cap_chan *chan = conn->smp;
	struct smp_chan *smp = chan->data;
	struct hci_conn *hcon = conn->hcon;
	u8 *pkax, *pkbx, *na, *nb;
	u32 passkey;
	int err;

	BT_DBG("conn %p", conn);

	if (skb->len < sizeof(smp->rrnd))
		return SMP_INVALID_PARAMS;

	memcpy(smp->rrnd, skb->data, sizeof(smp->rrnd));
	skb_pull(skb, sizeof(smp->rrnd));

	if (!test_bit(SMP_FLAG_SC, &smp->flags))
		return smp_random(smp);

	if (hcon->out) {
		pkax = smp->local_pk;
		pkbx = smp->remote_pk;
		na   = smp->prnd;
		nb   = smp->rrnd;
	} else {
		pkax = smp->remote_pk;
		pkbx = smp->local_pk;
		na   = smp->rrnd;
		nb   = smp->prnd;
	}

	if (smp->method == REQ_OOB) {
		if (!hcon->out)
			smp_send_cmd(conn, SMP_CMD_PAIRING_RANDOM,
				     sizeof(smp->prnd), smp->prnd);
		SMP_ALLOW_CMD(smp, SMP_CMD_DHKEY_CHECK);
		goto mackey_and_ltk;
	}

	/* Passkey entry has special treatment */
	if (smp->method == REQ_PASSKEY || smp->method == DSP_PASSKEY)
		return sc_passkey_round(smp, SMP_CMD_PAIRING_RANDOM);

	if (hcon->out) {
		u8 cfm[16];

		err = smp_f4(smp->tfm_cmac, smp->remote_pk, smp->local_pk,
			     smp->rrnd, 0, cfm);
		if (err)
			return SMP_UNSPECIFIED;

		if (crypto_memneq(smp->pcnf, cfm, 16))
			return SMP_CONFIRM_FAILED;
	} else {
		smp_send_cmd(conn, SMP_CMD_PAIRING_RANDOM, sizeof(smp->prnd),
			     smp->prnd);
		SMP_ALLOW_CMD(smp, SMP_CMD_DHKEY_CHECK);
	}

mackey_and_ltk:
	/* Generate MacKey and LTK */
	err = sc_mackey_and_ltk(smp, smp->mackey, smp->tk);
	if (err)
		return SMP_UNSPECIFIED;

	if (smp->method == JUST_WORKS || smp->method == REQ_OOB) {
		if (hcon->out) {
			sc_dhkey_check(smp);
			SMP_ALLOW_CMD(smp, SMP_CMD_DHKEY_CHECK);
		}
		return 0;
	}

	err = smp_g2(smp->tfm_cmac, pkax, pkbx, na, nb, &passkey);
	if (err)
		return SMP_UNSPECIFIED;

	err = mgmt_user_confirm_request(hcon->hdev, &hcon->dst, hcon->type,
					hcon->dst_type, passkey, 0);
	if (err)
		return SMP_UNSPECIFIED;

	set_bit(SMP_FLAG_WAIT_USER, &smp->flags);

	return 0;
}