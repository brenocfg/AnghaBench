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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct l2cap_conn {struct hci_conn* hcon; } ;
struct l2cap_cmd_rej_unk {int /*<<< orphan*/  reason; } ;
struct l2cap_cmd_hdr {int /*<<< orphan*/  ident; int /*<<< orphan*/  code; int /*<<< orphan*/  len; } ;
struct hci_conn {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  rej ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
 scalar_t__ L2CAP_CMD_HDR_SIZE ; 
 int /*<<< orphan*/  L2CAP_COMMAND_REJ ; 
 int /*<<< orphan*/  L2CAP_REJ_NOT_UNDERSTOOD ; 
 scalar_t__ LE_LINK ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int l2cap_le_sig_cmd (struct l2cap_conn*,struct l2cap_cmd_hdr*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_cmd_rej_unk*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static inline void l2cap_le_sig_channel(struct l2cap_conn *conn,
					struct sk_buff *skb)
{
	struct hci_conn *hcon = conn->hcon;
	struct l2cap_cmd_hdr *cmd;
	u16 len;
	int err;

	if (hcon->type != LE_LINK)
		goto drop;

	if (skb->len < L2CAP_CMD_HDR_SIZE)
		goto drop;

	cmd = (void *) skb->data;
	skb_pull(skb, L2CAP_CMD_HDR_SIZE);

	len = le16_to_cpu(cmd->len);

	BT_DBG("code 0x%2.2x len %d id 0x%2.2x", cmd->code, len, cmd->ident);

	if (len != skb->len || !cmd->ident) {
		BT_DBG("corrupted command");
		goto drop;
	}

	err = l2cap_le_sig_cmd(conn, cmd, len, skb->data);
	if (err) {
		struct l2cap_cmd_rej_unk rej;

		BT_ERR("Wrong link type (%d)", err);

		rej.reason = cpu_to_le16(L2CAP_REJ_NOT_UNDERSTOOD);
		l2cap_send_cmd(conn, cmd->ident, L2CAP_COMMAND_REJ,
			       sizeof(rej), &rej);
	}

drop:
	kfree_skb(skb);
}