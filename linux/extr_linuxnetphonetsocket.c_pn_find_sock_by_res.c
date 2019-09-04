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
struct sock {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ *) ; 
 TYPE_1__ pnres ; 
 struct sock* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 

struct sock *pn_find_sock_by_res(struct net *net, u8 res)
{
	struct sock *sk;

	if (!net_eq(net, &init_net))
		return NULL;

	rcu_read_lock();
	sk = rcu_dereference(pnres.sk[res]);
	if (sk)
		sock_hold(sk);
	rcu_read_unlock();
	return sk;
}