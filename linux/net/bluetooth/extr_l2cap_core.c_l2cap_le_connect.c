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
struct l2cap_le_conn_req {void* credits; void* mps; void* mtu; void* scid; int /*<<< orphan*/  psm; } ;
struct l2cap_conn {int dummy; } ;
struct l2cap_chan {int /*<<< orphan*/  ident; int /*<<< orphan*/  rx_credits; int /*<<< orphan*/  mps; int /*<<< orphan*/  imtu; int /*<<< orphan*/  scid; int /*<<< orphan*/  psm; int /*<<< orphan*/  flags; struct l2cap_conn* conn; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_LE_CONN_REQ_SENT ; 
 int /*<<< orphan*/  L2CAP_LE_CONN_REQ ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_get_ident (struct l2cap_conn*) ; 
 int /*<<< orphan*/  l2cap_le_flowctl_init (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_le_conn_req*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2cap_le_connect(struct l2cap_chan *chan)
{
	struct l2cap_conn *conn = chan->conn;
	struct l2cap_le_conn_req req;

	if (test_and_set_bit(FLAG_LE_CONN_REQ_SENT, &chan->flags))
		return;

	l2cap_le_flowctl_init(chan, 0);

	req.psm     = chan->psm;
	req.scid    = cpu_to_le16(chan->scid);
	req.mtu     = cpu_to_le16(chan->imtu);
	req.mps     = cpu_to_le16(chan->mps);
	req.credits = cpu_to_le16(chan->rx_credits);

	chan->ident = l2cap_get_ident(conn);

	l2cap_send_cmd(conn, chan->ident, L2CAP_LE_CONN_REQ,
		       sizeof(req), &req);
}