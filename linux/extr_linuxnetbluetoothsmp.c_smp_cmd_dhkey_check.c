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
struct smp_cmd_dhkey_check {int /*<<< orphan*/  e; } ;
struct smp_chan {scalar_t__ method; int /*<<< orphan*/  enc_key_size; int /*<<< orphan*/  tk; int /*<<< orphan*/  flags; int /*<<< orphan*/  prnd; int /*<<< orphan*/  rrnd; int /*<<< orphan*/  mackey; int /*<<< orphan*/  tfm_cmac; int /*<<< orphan*/ * lr; int /*<<< orphan*/ * preq; int /*<<< orphan*/ * prsp; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct l2cap_conn {struct hci_conn* hcon; struct l2cap_chan* smp; } ;
struct l2cap_chan {struct smp_chan* data; } ;
struct hci_conn {int /*<<< orphan*/  enc_key_size; scalar_t__ out; int /*<<< orphan*/  passkey_notify; int /*<<< orphan*/  resp_addr_type; int /*<<< orphan*/  init_addr_type; int /*<<< orphan*/  resp_addr; int /*<<< orphan*/  init_addr; } ;
typedef  int /*<<< orphan*/  r ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_conn*) ; 
 scalar_t__ DSP_PASSKEY ; 
 scalar_t__ REQ_OOB ; 
 scalar_t__ REQ_PASSKEY ; 
 int SMP_DHKEY_CHECK_FAILED ; 
 int /*<<< orphan*/  SMP_FLAG_DHKEY_PENDING ; 
 int /*<<< orphan*/  SMP_FLAG_WAIT_USER ; 
 int SMP_INVALID_PARAMS ; 
 int SMP_UNSPECIFIED ; 
 scalar_t__ crypto_memneq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hci_le_start_enc (struct hci_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sc_add_ltk (struct smp_chan*) ; 
 int /*<<< orphan*/  sc_dhkey_check (struct smp_chan*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int smp_f6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smp_cmd_dhkey_check(struct l2cap_conn *conn, struct sk_buff *skb)
{
	struct smp_cmd_dhkey_check *check = (void *) skb->data;
	struct l2cap_chan *chan = conn->smp;
	struct hci_conn *hcon = conn->hcon;
	struct smp_chan *smp = chan->data;
	u8 a[7], b[7], *local_addr, *remote_addr;
	u8 io_cap[3], r[16], e[16];
	int err;

	BT_DBG("conn %p", conn);

	if (skb->len < sizeof(*check))
		return SMP_INVALID_PARAMS;

	memcpy(a, &hcon->init_addr, 6);
	memcpy(b, &hcon->resp_addr, 6);
	a[6] = hcon->init_addr_type;
	b[6] = hcon->resp_addr_type;

	if (hcon->out) {
		local_addr = a;
		remote_addr = b;
		memcpy(io_cap, &smp->prsp[1], 3);
	} else {
		local_addr = b;
		remote_addr = a;
		memcpy(io_cap, &smp->preq[1], 3);
	}

	memset(r, 0, sizeof(r));

	if (smp->method == REQ_PASSKEY || smp->method == DSP_PASSKEY)
		put_unaligned_le32(hcon->passkey_notify, r);
	else if (smp->method == REQ_OOB)
		memcpy(r, smp->lr, 16);

	err = smp_f6(smp->tfm_cmac, smp->mackey, smp->rrnd, smp->prnd, r,
		     io_cap, remote_addr, local_addr, e);
	if (err)
		return SMP_UNSPECIFIED;

	if (crypto_memneq(check->e, e, 16))
		return SMP_DHKEY_CHECK_FAILED;

	if (!hcon->out) {
		if (test_bit(SMP_FLAG_WAIT_USER, &smp->flags)) {
			set_bit(SMP_FLAG_DHKEY_PENDING, &smp->flags);
			return 0;
		}

		/* Slave sends DHKey check as response to master */
		sc_dhkey_check(smp);
	}

	sc_add_ltk(smp);

	if (hcon->out) {
		hci_le_start_enc(hcon, 0, 0, smp->tk, smp->enc_key_size);
		hcon->enc_key_size = smp->enc_key_size;
	}

	return 0;
}