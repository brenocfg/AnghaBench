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
typedef  size_t u32 ;
struct tipc_bearer {int mtu; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bearer_list; } ;

/* Variables and functions */
 struct tipc_bearer* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 TYPE_1__* tipc_net (struct net*) ; 

int tipc_bearer_mtu(struct net *net, u32 bearer_id)
{
	int mtu = 0;
	struct tipc_bearer *b;

	rcu_read_lock();
	b = rcu_dereference(tipc_net(net)->bearer_list[bearer_id]);
	if (b)
		mtu = b->mtu;
	rcu_read_unlock();
	return mtu;
}