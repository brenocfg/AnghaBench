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
struct l2cap_conn_req {int /*<<< orphan*/  psm; int /*<<< orphan*/  scid; } ;
struct l2cap_conn {int dummy; } ;
struct l2cap_chan {int /*<<< orphan*/  ident; int /*<<< orphan*/  conf_state; int /*<<< orphan*/  psm; int /*<<< orphan*/  scid; struct l2cap_conn* conn; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_CONNECT_PEND ; 
 int /*<<< orphan*/  L2CAP_CONN_REQ ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_get_ident (struct l2cap_conn*) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_conn_req*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void l2cap_send_conn_req(struct l2cap_chan *chan)
{
	struct l2cap_conn *conn = chan->conn;
	struct l2cap_conn_req req;

	req.scid = cpu_to_le16(chan->scid);
	req.psm  = chan->psm;

	chan->ident = l2cap_get_ident(conn);

	set_bit(CONF_CONNECT_PEND, &chan->conf_state);

	l2cap_send_cmd(conn, chan->ident, L2CAP_CONN_REQ, sizeof(req), &req);
}