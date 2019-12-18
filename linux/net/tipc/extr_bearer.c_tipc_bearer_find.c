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
 size_t MAX_BEARERS ; 
 struct tipc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct tipc_bearer* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  tipc_net_id ; 

struct tipc_bearer *tipc_bearer_find(struct net *net, const char *name)
{
	struct tipc_net *tn = net_generic(net, tipc_net_id);
	struct tipc_bearer *b;
	u32 i;

	for (i = 0; i < MAX_BEARERS; i++) {
		b = rtnl_dereference(tn->bearer_list[i]);
		if (b && (!strcmp(b->name, name)))
			return b;
	}
	return NULL;
}