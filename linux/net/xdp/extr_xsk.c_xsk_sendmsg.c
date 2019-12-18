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
struct xdp_sock {int dummy; } ;
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct msghdr {int msg_flags; } ;

/* Variables and functions */
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int MSG_DONTWAIT ; 
 int __xsk_sendmsg (struct sock*) ; 
 scalar_t__ unlikely (int) ; 
 struct xdp_sock* xdp_sk (struct sock*) ; 
 int /*<<< orphan*/  xsk_is_bound (struct xdp_sock*) ; 

__attribute__((used)) static int xsk_sendmsg(struct socket *sock, struct msghdr *m, size_t total_len)
{
	bool need_wait = !(m->msg_flags & MSG_DONTWAIT);
	struct sock *sk = sock->sk;
	struct xdp_sock *xs = xdp_sk(sk);

	if (unlikely(!xsk_is_bound(xs)))
		return -ENXIO;
	if (unlikely(need_wait))
		return -EOPNOTSUPP;

	return __xsk_sendmsg(sk);
}