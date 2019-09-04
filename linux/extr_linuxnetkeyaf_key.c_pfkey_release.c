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
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_write_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  pfkey_remove (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static int pfkey_release(struct socket *sock)
{
	struct sock *sk = sock->sk;

	if (!sk)
		return 0;

	pfkey_remove(sk);

	sock_orphan(sk);
	sock->sk = NULL;
	skb_queue_purge(&sk->sk_write_queue);

	synchronize_rcu();
	sock_put(sk);

	return 0;
}