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
struct tipc_net {int /*<<< orphan*/ * bearer_list; } ;
struct tipc_bearer {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct tipc_bearer* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct tipc_net* tipc_net (struct net*) ; 

__attribute__((used)) static struct tipc_bearer *bearer_get(struct net *net, int bearer_id)
{
	struct tipc_net *tn = tipc_net(net);

	return rcu_dereference(tn->bearer_list[bearer_id]);
}