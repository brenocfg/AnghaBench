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
struct sock {int /*<<< orphan*/  sk_ack_backlog; } ;
struct l2cap_chan {struct sock* data; } ;
struct TYPE_2__ {struct l2cap_chan* chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTPROTO_L2CAP ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  bt_accept_enqueue (struct sock*,struct sock*,int) ; 
 int /*<<< orphan*/  bt_sock_reclassify_lock (struct sock*,int /*<<< orphan*/ ) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 struct sock* l2cap_sock_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_sock_init (struct sock*,struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 scalar_t__ sk_acceptq_is_full (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static struct l2cap_chan *l2cap_sock_new_connection_cb(struct l2cap_chan *chan)
{
	struct sock *sk, *parent = chan->data;

	lock_sock(parent);

	/* Check for backlog size */
	if (sk_acceptq_is_full(parent)) {
		BT_DBG("backlog full %d", parent->sk_ack_backlog);
		release_sock(parent);
		return NULL;
	}

	sk = l2cap_sock_alloc(sock_net(parent), NULL, BTPROTO_L2CAP,
			      GFP_ATOMIC, 0);
	if (!sk) {
		release_sock(parent);
		return NULL;
        }

	bt_sock_reclassify_lock(sk, BTPROTO_L2CAP);

	l2cap_sock_init(sk, parent);

	bt_accept_enqueue(parent, sk, false);

	release_sock(parent);

	return l2cap_pi(sk)->chan;
}