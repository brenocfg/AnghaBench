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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ broadcast; } ;
struct tipc_bearer {TYPE_1__ bcast_addr; } ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ TIPC_BROADCAST_SUPPORT ; 
 struct tipc_bearer* bearer_get (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

bool tipc_bearer_bcast_support(struct net *net, u32 bearer_id)
{
	bool supp = false;
	struct tipc_bearer *b;

	rcu_read_lock();
	b = bearer_get(net, bearer_id);
	if (b)
		supp = (b->bcast_addr.broadcast == TIPC_BROADCAST_SUPPORT);
	rcu_read_unlock();
	return supp;
}