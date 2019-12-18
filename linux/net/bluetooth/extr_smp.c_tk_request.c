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
typedef  int u32 ;
struct smp_chan {scalar_t__ method; int /*<<< orphan*/  flags; int /*<<< orphan*/  tk; } ;
struct l2cap_conn {struct l2cap_chan* smp; struct hci_conn* hcon; } ;
struct l2cap_chan {struct smp_chan* data; } ;
struct hci_conn {scalar_t__ io_capability; scalar_t__ pending_sec_level; scalar_t__ role; int /*<<< orphan*/  dst_type; int /*<<< orphan*/  type; int /*<<< orphan*/  dst; int /*<<< orphan*/  hdev; } ;
typedef  int /*<<< orphan*/  passkey ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int,...) ; 
 scalar_t__ BT_SECURITY_HIGH ; 
 scalar_t__ CFM_PASSKEY ; 
 int EINVAL ; 
 scalar_t__ HCI_IO_NO_INPUT_OUTPUT ; 
 scalar_t__ HCI_ROLE_MASTER ; 
 scalar_t__ JUST_CFM ; 
 scalar_t__ JUST_WORKS ; 
 scalar_t__ OVERLAP ; 
 scalar_t__ REQ_PASSKEY ; 
 int SMP_AUTH_MITM ; 
 int /*<<< orphan*/  SMP_FLAG_INITIATOR ; 
 int /*<<< orphan*/  SMP_FLAG_MITM_AUTH ; 
 int /*<<< orphan*/  SMP_FLAG_SC ; 
 int /*<<< orphan*/  SMP_FLAG_TK_VALID ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ get_auth_method (struct smp_chan*,int,int) ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mgmt_user_confirm_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int mgmt_user_passkey_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mgmt_user_passkey_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tk_request(struct l2cap_conn *conn, u8 remote_oob, u8 auth,
						u8 local_io, u8 remote_io)
{
	struct hci_conn *hcon = conn->hcon;
	struct l2cap_chan *chan = conn->smp;
	struct smp_chan *smp = chan->data;
	u32 passkey = 0;
	int ret = 0;

	/* Initialize key for JUST WORKS */
	memset(smp->tk, 0, sizeof(smp->tk));
	clear_bit(SMP_FLAG_TK_VALID, &smp->flags);

	BT_DBG("tk_request: auth:%d lcl:%d rem:%d", auth, local_io, remote_io);

	/* If neither side wants MITM, either "just" confirm an incoming
	 * request or use just-works for outgoing ones. The JUST_CFM
	 * will be converted to JUST_WORKS if necessary later in this
	 * function. If either side has MITM look up the method from the
	 * table.
	 */
	if (!(auth & SMP_AUTH_MITM))
		smp->method = JUST_CFM;
	else
		smp->method = get_auth_method(smp, local_io, remote_io);

	/* Don't confirm locally initiated pairing attempts */
	if (smp->method == JUST_CFM && test_bit(SMP_FLAG_INITIATOR,
						&smp->flags))
		smp->method = JUST_WORKS;

	/* Don't bother user space with no IO capabilities */
	if (smp->method == JUST_CFM &&
	    hcon->io_capability == HCI_IO_NO_INPUT_OUTPUT)
		smp->method = JUST_WORKS;

	/* If Just Works, Continue with Zero TK */
	if (smp->method == JUST_WORKS) {
		set_bit(SMP_FLAG_TK_VALID, &smp->flags);
		return 0;
	}

	/* If this function is used for SC -> legacy fallback we
	 * can only recover the just-works case.
	 */
	if (test_bit(SMP_FLAG_SC, &smp->flags))
		return -EINVAL;

	/* Not Just Works/Confirm results in MITM Authentication */
	if (smp->method != JUST_CFM) {
		set_bit(SMP_FLAG_MITM_AUTH, &smp->flags);
		if (hcon->pending_sec_level < BT_SECURITY_HIGH)
			hcon->pending_sec_level = BT_SECURITY_HIGH;
	}

	/* If both devices have Keyoard-Display I/O, the master
	 * Confirms and the slave Enters the passkey.
	 */
	if (smp->method == OVERLAP) {
		if (hcon->role == HCI_ROLE_MASTER)
			smp->method = CFM_PASSKEY;
		else
			smp->method = REQ_PASSKEY;
	}

	/* Generate random passkey. */
	if (smp->method == CFM_PASSKEY) {
		memset(smp->tk, 0, sizeof(smp->tk));
		get_random_bytes(&passkey, sizeof(passkey));
		passkey %= 1000000;
		put_unaligned_le32(passkey, smp->tk);
		BT_DBG("PassKey: %d", passkey);
		set_bit(SMP_FLAG_TK_VALID, &smp->flags);
	}

	if (smp->method == REQ_PASSKEY)
		ret = mgmt_user_passkey_request(hcon->hdev, &hcon->dst,
						hcon->type, hcon->dst_type);
	else if (smp->method == JUST_CFM)
		ret = mgmt_user_confirm_request(hcon->hdev, &hcon->dst,
						hcon->type, hcon->dst_type,
						passkey, 1);
	else
		ret = mgmt_user_passkey_notify(hcon->hdev, &hcon->dst,
						hcon->type, hcon->dst_type,
						passkey, 0);

	return ret;
}