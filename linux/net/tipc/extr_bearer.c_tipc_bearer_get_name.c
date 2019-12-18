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
typedef  size_t u32 ;
struct tipc_net {int /*<<< orphan*/ * bearer_list; } ;
struct tipc_bearer {int /*<<< orphan*/  name; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t MAX_BEARERS ; 
 struct tipc_bearer* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 struct tipc_net* tipc_net (struct net*) ; 

int tipc_bearer_get_name(struct net *net, char *name, u32 bearer_id)
{
	struct tipc_net *tn = tipc_net(net);
	struct tipc_bearer *b;

	if (bearer_id >= MAX_BEARERS)
		return -EINVAL;

	b = rtnl_dereference(tn->bearer_list[bearer_id]);
	if (!b)
		return -EINVAL;

	strcpy(name, b->name);
	return 0;
}