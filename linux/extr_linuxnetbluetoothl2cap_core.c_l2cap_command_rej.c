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
struct l2cap_conn {int info_state; scalar_t__ info_ident; int /*<<< orphan*/  info_timer; } ;
struct l2cap_cmd_rej_unk {scalar_t__ reason; } ;
struct l2cap_cmd_hdr {scalar_t__ ident; } ;

/* Variables and functions */
 int EPROTO ; 
 int L2CAP_INFO_FEAT_MASK_REQ_DONE ; 
 int L2CAP_INFO_FEAT_MASK_REQ_SENT ; 
 scalar_t__ L2CAP_REJ_NOT_UNDERSTOOD ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_conn_start (struct l2cap_conn*) ; 

__attribute__((used)) static inline int l2cap_command_rej(struct l2cap_conn *conn,
				    struct l2cap_cmd_hdr *cmd, u16 cmd_len,
				    u8 *data)
{
	struct l2cap_cmd_rej_unk *rej = (struct l2cap_cmd_rej_unk *) data;

	if (cmd_len < sizeof(*rej))
		return -EPROTO;

	if (rej->reason != L2CAP_REJ_NOT_UNDERSTOOD)
		return 0;

	if ((conn->info_state & L2CAP_INFO_FEAT_MASK_REQ_SENT) &&
	    cmd->ident == conn->info_ident) {
		cancel_delayed_work(&conn->info_timer);

		conn->info_state |= L2CAP_INFO_FEAT_MASK_REQ_DONE;
		conn->info_ident = 0;

		l2cap_conn_start(conn);
	}

	return 0;
}