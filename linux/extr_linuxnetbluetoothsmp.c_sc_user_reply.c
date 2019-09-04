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
typedef  int u16 ;
struct smp_chan {int /*<<< orphan*/  flags; int /*<<< orphan*/  passkey_round; struct l2cap_conn* conn; } ;
struct l2cap_conn {struct hci_conn* hcon; } ;
struct hci_conn {scalar_t__ out; int /*<<< orphan*/  passkey_notify; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EIO ; 
#define  MGMT_OP_USER_CONFIRM_NEG_REPLY 130 
#define  MGMT_OP_USER_PASSKEY_NEG_REPLY 129 
#define  MGMT_OP_USER_PASSKEY_REPLY 128 
 int /*<<< orphan*/  SMP_ALLOW_CMD (struct smp_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMP_CMD_DHKEY_CHECK ; 
 int /*<<< orphan*/  SMP_CMD_PAIRING_CONFIRM ; 
 int /*<<< orphan*/  SMP_FLAG_CFM_PENDING ; 
 int /*<<< orphan*/  SMP_FLAG_DHKEY_PENDING ; 
 int /*<<< orphan*/  SMP_FLAG_WAIT_USER ; 
 int /*<<< orphan*/  SMP_NUMERIC_COMP_FAILED ; 
 int /*<<< orphan*/  SMP_PASSKEY_ENTRY_FAILED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_add_ltk (struct smp_chan*) ; 
 int /*<<< orphan*/  sc_dhkey_check (struct smp_chan*) ; 
 int /*<<< orphan*/  sc_passkey_round (struct smp_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_failure (struct l2cap_conn*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sc_user_reply(struct smp_chan *smp, u16 mgmt_op, __le32 passkey)
{
	struct l2cap_conn *conn = smp->conn;
	struct hci_conn *hcon = conn->hcon;
	u8 smp_op;

	clear_bit(SMP_FLAG_WAIT_USER, &smp->flags);

	switch (mgmt_op) {
	case MGMT_OP_USER_PASSKEY_NEG_REPLY:
		smp_failure(smp->conn, SMP_PASSKEY_ENTRY_FAILED);
		return 0;
	case MGMT_OP_USER_CONFIRM_NEG_REPLY:
		smp_failure(smp->conn, SMP_NUMERIC_COMP_FAILED);
		return 0;
	case MGMT_OP_USER_PASSKEY_REPLY:
		hcon->passkey_notify = le32_to_cpu(passkey);
		smp->passkey_round = 0;

		if (test_and_clear_bit(SMP_FLAG_CFM_PENDING, &smp->flags))
			smp_op = SMP_CMD_PAIRING_CONFIRM;
		else
			smp_op = 0;

		if (sc_passkey_round(smp, smp_op))
			return -EIO;

		return 0;
	}

	/* Initiator sends DHKey check first */
	if (hcon->out) {
		sc_dhkey_check(smp);
		SMP_ALLOW_CMD(smp, SMP_CMD_DHKEY_CHECK);
	} else if (test_and_clear_bit(SMP_FLAG_DHKEY_PENDING, &smp->flags)) {
		sc_dhkey_check(smp);
		sc_add_ltk(smp);
	}

	return 0;
}