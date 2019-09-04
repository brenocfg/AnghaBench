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
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct l2cap_conn {struct hci_conn* hcon; } ;
struct l2cap_cmd_rej_unk {int /*<<< orphan*/  reason; } ;
struct l2cap_cmd_hdr {int /*<<< orphan*/  ident; int /*<<< orphan*/  code; int /*<<< orphan*/  len; } ;
struct hci_conn {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  rej ;

/* Variables and functions */
 scalar_t__ ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
 int L2CAP_CMD_HDR_SIZE ; 
 int /*<<< orphan*/  L2CAP_COMMAND_REJ ; 
 int /*<<< orphan*/  L2CAP_REJ_NOT_UNDERSTOOD ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int l2cap_bredr_sig_cmd (struct l2cap_conn*,struct l2cap_cmd_hdr*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_raw_recv (struct l2cap_conn*,struct sk_buff*) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_cmd_rej_unk*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct l2cap_cmd_hdr*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void l2cap_sig_channel(struct l2cap_conn *conn,
				     struct sk_buff *skb)
{
	struct hci_conn *hcon = conn->hcon;
	u8 *data = skb->data;
	int len = skb->len;
	struct l2cap_cmd_hdr cmd;
	int err;

	l2cap_raw_recv(conn, skb);

	if (hcon->type != ACL_LINK)
		goto drop;

	while (len >= L2CAP_CMD_HDR_SIZE) {
		u16 cmd_len;
		memcpy(&cmd, data, L2CAP_CMD_HDR_SIZE);
		data += L2CAP_CMD_HDR_SIZE;
		len  -= L2CAP_CMD_HDR_SIZE;

		cmd_len = le16_to_cpu(cmd.len);

		BT_DBG("code 0x%2.2x len %d id 0x%2.2x", cmd.code, cmd_len,
		       cmd.ident);

		if (cmd_len > len || !cmd.ident) {
			BT_DBG("corrupted command");
			break;
		}

		err = l2cap_bredr_sig_cmd(conn, &cmd, cmd_len, data);
		if (err) {
			struct l2cap_cmd_rej_unk rej;

			BT_ERR("Wrong link type (%d)", err);

			rej.reason = cpu_to_le16(L2CAP_REJ_NOT_UNDERSTOOD);
			l2cap_send_cmd(conn, cmd.ident, L2CAP_COMMAND_REJ,
				       sizeof(rej), &rej);
		}

		data += cmd_len;
		len  -= cmd_len;
	}

drop:
	kfree_skb(skb);
}