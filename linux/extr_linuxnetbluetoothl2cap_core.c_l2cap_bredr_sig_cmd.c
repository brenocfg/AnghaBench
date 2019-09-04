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
struct l2cap_cmd_hdr {int code; int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
 int EINVAL ; 
#define  L2CAP_COMMAND_REJ 144 
#define  L2CAP_CONF_REQ 143 
#define  L2CAP_CONF_RSP 142 
#define  L2CAP_CONN_REQ 141 
#define  L2CAP_CONN_RSP 140 
#define  L2CAP_CREATE_CHAN_REQ 139 
#define  L2CAP_CREATE_CHAN_RSP 138 
#define  L2CAP_DISCONN_REQ 137 
#define  L2CAP_DISCONN_RSP 136 
#define  L2CAP_ECHO_REQ 135 
#define  L2CAP_ECHO_RSP 134 
#define  L2CAP_INFO_REQ 133 
#define  L2CAP_INFO_RSP 132 
#define  L2CAP_MOVE_CHAN_CFM 131 
#define  L2CAP_MOVE_CHAN_CFM_RSP 130 
#define  L2CAP_MOVE_CHAN_REQ 129 
#define  L2CAP_MOVE_CHAN_RSP 128 
 int /*<<< orphan*/  l2cap_command_rej (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int l2cap_config_req (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_config_rsp (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_connect_create_rsp (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int l2cap_connect_req (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int l2cap_create_channel_req (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int l2cap_disconnect_req (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_disconnect_rsp (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int l2cap_information_req (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_information_rsp (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int l2cap_move_channel_confirm (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_move_channel_confirm_rsp (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int l2cap_move_channel_req (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_move_channel_rsp (struct l2cap_conn*,struct l2cap_cmd_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int l2cap_bredr_sig_cmd(struct l2cap_conn *conn,
				      struct l2cap_cmd_hdr *cmd, u16 cmd_len,
				      u8 *data)
{
	int err = 0;

	switch (cmd->code) {
	case L2CAP_COMMAND_REJ:
		l2cap_command_rej(conn, cmd, cmd_len, data);
		break;

	case L2CAP_CONN_REQ:
		err = l2cap_connect_req(conn, cmd, cmd_len, data);
		break;

	case L2CAP_CONN_RSP:
	case L2CAP_CREATE_CHAN_RSP:
		l2cap_connect_create_rsp(conn, cmd, cmd_len, data);
		break;

	case L2CAP_CONF_REQ:
		err = l2cap_config_req(conn, cmd, cmd_len, data);
		break;

	case L2CAP_CONF_RSP:
		l2cap_config_rsp(conn, cmd, cmd_len, data);
		break;

	case L2CAP_DISCONN_REQ:
		err = l2cap_disconnect_req(conn, cmd, cmd_len, data);
		break;

	case L2CAP_DISCONN_RSP:
		l2cap_disconnect_rsp(conn, cmd, cmd_len, data);
		break;

	case L2CAP_ECHO_REQ:
		l2cap_send_cmd(conn, cmd->ident, L2CAP_ECHO_RSP, cmd_len, data);
		break;

	case L2CAP_ECHO_RSP:
		break;

	case L2CAP_INFO_REQ:
		err = l2cap_information_req(conn, cmd, cmd_len, data);
		break;

	case L2CAP_INFO_RSP:
		l2cap_information_rsp(conn, cmd, cmd_len, data);
		break;

	case L2CAP_CREATE_CHAN_REQ:
		err = l2cap_create_channel_req(conn, cmd, cmd_len, data);
		break;

	case L2CAP_MOVE_CHAN_REQ:
		err = l2cap_move_channel_req(conn, cmd, cmd_len, data);
		break;

	case L2CAP_MOVE_CHAN_RSP:
		l2cap_move_channel_rsp(conn, cmd, cmd_len, data);
		break;

	case L2CAP_MOVE_CHAN_CFM:
		err = l2cap_move_channel_confirm(conn, cmd, cmd_len, data);
		break;

	case L2CAP_MOVE_CHAN_CFM_RSP:
		l2cap_move_channel_confirm_rsp(conn, cmd, cmd_len, data);
		break;

	default:
		BT_ERR("Unknown BR/EDR signaling command 0x%2.2x", cmd->code);
		err = -EINVAL;
		break;
	}

	return err;
}