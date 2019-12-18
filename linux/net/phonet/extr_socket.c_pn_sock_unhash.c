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
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pn_sock_unbind_all_res (struct sock*) ; 
 TYPE_1__ pnsocks ; 
 int /*<<< orphan*/  sk_del_node_init_rcu (struct sock*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void pn_sock_unhash(struct sock *sk)
{
	mutex_lock(&pnsocks.lock);
	sk_del_node_init_rcu(sk);
	mutex_unlock(&pnsocks.lock);
	pn_sock_unbind_all_res(sk);
	synchronize_rcu();
}