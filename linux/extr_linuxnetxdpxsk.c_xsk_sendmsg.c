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
struct xdp_sock {scalar_t__ zc; int /*<<< orphan*/  tx; TYPE_1__* dev; } ;
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct msghdr {int msg_flags; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int ENETDOWN ; 
 int ENOBUFS ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int IFF_UP ; 
 int MSG_DONTWAIT ; 
 scalar_t__ unlikely (int) ; 
 struct xdp_sock* xdp_sk (struct sock*) ; 
 int xsk_generic_xmit (struct sock*,struct msghdr*,size_t) ; 
 int xsk_zc_xmit (struct sock*) ; 

__attribute__((used)) static int xsk_sendmsg(struct socket *sock, struct msghdr *m, size_t total_len)
{
	bool need_wait = !(m->msg_flags & MSG_DONTWAIT);
	struct sock *sk = sock->sk;
	struct xdp_sock *xs = xdp_sk(sk);

	if (unlikely(!xs->dev))
		return -ENXIO;
	if (unlikely(!(xs->dev->flags & IFF_UP)))
		return -ENETDOWN;
	if (unlikely(!xs->tx))
		return -ENOBUFS;
	if (need_wait)
		return -EOPNOTSUPP;

	return (xs->zc) ? xsk_zc_xmit(sk) : xsk_generic_xmit(sk, m, total_len);
}