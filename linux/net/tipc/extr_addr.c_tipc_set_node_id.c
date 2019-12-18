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
typedef  int u32 ;
struct tipc_net {int trial_addr; int /*<<< orphan*/  net_id; int /*<<< orphan*/  node_id_string; int /*<<< orphan*/  node_id; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_ID_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tipc_net* tipc_net (struct net*) ; 
 int /*<<< orphan*/  tipc_nodeid2string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_own_id_string (struct net*) ; 

void tipc_set_node_id(struct net *net, u8 *id)
{
	struct tipc_net *tn = tipc_net(net);
	u32 *tmp = (u32 *)id;

	memcpy(tn->node_id, id, NODE_ID_LEN);
	tipc_nodeid2string(tn->node_id_string, id);
	tn->trial_addr = tmp[0] ^ tmp[1] ^ tmp[2] ^ tmp[3];
	pr_info("Own node identity %s, cluster identity %u\n",
		tipc_own_id_string(net), tn->net_id);
}