#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {int /*<<< orphan*/  sk; } ;
struct l2cap_chan {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct hidp_session {int dummy; } ;
struct TYPE_3__ {scalar_t__ sk_state; } ;
struct bt_sock {TYPE_1__ sk; } ;
struct TYPE_4__ {struct l2cap_chan* chan; } ;

/* Variables and functions */
 scalar_t__ BT_CONNECTED ; 
 int EBADFD ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOTUNIQ ; 
 scalar_t__ bacmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct bt_sock* bt_sk (int /*<<< orphan*/ ) ; 
 struct hidp_session* hidp_session_find (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hidp_session_put (struct hidp_session*) ; 
 int /*<<< orphan*/  l2cap_is_socket (struct socket*) ; 
 TYPE_2__* l2cap_pi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hidp_verify_sockets(struct socket *ctrl_sock,
			       struct socket *intr_sock)
{
	struct l2cap_chan *ctrl_chan, *intr_chan;
	struct bt_sock *ctrl, *intr;
	struct hidp_session *session;

	if (!l2cap_is_socket(ctrl_sock) || !l2cap_is_socket(intr_sock))
		return -EINVAL;

	ctrl_chan = l2cap_pi(ctrl_sock->sk)->chan;
	intr_chan = l2cap_pi(intr_sock->sk)->chan;

	if (bacmp(&ctrl_chan->src, &intr_chan->src) ||
	    bacmp(&ctrl_chan->dst, &intr_chan->dst))
		return -ENOTUNIQ;

	ctrl = bt_sk(ctrl_sock->sk);
	intr = bt_sk(intr_sock->sk);

	if (ctrl->sk.sk_state != BT_CONNECTED ||
	    intr->sk.sk_state != BT_CONNECTED)
		return -EBADFD;

	/* early session check, we check again during session registration */
	session = hidp_session_find(&ctrl_chan->dst);
	if (session) {
		hidp_session_put(session);
		return -EEXIST;
	}

	return 0;
}