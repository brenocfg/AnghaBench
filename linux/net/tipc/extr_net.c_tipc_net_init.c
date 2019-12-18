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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  tipc_net_finalize (struct net*,scalar_t__) ; 
 scalar_t__ tipc_own_id (struct net*) ; 
 int /*<<< orphan*/  tipc_set_node_id (struct net*,int /*<<< orphan*/ *) ; 

int tipc_net_init(struct net *net, u8 *node_id, u32 addr)
{
	if (tipc_own_id(net)) {
		pr_info("Cannot configure node identity twice\n");
		return -1;
	}
	pr_info("Started in network mode\n");

	if (node_id)
		tipc_set_node_id(net, node_id);
	if (addr)
		tipc_net_finalize(net, addr);
	return 0;
}