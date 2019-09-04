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
struct l2cap_cmd_rej_cid {void* dcid; void* scid; int /*<<< orphan*/  reason; } ;
typedef  int /*<<< orphan*/  rej ;

/* Variables and functions */
 int /*<<< orphan*/  L2CAP_COMMAND_REJ ; 
 int /*<<< orphan*/  L2CAP_REJ_INVALID_CID ; 
 void* __cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_cmd_rej_cid*) ; 

__attribute__((used)) static void cmd_reject_invalid_cid(struct l2cap_conn *conn, u8 ident,
				   u16 scid, u16 dcid)
{
	struct l2cap_cmd_rej_cid rej;

	rej.reason = cpu_to_le16(L2CAP_REJ_INVALID_CID);
	rej.scid = __cpu_to_le16(scid);
	rej.dcid = __cpu_to_le16(dcid);

	l2cap_send_cmd(conn, ident, L2CAP_COMMAND_REJ, sizeof(rej), &rej);
}