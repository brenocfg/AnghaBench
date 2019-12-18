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
struct smp_chan {int passkey_round; int /*<<< orphan*/  prnd; int /*<<< orphan*/  flags; int /*<<< orphan*/  tk; int /*<<< orphan*/  mackey; int /*<<< orphan*/  pcnf; int /*<<< orphan*/  rrnd; int /*<<< orphan*/  local_pk; int /*<<< orphan*/  remote_pk; int /*<<< orphan*/  tfm_cmac; struct l2cap_conn* conn; } ;
struct l2cap_conn {struct hci_conn* hcon; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_conn {int passkey_notify; int /*<<< orphan*/  out; struct hci_dev* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SMP_ALLOW_CMD (struct smp_chan*,int const) ; 
 int const SMP_CMD_DHKEY_CHECK ; 
#define  SMP_CMD_PAIRING_CONFIRM 130 
#define  SMP_CMD_PAIRING_RANDOM 129 
#define  SMP_CMD_PUBLIC_KEY 128 
 int SMP_CONFIRM_FAILED ; 
 int /*<<< orphan*/  SMP_FLAG_CFM_PENDING ; 
 int /*<<< orphan*/  SMP_FLAG_WAIT_USER ; 
 int SMP_UNSPECIFIED ; 
 int /*<<< orphan*/  crypto_memneq (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  sc_dhkey_check (struct smp_chan*) ; 
 int /*<<< orphan*/  sc_mackey_and_ltk (struct smp_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sc_passkey_send_confirm (struct smp_chan*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_f4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  smp_send_cmd (struct l2cap_conn*,int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 sc_passkey_round(struct smp_chan *smp, u8 smp_op)
{
	struct l2cap_conn *conn = smp->conn;
	struct hci_conn *hcon = conn->hcon;
	struct hci_dev *hdev = hcon->hdev;
	u8 cfm[16], r;

	/* Ignore the PDU if we've already done 20 rounds (0 - 19) */
	if (smp->passkey_round >= 20)
		return 0;

	switch (smp_op) {
	case SMP_CMD_PAIRING_RANDOM:
		r = ((hcon->passkey_notify >> smp->passkey_round) & 0x01);
		r |= 0x80;

		if (smp_f4(smp->tfm_cmac, smp->remote_pk, smp->local_pk,
			   smp->rrnd, r, cfm))
			return SMP_UNSPECIFIED;

		if (crypto_memneq(smp->pcnf, cfm, 16))
			return SMP_CONFIRM_FAILED;

		smp->passkey_round++;

		if (smp->passkey_round == 20) {
			/* Generate MacKey and LTK */
			if (sc_mackey_and_ltk(smp, smp->mackey, smp->tk))
				return SMP_UNSPECIFIED;
		}

		/* The round is only complete when the initiator
		 * receives pairing random.
		 */
		if (!hcon->out) {
			smp_send_cmd(conn, SMP_CMD_PAIRING_RANDOM,
				     sizeof(smp->prnd), smp->prnd);
			if (smp->passkey_round == 20)
				SMP_ALLOW_CMD(smp, SMP_CMD_DHKEY_CHECK);
			else
				SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_CONFIRM);
			return 0;
		}

		/* Start the next round */
		if (smp->passkey_round != 20)
			return sc_passkey_round(smp, 0);

		/* Passkey rounds are complete - start DHKey Check */
		sc_dhkey_check(smp);
		SMP_ALLOW_CMD(smp, SMP_CMD_DHKEY_CHECK);

		break;

	case SMP_CMD_PAIRING_CONFIRM:
		if (test_bit(SMP_FLAG_WAIT_USER, &smp->flags)) {
			set_bit(SMP_FLAG_CFM_PENDING, &smp->flags);
			return 0;
		}

		SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_RANDOM);

		if (hcon->out) {
			smp_send_cmd(conn, SMP_CMD_PAIRING_RANDOM,
				     sizeof(smp->prnd), smp->prnd);
			return 0;
		}

		return sc_passkey_send_confirm(smp);

	case SMP_CMD_PUBLIC_KEY:
	default:
		/* Initiating device starts the round */
		if (!hcon->out)
			return 0;

		BT_DBG("%s Starting passkey round %u", hdev->name,
		       smp->passkey_round + 1);

		SMP_ALLOW_CMD(smp, SMP_CMD_PAIRING_CONFIRM);

		return sc_passkey_send_confirm(smp);
	}

	return 0;
}