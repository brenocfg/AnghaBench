#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_3__* sk; } ;
struct rfcomm_session {scalar_t__ mtu; struct socket* sock; } ;
struct TYPE_9__ {int /*<<< orphan*/  accept_q; } ;
struct TYPE_8__ {int /*<<< orphan*/  sk_state_change; int /*<<< orphan*/  sk_data_ready; } ;
struct TYPE_7__ {TYPE_1__* chan; } ;
struct TYPE_6__ {int /*<<< orphan*/  imtu; int /*<<< orphan*/  omtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_session*) ; 
 int /*<<< orphan*/  BT_OPEN ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 TYPE_4__* bt_sk (TYPE_3__*) ; 
 int kernel_accept (struct socket*,struct socket**,int /*<<< orphan*/ ) ; 
 TYPE_2__* l2cap_pi (TYPE_3__*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_l2data_ready ; 
 int /*<<< orphan*/  rfcomm_l2state_change ; 
 int /*<<< orphan*/  rfcomm_schedule () ; 
 struct rfcomm_session* rfcomm_session_add (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 

__attribute__((used)) static void rfcomm_accept_connection(struct rfcomm_session *s)
{
	struct socket *sock = s->sock, *nsock;
	int err;

	/* Fast check for a new connection.
	 * Avoids unnesesary socket allocations. */
	if (list_empty(&bt_sk(sock->sk)->accept_q))
		return;

	BT_DBG("session %p", s);

	err = kernel_accept(sock, &nsock, O_NONBLOCK);
	if (err < 0)
		return;

	/* Set our callbacks */
	nsock->sk->sk_data_ready   = rfcomm_l2data_ready;
	nsock->sk->sk_state_change = rfcomm_l2state_change;

	s = rfcomm_session_add(nsock, BT_OPEN);
	if (s) {
		/* We should adjust MTU on incoming sessions.
		 * L2CAP MTU minus UIH header and FCS. */
		s->mtu = min(l2cap_pi(nsock->sk)->chan->omtu,
				l2cap_pi(nsock->sk)->chan->imtu) - 5;

		rfcomm_schedule();
	} else
		sock_release(nsock);
}