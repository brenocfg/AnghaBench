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
struct l2cap_conn_param_update_rsp {void* result; } ;
struct l2cap_conn_param_update_req {int /*<<< orphan*/  to_multiplier; int /*<<< orphan*/  latency; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct l2cap_conn {struct hci_conn* hcon; } ;
struct l2cap_cmd_hdr {int /*<<< orphan*/  ident; } ;
struct hci_conn {scalar_t__ role; int /*<<< orphan*/  dst_type; int /*<<< orphan*/  dst; int /*<<< orphan*/  hdev; } ;
typedef  int /*<<< orphan*/  rsp ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int,int,int,int) ; 
 int EINVAL ; 
 int EPROTO ; 
 scalar_t__ HCI_ROLE_MASTER ; 
 int /*<<< orphan*/  L2CAP_CONN_PARAM_ACCEPTED ; 
 int /*<<< orphan*/  L2CAP_CONN_PARAM_REJECTED ; 
 int /*<<< orphan*/  L2CAP_CONN_PARAM_UPDATE_RSP ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int hci_check_conn_params (int,int,int,int) ; 
 int /*<<< orphan*/  hci_le_conn_update (struct hci_conn*,int,int,int,int) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_conn_param_update_rsp*) ; 
 int /*<<< orphan*/  memset (struct l2cap_conn_param_update_rsp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mgmt_new_conn_param (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static inline int l2cap_conn_param_update_req(struct l2cap_conn *conn,
					      struct l2cap_cmd_hdr *cmd,
					      u16 cmd_len, u8 *data)
{
	struct hci_conn *hcon = conn->hcon;
	struct l2cap_conn_param_update_req *req;
	struct l2cap_conn_param_update_rsp rsp;
	u16 min, max, latency, to_multiplier;
	int err;

	if (hcon->role != HCI_ROLE_MASTER)
		return -EINVAL;

	if (cmd_len != sizeof(struct l2cap_conn_param_update_req))
		return -EPROTO;

	req = (struct l2cap_conn_param_update_req *) data;
	min		= __le16_to_cpu(req->min);
	max		= __le16_to_cpu(req->max);
	latency		= __le16_to_cpu(req->latency);
	to_multiplier	= __le16_to_cpu(req->to_multiplier);

	BT_DBG("min 0x%4.4x max 0x%4.4x latency: 0x%4.4x Timeout: 0x%4.4x",
	       min, max, latency, to_multiplier);

	memset(&rsp, 0, sizeof(rsp));

	err = hci_check_conn_params(min, max, latency, to_multiplier);
	if (err)
		rsp.result = cpu_to_le16(L2CAP_CONN_PARAM_REJECTED);
	else
		rsp.result = cpu_to_le16(L2CAP_CONN_PARAM_ACCEPTED);

	l2cap_send_cmd(conn, cmd->ident, L2CAP_CONN_PARAM_UPDATE_RSP,
		       sizeof(rsp), &rsp);

	if (!err) {
		u8 store_hint;

		store_hint = hci_le_conn_update(hcon, min, max, latency,
						to_multiplier);
		mgmt_new_conn_param(hcon->hdev, &hcon->dst, hcon->dst_type,
				    store_hint, min, max, latency,
				    to_multiplier);

	}

	return 0;
}