#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct socket {int /*<<< orphan*/  sk; } ;
struct l2cap_conn {int dummy; } ;
struct l2cap_chan {int /*<<< orphan*/  dst; scalar_t__ conn; } ;
struct hidp_session {int /*<<< orphan*/  user; } ;
struct hidp_connadd_req {int flags; } ;
struct TYPE_2__ {struct l2cap_chan* chan; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EBADFD ; 
 int EINVAL ; 
 int /*<<< orphan*/  HIDP_BOOT_PROTOCOL_MODE ; 
 int /*<<< orphan*/  HIDP_VIRTUAL_CABLE_UNPLUG ; 
 int hidp_session_new (struct hidp_session**,int /*<<< orphan*/ *,struct socket*,struct socket*,struct hidp_connadd_req const*,struct l2cap_conn*) ; 
 int /*<<< orphan*/  hidp_session_put (struct hidp_session*) ; 
 int hidp_verify_sockets (struct socket*,struct socket*) ; 
 int /*<<< orphan*/  l2cap_chan_lock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_unlock (struct l2cap_chan*) ; 
 struct l2cap_conn* l2cap_conn_get (scalar_t__) ; 
 int /*<<< orphan*/  l2cap_conn_put (struct l2cap_conn*) ; 
 TYPE_1__* l2cap_pi (int /*<<< orphan*/ ) ; 
 int l2cap_register_user (struct l2cap_conn*,int /*<<< orphan*/ *) ; 

int hidp_connection_add(const struct hidp_connadd_req *req,
			struct socket *ctrl_sock,
			struct socket *intr_sock)
{
	u32 valid_flags = BIT(HIDP_VIRTUAL_CABLE_UNPLUG) |
			  BIT(HIDP_BOOT_PROTOCOL_MODE);
	struct hidp_session *session;
	struct l2cap_conn *conn;
	struct l2cap_chan *chan;
	int ret;

	ret = hidp_verify_sockets(ctrl_sock, intr_sock);
	if (ret)
		return ret;

	if (req->flags & ~valid_flags)
		return -EINVAL;

	chan = l2cap_pi(ctrl_sock->sk)->chan;
	conn = NULL;
	l2cap_chan_lock(chan);
	if (chan->conn)
		conn = l2cap_conn_get(chan->conn);
	l2cap_chan_unlock(chan);

	if (!conn)
		return -EBADFD;

	ret = hidp_session_new(&session, &chan->dst, ctrl_sock,
			       intr_sock, req, conn);
	if (ret)
		goto out_conn;

	ret = l2cap_register_user(conn, &session->user);
	if (ret)
		goto out_session;

	ret = 0;

out_session:
	hidp_session_put(session);
out_conn:
	l2cap_conn_put(conn);
	return ret;
}