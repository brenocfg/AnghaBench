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
struct sock {scalar_t__ sk_state; } ;
struct msghdr {int dummy; } ;

/* Variables and functions */
 int ENOTCONN ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int unix_dgram_recvmsg (struct socket*,struct msghdr*,size_t,int) ; 

__attribute__((used)) static int unix_seqpacket_recvmsg(struct socket *sock, struct msghdr *msg,
				  size_t size, int flags)
{
	struct sock *sk = sock->sk;

	if (sk->sk_state != TCP_ESTABLISHED)
		return -ENOTCONN;

	return unix_dgram_recvmsg(sock, msg, size, flags);
}