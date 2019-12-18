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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_node {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ in_own_node (struct net*,int /*<<< orphan*/ ) ; 
 int node_is_up (struct tipc_node*) ; 
 struct tipc_node* tipc_node_find (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_put (struct tipc_node*) ; 

bool tipc_node_is_up(struct net *net, u32 addr)
{
	struct tipc_node *n;
	bool retval = false;

	if (in_own_node(net, addr))
		return true;

	n = tipc_node_find(net, addr);
	if (!n)
		return false;
	retval = node_is_up(n);
	tipc_node_put(n);
	return retval;
}