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
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  tipc_bearer_stop (struct net*) ; 
 int /*<<< orphan*/  tipc_node_stop (struct net*) ; 
 int /*<<< orphan*/  tipc_own_id (struct net*) ; 

void tipc_net_stop(struct net *net)
{
	if (!tipc_own_id(net))
		return;

	rtnl_lock();
	tipc_bearer_stop(net);
	tipc_node_stop(net);
	rtnl_unlock();

	pr_info("Left network mode\n");
}