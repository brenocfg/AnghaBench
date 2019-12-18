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
typedef  int /*<<< orphan*/  u16 ;
struct tipc_node {int /*<<< orphan*/  capabilities; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_NODE_CAPABILITIES ; 
 struct tipc_node* tipc_node_find (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_put (struct tipc_node*) ; 
 scalar_t__ unlikely (int) ; 

u16 tipc_node_get_capabilities(struct net *net, u32 addr)
{
	struct tipc_node *n;
	u16 caps;

	n = tipc_node_find(net, addr);
	if (unlikely(!n))
		return TIPC_NODE_CAPABILITIES;
	caps = n->capabilities;
	tipc_node_put(n);
	return caps;
}