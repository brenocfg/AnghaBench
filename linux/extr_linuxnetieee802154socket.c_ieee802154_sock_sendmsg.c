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
struct TYPE_2__ {int (* sendmsg ) (struct sock*,struct msghdr*,size_t) ;} ;

/* Variables and functions */
 int stub1 (struct sock*,struct msghdr*,size_t) ; 

__attribute__((used)) static int ieee802154_sock_sendmsg(struct socket *sock, struct msghdr *msg,
				   size_t len)
{
	struct sock *sk = sock->sk;

	return sk->sk_prot->sendmsg(sk, msg, len);
}