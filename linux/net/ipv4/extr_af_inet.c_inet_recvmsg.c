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
struct msghdr {int msg_namelen; } ;
struct TYPE_2__ {int /*<<< orphan*/  recvmsg; } ;

/* Variables and functions */
 int INDIRECT_CALL_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sock*,struct msghdr*,size_t,int,int,int*) ; 
 int MSG_DONTWAIT ; 
 int MSG_ERRQUEUE ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  sock_rps_record_flow (struct sock*) ; 
 int /*<<< orphan*/  tcp_recvmsg ; 
 int /*<<< orphan*/  udp_recvmsg ; 

int inet_recvmsg(struct socket *sock, struct msghdr *msg, size_t size,
		 int flags)
{
	struct sock *sk = sock->sk;
	int addr_len = 0;
	int err;

	if (likely(!(flags & MSG_ERRQUEUE)))
		sock_rps_record_flow(sk);

	err = INDIRECT_CALL_2(sk->sk_prot->recvmsg, tcp_recvmsg, udp_recvmsg,
			      sk, msg, size, flags & MSG_DONTWAIT,
			      flags & ~MSG_DONTWAIT, &addr_len);
	if (err >= 0)
		msg->msg_namelen = addr_len;
	return err;
}