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
struct tipc_node {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  random; } ;

/* Variables and functions */
 TYPE_1__* tipc_net (struct net*) ; 
 struct tipc_node* tipc_node_find (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_put (struct tipc_node*) ; 

__attribute__((used)) static u32 tipc_node_suggest_addr(struct net *net, u32 addr)
{
	struct tipc_node *n;

	addr ^= tipc_net(net)->random;
	while ((n = tipc_node_find(net, addr))) {
		tipc_node_put(n);
		addr++;
	}
	return addr;
}