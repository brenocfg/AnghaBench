#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_3__* sk; } ;
struct sockaddr {int dummy; } ;
struct smc_sock {TYPE_2__* clcsock; } ;
struct TYPE_6__ {scalar_t__ sk_state; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int (* getname ) (TYPE_2__*,struct sockaddr*,int) ;} ;

/* Variables and functions */
 int ENOTCONN ; 
 scalar_t__ SMC_ACTIVE ; 
 scalar_t__ SMC_APPCLOSEWAIT1 ; 
 struct smc_sock* smc_sk (TYPE_3__*) ; 
 int stub1 (TYPE_2__*,struct sockaddr*,int) ; 

__attribute__((used)) static int smc_getname(struct socket *sock, struct sockaddr *addr,
		       int peer)
{
	struct smc_sock *smc;

	if (peer && (sock->sk->sk_state != SMC_ACTIVE) &&
	    (sock->sk->sk_state != SMC_APPCLOSEWAIT1))
		return -ENOTCONN;

	smc = smc_sk(sock->sk);

	return smc->clcsock->ops->getname(smc->clcsock, addr, peer);
}