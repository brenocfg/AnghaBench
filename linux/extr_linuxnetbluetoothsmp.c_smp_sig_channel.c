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
struct smp_chan {int /*<<< orphan*/  allow_cmd; } ;
struct sk_buff {int len; int* data; } ;
struct l2cap_conn {struct hci_conn* hcon; } ;
struct l2cap_chan {struct smp_chan* data; struct l2cap_conn* conn; } ;
struct hci_conn {int /*<<< orphan*/  dst; int /*<<< orphan*/  hdev; } ;
typedef  int /*<<< orphan*/  code ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int) ; 
 int EILSEQ ; 
 int EPERM ; 
 int /*<<< orphan*/  HCI_LE_ENABLED ; 
#define  SMP_CMD_DHKEY_CHECK 141 
#define  SMP_CMD_ENCRYPT_INFO 140 
#define  SMP_CMD_IDENT_ADDR_INFO 139 
#define  SMP_CMD_IDENT_INFO 138 
#define  SMP_CMD_KEYPRESS_NOTIFY 137 
#define  SMP_CMD_MASTER_IDENT 136 
 int SMP_CMD_MAX ; 
 int SMP_CMD_NOTSUPP ; 
#define  SMP_CMD_PAIRING_CONFIRM 135 
#define  SMP_CMD_PAIRING_FAIL 134 
#define  SMP_CMD_PAIRING_RANDOM 133 
#define  SMP_CMD_PAIRING_REQ 132 
#define  SMP_CMD_PAIRING_RSP 131 
#define  SMP_CMD_PUBLIC_KEY 130 
#define  SMP_CMD_SECURITY_REQ 129 
#define  SMP_CMD_SIGN_INFO 128 
 int SMP_PAIRING_NOTSUPP ; 
 int /*<<< orphan*/  bt_dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_test_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int smp_cmd_dhkey_check (struct l2cap_conn*,struct sk_buff*) ; 
 int smp_cmd_encrypt_info (struct l2cap_conn*,struct sk_buff*) ; 
 int smp_cmd_ident_addr_info (struct l2cap_conn*,struct sk_buff*) ; 
 int smp_cmd_ident_info (struct l2cap_conn*,struct sk_buff*) ; 
 int smp_cmd_keypress_notify (struct l2cap_conn*,struct sk_buff*) ; 
 int smp_cmd_master_ident (struct l2cap_conn*,struct sk_buff*) ; 
 int smp_cmd_pairing_confirm (struct l2cap_conn*,struct sk_buff*) ; 
 int smp_cmd_pairing_random (struct l2cap_conn*,struct sk_buff*) ; 
 int smp_cmd_pairing_req (struct l2cap_conn*,struct sk_buff*) ; 
 int smp_cmd_pairing_rsp (struct l2cap_conn*,struct sk_buff*) ; 
 int smp_cmd_public_key (struct l2cap_conn*,struct sk_buff*) ; 
 int smp_cmd_security_req (struct l2cap_conn*,struct sk_buff*) ; 
 int smp_cmd_sign_info (struct l2cap_conn*,struct sk_buff*) ; 
 int /*<<< orphan*/  smp_failure (struct l2cap_conn*,int) ; 
 int /*<<< orphan*/  test_and_clear_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smp_sig_channel(struct l2cap_chan *chan, struct sk_buff *skb)
{
	struct l2cap_conn *conn = chan->conn;
	struct hci_conn *hcon = conn->hcon;
	struct smp_chan *smp;
	__u8 code, reason;
	int err = 0;

	if (skb->len < 1)
		return -EILSEQ;

	if (!hci_dev_test_flag(hcon->hdev, HCI_LE_ENABLED)) {
		reason = SMP_PAIRING_NOTSUPP;
		goto done;
	}

	code = skb->data[0];
	skb_pull(skb, sizeof(code));

	smp = chan->data;

	if (code > SMP_CMD_MAX)
		goto drop;

	if (smp && !test_and_clear_bit(code, &smp->allow_cmd))
		goto drop;

	/* If we don't have a context the only allowed commands are
	 * pairing request and security request.
	 */
	if (!smp && code != SMP_CMD_PAIRING_REQ && code != SMP_CMD_SECURITY_REQ)
		goto drop;

	switch (code) {
	case SMP_CMD_PAIRING_REQ:
		reason = smp_cmd_pairing_req(conn, skb);
		break;

	case SMP_CMD_PAIRING_FAIL:
		smp_failure(conn, 0);
		err = -EPERM;
		break;

	case SMP_CMD_PAIRING_RSP:
		reason = smp_cmd_pairing_rsp(conn, skb);
		break;

	case SMP_CMD_SECURITY_REQ:
		reason = smp_cmd_security_req(conn, skb);
		break;

	case SMP_CMD_PAIRING_CONFIRM:
		reason = smp_cmd_pairing_confirm(conn, skb);
		break;

	case SMP_CMD_PAIRING_RANDOM:
		reason = smp_cmd_pairing_random(conn, skb);
		break;

	case SMP_CMD_ENCRYPT_INFO:
		reason = smp_cmd_encrypt_info(conn, skb);
		break;

	case SMP_CMD_MASTER_IDENT:
		reason = smp_cmd_master_ident(conn, skb);
		break;

	case SMP_CMD_IDENT_INFO:
		reason = smp_cmd_ident_info(conn, skb);
		break;

	case SMP_CMD_IDENT_ADDR_INFO:
		reason = smp_cmd_ident_addr_info(conn, skb);
		break;

	case SMP_CMD_SIGN_INFO:
		reason = smp_cmd_sign_info(conn, skb);
		break;

	case SMP_CMD_PUBLIC_KEY:
		reason = smp_cmd_public_key(conn, skb);
		break;

	case SMP_CMD_DHKEY_CHECK:
		reason = smp_cmd_dhkey_check(conn, skb);
		break;

	case SMP_CMD_KEYPRESS_NOTIFY:
		reason = smp_cmd_keypress_notify(conn, skb);
		break;

	default:
		BT_DBG("Unknown command code 0x%2.2x", code);
		reason = SMP_CMD_NOTSUPP;
		goto done;
	}

done:
	if (!err) {
		if (reason)
			smp_failure(conn, reason);
		kfree_skb(skb);
	}

	return err;

drop:
	bt_dev_err(hcon->hdev, "unexpected SMP command 0x%02x from %pMR",
		   code, &hcon->dst);
	kfree_skb(skb);
	return 0;
}