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
struct sock {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int inet_release (struct socket*) ; 
 int /*<<< orphan*/  ipv6_sock_ac_close (struct sock*) ; 
 int /*<<< orphan*/  ipv6_sock_mc_close (struct sock*) ; 

int inet6_release(struct socket *sock)
{
	struct sock *sk = sock->sk;

	if (!sk)
		return -EINVAL;

	/* Free mc lists */
	ipv6_sock_mc_close(sk);

	/* Free ac lists */
	ipv6_sock_ac_close(sk);

	return inet_release(sock);
}