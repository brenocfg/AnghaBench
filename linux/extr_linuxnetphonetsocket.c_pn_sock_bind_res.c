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
typedef  size_t u8 ;
struct sock {int /*<<< orphan*/  sk_socket; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EADDRINUSE ; 
 int EAGAIN ; 
 int ENOIOCTLCMD ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pn_socket_autobind (int /*<<< orphan*/ ) ; 
 TYPE_1__ pnres ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  resource_mutex ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

int pn_sock_bind_res(struct sock *sk, u8 res)
{
	int ret = -EADDRINUSE;

	if (!net_eq(sock_net(sk), &init_net))
		return -ENOIOCTLCMD;
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	if (pn_socket_autobind(sk->sk_socket))
		return -EAGAIN;

	mutex_lock(&resource_mutex);
	if (pnres.sk[res] == NULL) {
		sock_hold(sk);
		rcu_assign_pointer(pnres.sk[res], sk);
		ret = 0;
	}
	mutex_unlock(&resource_mutex);
	return ret;
}