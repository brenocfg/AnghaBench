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
struct sock {TYPE_1__* sk_prot; } ;
struct TYPE_4__ {int /*<<< orphan*/  user_ns; } ;
struct TYPE_3__ {int (* diag_destroy ) (struct sock*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* sock_net (struct sock*) ; 
 int stub1 (struct sock*,int) ; 

int sock_diag_destroy(struct sock *sk, int err)
{
	if (!ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN))
		return -EPERM;

	if (!sk->sk_prot->diag_destroy)
		return -EOPNOTSUPP;

	return sk->sk_prot->diag_destroy(sk, err);
}