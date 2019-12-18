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
typedef  int /*<<< orphan*/  u16 ;
struct l2cap_conn {int dummy; } ;
struct l2cap_cmd_hdr {int code; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
 int EINVAL ; 
#define  L2CAP_COMMAND_REJ 135 
#define  L2CAP_CONN_PARAM_UPDATE_REQ 134 
#define  L2CAP_CONN_PARAM_UPDATE_RSP 133 
#define  L2CAP_DISCONN_REQ 132 
#define  L2CAP_DISCONN_RSP 131 
#define  L2CAP_LE_CONN_REQ 130 
#define  L2CAP_LE_CONN_RSP 129 
#define  L2CAP_LE_CREDITS 128 
 int l2cap_conn_param_update_req (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int l2cap_disconnect_req (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_disconnect_rsp (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_le_command_rej (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int l2cap_le_connect_req (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_le_connect_rsp (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int l2cap_le_credits (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int l2cap_le_sig_cmd(struct l2cap_conn *conn,
				   struct l2cap_cmd_hdr *cmd, u16 cmd_len,
				   u8 *data)
{
	int err = 0;

	switch (cmd->code) {
	case L2CAP_COMMAND_REJ:
		l2cap_le_command_rej(conn, cmd, cmd_len, data);
		break;

	case L2CAP_CONN_PARAM_UPDATE_REQ:
		err = l2cap_conn_param_update_req(conn, cmd, cmd_len, data);
		break;

	case L2CAP_CONN_PARAM_UPDATE_RSP:
		break;

	case L2CAP_LE_CONN_RSP:
		l2cap_le_connect_rsp(conn, cmd, cmd_len, data);
		break;

	case L2CAP_LE_CONN_REQ:
		err = l2cap_le_connect_req(conn, cmd, cmd_len, data);
		break;

	case L2CAP_LE_CREDITS:
		err = l2cap_le_credits(conn, cmd, cmd_len, data);
		break;

	case L2CAP_DISCONN_REQ:
		err = l2cap_disconnect_req(conn, cmd, cmd_len, data);
		break;

	case L2CAP_DISCONN_RSP:
		l2cap_disconnect_rsp(conn, cmd, cmd_len, data);
		break;

	default:
		BT_ERR("Unknown LE signaling command 0x%2.2x", cmd->code);
		err = -EINVAL;
		break;
	}

	return err;
}