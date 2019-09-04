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
struct sock {int /*<<< orphan*/  state; int /*<<< orphan*/  sk_state; } ;
struct l2cap_chan {int /*<<< orphan*/  state; int /*<<< orphan*/  sk_state; } ;
struct TYPE_2__ {struct sock* chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  __clear_chan_timer (struct sock*) ; 
 struct sock* bt_accept_dequeue (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_chan_close (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_lock (struct sock*) ; 
 int /*<<< orphan*/  l2cap_chan_unlock (struct sock*) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_sock_kill (struct sock*) ; 
 int /*<<< orphan*/  state_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_sock_cleanup_listen(struct sock *parent)
{
	struct sock *sk;

	BT_DBG("parent %p state %s", parent,
	       state_to_string(parent->sk_state));

	/* Close not yet accepted channels */
	while ((sk = bt_accept_dequeue(parent, NULL))) {
		struct l2cap_chan *chan = l2cap_pi(sk)->chan;

		BT_DBG("child chan %p state %s", chan,
		       state_to_string(chan->state));

		l2cap_chan_lock(chan);
		__clear_chan_timer(chan);
		l2cap_chan_close(chan, ECONNRESET);
		l2cap_chan_unlock(chan);

		l2cap_sock_kill(sk);
	}
}