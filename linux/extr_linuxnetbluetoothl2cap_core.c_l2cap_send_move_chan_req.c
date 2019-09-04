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
typedef  void* u8 ;
struct l2cap_move_chan_req {void* dest_amp_id; int /*<<< orphan*/  icid; } ;
struct l2cap_chan {int /*<<< orphan*/  conn; int /*<<< orphan*/  scid; void* ident; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,void*) ; 
 int /*<<< orphan*/  L2CAP_MOVE_CHAN_REQ ; 
 int /*<<< orphan*/  L2CAP_MOVE_TIMEOUT ; 
 int /*<<< orphan*/  __set_chan_timer (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* l2cap_get_ident (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_send_cmd (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int,struct l2cap_move_chan_req*) ; 

__attribute__((used)) static void l2cap_send_move_chan_req(struct l2cap_chan *chan, u8 dest_amp_id)
{
	struct l2cap_move_chan_req req;
	u8 ident;

	BT_DBG("chan %p, dest_amp_id %d", chan, dest_amp_id);

	ident = l2cap_get_ident(chan->conn);
	chan->ident = ident;

	req.icid = cpu_to_le16(chan->scid);
	req.dest_amp_id = dest_amp_id;

	l2cap_send_cmd(chan->conn, ident, L2CAP_MOVE_CHAN_REQ, sizeof(req),
		       &req);

	__set_chan_timer(chan, L2CAP_MOVE_TIMEOUT);
}