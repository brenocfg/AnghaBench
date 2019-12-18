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
struct l2cap_disconn_req {void* scid; void* dcid; } ;
struct l2cap_conn {int dummy; } ;
struct l2cap_chan {scalar_t__ mode; scalar_t__ state; scalar_t__ scid; scalar_t__ dcid; struct l2cap_conn* conn; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DISCONN ; 
 scalar_t__ L2CAP_CID_A2MP ; 
 int /*<<< orphan*/  L2CAP_DISCONN_REQ ; 
 scalar_t__ L2CAP_MODE_ERTM ; 
 int /*<<< orphan*/  __clear_ack_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  __clear_monitor_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  __clear_retrans_timer (struct l2cap_chan*) ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  l2cap_get_ident (struct l2cap_conn*) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_disconn_req*) ; 
 int /*<<< orphan*/  l2cap_state_change (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_state_change_and_error (struct l2cap_chan*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void l2cap_send_disconn_req(struct l2cap_chan *chan, int err)
{
	struct l2cap_conn *conn = chan->conn;
	struct l2cap_disconn_req req;

	if (!conn)
		return;

	if (chan->mode == L2CAP_MODE_ERTM && chan->state == BT_CONNECTED) {
		__clear_retrans_timer(chan);
		__clear_monitor_timer(chan);
		__clear_ack_timer(chan);
	}

	if (chan->scid == L2CAP_CID_A2MP) {
		l2cap_state_change(chan, BT_DISCONN);
		return;
	}

	req.dcid = cpu_to_le16(chan->dcid);
	req.scid = cpu_to_le16(chan->scid);
	l2cap_send_cmd(conn, l2cap_get_ident(conn), L2CAP_DISCONN_REQ,
		       sizeof(req), &req);

	l2cap_state_change_and_error(chan, BT_DISCONN, err);
}