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
struct vsock_sock {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/  sk_shutdown; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release ) (struct vsock_sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SHUTDOWN_MASK ; 
 int SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  lock_sock_nested (struct sock*,int) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct vsock_sock*) ; 
 TYPE_1__* transport ; 
 struct sock* vsock_dequeue_accept (struct sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static void __vsock_release(struct sock *sk, int level)
{
	if (sk) {
		struct sk_buff *skb;
		struct sock *pending;
		struct vsock_sock *vsk;

		vsk = vsock_sk(sk);
		pending = NULL;	/* Compiler warning. */

		/* The release call is supposed to use lock_sock_nested()
		 * rather than lock_sock(), if a sock lock should be acquired.
		 */
		transport->release(vsk);

		/* When "level" is SINGLE_DEPTH_NESTING, use the nested
		 * version to avoid the warning "possible recursive locking
		 * detected". When "level" is 0, lock_sock_nested(sk, level)
		 * is the same as lock_sock(sk).
		 */
		lock_sock_nested(sk, level);
		sock_orphan(sk);
		sk->sk_shutdown = SHUTDOWN_MASK;

		while ((skb = skb_dequeue(&sk->sk_receive_queue)))
			kfree_skb(skb);

		/* Clean up any sockets that never were accepted. */
		while ((pending = vsock_dequeue_accept(sk)) != NULL) {
			__vsock_release(pending, SINGLE_DEPTH_NESTING);
			sock_put(pending);
		}

		release_sock(sk);
		sock_put(sk);
	}
}