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
struct sock {unsigned long sk_tsq_flags; } ;
struct TYPE_4__ {TYPE_1__* icsk_af_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* mtu_reduced ) (struct sock*) ;} ;

/* Variables and functions */
 unsigned long TCPF_DELACK_TIMER_DEFERRED ; 
 unsigned long TCPF_MTU_REDUCED_DEFERRED ; 
 unsigned long TCPF_TSQ_DEFERRED ; 
 unsigned long TCPF_WRITE_TIMER_DEFERRED ; 
 unsigned long TCP_DEFERRED_ALL ; 
 int /*<<< orphan*/  __sock_put (struct sock*) ; 
 unsigned long cmpxchg (unsigned long*,unsigned long,unsigned long) ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  sock_release_ownership (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  tcp_delack_timer_handler (struct sock*) ; 
 int /*<<< orphan*/  tcp_tsq_write (struct sock*) ; 
 int /*<<< orphan*/  tcp_write_timer_handler (struct sock*) ; 

void tcp_release_cb(struct sock *sk)
{
	unsigned long flags, nflags;

	/* perform an atomic operation only if at least one flag is set */
	do {
		flags = sk->sk_tsq_flags;
		if (!(flags & TCP_DEFERRED_ALL))
			return;
		nflags = flags & ~TCP_DEFERRED_ALL;
	} while (cmpxchg(&sk->sk_tsq_flags, flags, nflags) != flags);

	if (flags & TCPF_TSQ_DEFERRED) {
		tcp_tsq_write(sk);
		__sock_put(sk);
	}
	/* Here begins the tricky part :
	 * We are called from release_sock() with :
	 * 1) BH disabled
	 * 2) sk_lock.slock spinlock held
	 * 3) socket owned by us (sk->sk_lock.owned == 1)
	 *
	 * But following code is meant to be called from BH handlers,
	 * so we should keep BH disabled, but early release socket ownership
	 */
	sock_release_ownership(sk);

	if (flags & TCPF_WRITE_TIMER_DEFERRED) {
		tcp_write_timer_handler(sk);
		__sock_put(sk);
	}
	if (flags & TCPF_DELACK_TIMER_DEFERRED) {
		tcp_delack_timer_handler(sk);
		__sock_put(sk);
	}
	if (flags & TCPF_MTU_REDUCED_DEFERRED) {
		inet_csk(sk)->icsk_af_ops->mtu_reduced(sk);
		__sock_put(sk);
	}
}