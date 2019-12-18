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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct smp_chan {int /*<<< orphan*/  flags; int /*<<< orphan*/  tk; } ;
struct l2cap_conn {struct l2cap_chan* smp; } ;
struct l2cap_chan {struct smp_chan* data; } ;
struct hci_conn {struct l2cap_conn* l2cap_data; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
#define  MGMT_OP_USER_CONFIRM_NEG_REPLY 131 
#define  MGMT_OP_USER_CONFIRM_REPLY 130 
#define  MGMT_OP_USER_PASSKEY_NEG_REPLY 129 
#define  MGMT_OP_USER_PASSKEY_REPLY 128 
 int /*<<< orphan*/  SMP_FLAG_CFM_PENDING ; 
 int /*<<< orphan*/  SMP_FLAG_SC ; 
 int /*<<< orphan*/  SMP_FLAG_TK_VALID ; 
 scalar_t__ SMP_PASSKEY_ENTRY_FAILED ; 
 int /*<<< orphan*/  l2cap_chan_lock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_unlock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sc_user_reply (struct smp_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ smp_confirm (struct smp_chan*) ; 
 int /*<<< orphan*/  smp_failure (struct l2cap_conn*,scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int smp_user_confirm_reply(struct hci_conn *hcon, u16 mgmt_op, __le32 passkey)
{
	struct l2cap_conn *conn = hcon->l2cap_data;
	struct l2cap_chan *chan;
	struct smp_chan *smp;
	u32 value;
	int err;

	BT_DBG("");

	if (!conn)
		return -ENOTCONN;

	chan = conn->smp;
	if (!chan)
		return -ENOTCONN;

	l2cap_chan_lock(chan);
	if (!chan->data) {
		err = -ENOTCONN;
		goto unlock;
	}

	smp = chan->data;

	if (test_bit(SMP_FLAG_SC, &smp->flags)) {
		err = sc_user_reply(smp, mgmt_op, passkey);
		goto unlock;
	}

	switch (mgmt_op) {
	case MGMT_OP_USER_PASSKEY_REPLY:
		value = le32_to_cpu(passkey);
		memset(smp->tk, 0, sizeof(smp->tk));
		BT_DBG("PassKey: %d", value);
		put_unaligned_le32(value, smp->tk);
		/* Fall Through */
	case MGMT_OP_USER_CONFIRM_REPLY:
		set_bit(SMP_FLAG_TK_VALID, &smp->flags);
		break;
	case MGMT_OP_USER_PASSKEY_NEG_REPLY:
	case MGMT_OP_USER_CONFIRM_NEG_REPLY:
		smp_failure(conn, SMP_PASSKEY_ENTRY_FAILED);
		err = 0;
		goto unlock;
	default:
		smp_failure(conn, SMP_PASSKEY_ENTRY_FAILED);
		err = -EOPNOTSUPP;
		goto unlock;
	}

	err = 0;

	/* If it is our turn to send Pairing Confirm, do so now */
	if (test_bit(SMP_FLAG_CFM_PENDING, &smp->flags)) {
		u8 rsp = smp_confirm(smp);
		if (rsp)
			smp_failure(conn, rsp);
	}

unlock:
	l2cap_chan_unlock(chan);
	return err;
}