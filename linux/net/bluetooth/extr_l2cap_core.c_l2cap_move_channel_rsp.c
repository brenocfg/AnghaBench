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
typedef  int u16 ;
struct l2cap_move_chan_rsp {int /*<<< orphan*/  result; int /*<<< orphan*/  icid; } ;
struct l2cap_conn {int dummy; } ;
struct l2cap_cmd_hdr {int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int,int) ; 
 int EPROTO ; 
 int L2CAP_MR_PEND ; 
 int L2CAP_MR_SUCCESS ; 
 int /*<<< orphan*/  l2cap_move_continue (struct l2cap_conn*,int,int) ; 
 int /*<<< orphan*/  l2cap_move_fail (struct l2cap_conn*,int /*<<< orphan*/ ,int,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l2cap_move_channel_rsp(struct l2cap_conn *conn,
				  struct l2cap_cmd_hdr *cmd,
				  u16 cmd_len, void *data)
{
	struct l2cap_move_chan_rsp *rsp = data;
	u16 icid, result;

	if (cmd_len != sizeof(*rsp))
		return -EPROTO;

	icid = le16_to_cpu(rsp->icid);
	result = le16_to_cpu(rsp->result);

	BT_DBG("icid 0x%4.4x, result 0x%4.4x", icid, result);

	if (result == L2CAP_MR_SUCCESS || result == L2CAP_MR_PEND)
		l2cap_move_continue(conn, icid, result);
	else
		l2cap_move_fail(conn, cmd->ident, icid, result);

	return 0;
}