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
struct smp_chan {int /*<<< orphan*/  enc_key_size; int /*<<< orphan*/  rrnd; int /*<<< orphan*/  prnd; int /*<<< orphan*/  tk; int /*<<< orphan*/  pcnf; int /*<<< orphan*/  prsp; int /*<<< orphan*/  preq; struct l2cap_conn* conn; } ;
struct l2cap_conn {struct hci_conn* hcon; } ;
struct hci_conn {scalar_t__ pending_sec_level; int /*<<< orphan*/  dst_type; int /*<<< orphan*/  dst; int /*<<< orphan*/  hdev; int /*<<< orphan*/  flags; int /*<<< orphan*/  enc_key_size; scalar_t__ out; int /*<<< orphan*/  resp_addr; int /*<<< orphan*/  resp_addr_type; int /*<<< orphan*/  init_addr; int /*<<< orphan*/  init_addr_type; } ;
typedef  int /*<<< orphan*/  __le64 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_conn*,char*) ; 
 scalar_t__ BT_SECURITY_HIGH ; 
 int /*<<< orphan*/  HCI_CONN_ENCRYPT_PEND ; 
 int /*<<< orphan*/  HCI_CONN_STK_ENCRYPT ; 
 int /*<<< orphan*/  SMP_CMD_PAIRING_RANDOM ; 
 int SMP_CONFIRM_FAILED ; 
 int /*<<< orphan*/  SMP_STK ; 
 int SMP_UNSPECIFIED ; 
 int /*<<< orphan*/  bt_dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ crypto_memneq (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  hci_add_ltk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_le_start_enc (struct hci_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int smp_c1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  smp_s1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  smp_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 smp_random(struct smp_chan *smp)
{
	struct l2cap_conn *conn = smp->conn;
	struct hci_conn *hcon = conn->hcon;
	u8 confirm[16];
	int ret;

	BT_DBG("conn %p %s", conn, conn->hcon->out ? "master" : "slave");

	ret = smp_c1(smp->tk, smp->rrnd, smp->preq, smp->prsp,
		     hcon->init_addr_type, &hcon->init_addr,
		     hcon->resp_addr_type, &hcon->resp_addr, confirm);
	if (ret)
		return SMP_UNSPECIFIED;

	if (crypto_memneq(smp->pcnf, confirm, sizeof(smp->pcnf))) {
		bt_dev_err(hcon->hdev, "pairing failed "
			   "(confirmation values mismatch)");
		return SMP_CONFIRM_FAILED;
	}

	if (hcon->out) {
		u8 stk[16];
		__le64 rand = 0;
		__le16 ediv = 0;

		smp_s1(smp->tk, smp->rrnd, smp->prnd, stk);

		if (test_and_set_bit(HCI_CONN_ENCRYPT_PEND, &hcon->flags))
			return SMP_UNSPECIFIED;

		hci_le_start_enc(hcon, ediv, rand, stk, smp->enc_key_size);
		hcon->enc_key_size = smp->enc_key_size;
		set_bit(HCI_CONN_STK_ENCRYPT, &hcon->flags);
	} else {
		u8 stk[16], auth;
		__le64 rand = 0;
		__le16 ediv = 0;

		smp_send_cmd(conn, SMP_CMD_PAIRING_RANDOM, sizeof(smp->prnd),
			     smp->prnd);

		smp_s1(smp->tk, smp->prnd, smp->rrnd, stk);

		if (hcon->pending_sec_level == BT_SECURITY_HIGH)
			auth = 1;
		else
			auth = 0;

		/* Even though there's no _SLAVE suffix this is the
		 * slave STK we're adding for later lookup (the master
		 * STK never needs to be stored).
		 */
		hci_add_ltk(hcon->hdev, &hcon->dst, hcon->dst_type,
			    SMP_STK, auth, stk, smp->enc_key_size, ediv, rand);
	}

	return 0;
}