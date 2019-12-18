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
struct socket {struct sock* sk; } ;
struct sock {TYPE_1__* sk_prot; } ;
struct msghdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sendmsg; } ;

/* Variables and functions */
 int EAGAIN ; 
 int INDIRECT_CALL_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sock*,struct msghdr*,size_t) ; 
 int /*<<< orphan*/  inet_send_prepare (struct sock*) ; 
 int /*<<< orphan*/  tcp_sendmsg ; 
 int /*<<< orphan*/  udpv6_sendmsg ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int inet6_sendmsg(struct socket *sock, struct msghdr *msg, size_t size)
{
	struct sock *sk = sock->sk;

	if (unlikely(inet_send_prepare(sk)))
		return -EAGAIN;

	return INDIRECT_CALL_2(sk->sk_prot->sendmsg, tcp_sendmsg, udpv6_sendmsg,
			       sk, msg, size);
}