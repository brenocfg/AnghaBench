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
struct tipc_service {int /*<<< orphan*/  lock; } ;
struct publication {int dummy; } ;
struct net {int dummy; } ;
struct name_table {int /*<<< orphan*/ * services; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_NODE_SCOPE ; 
 size_t hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct name_table* tipc_name_table (struct net*) ; 
 struct tipc_service* tipc_service_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tipc_service* tipc_service_find (struct net*,int /*<<< orphan*/ ) ; 
 struct publication* tipc_service_insert_publ (struct net*,struct tipc_service*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct publication *tipc_nametbl_insert_publ(struct net *net, u32 type,
					     u32 lower, u32 upper,
					     u32 scope, u32 node,
					     u32 port, u32 key)
{
	struct name_table *nt = tipc_name_table(net);
	struct tipc_service *sc;
	struct publication *p;

	if (scope > TIPC_NODE_SCOPE || lower > upper) {
		pr_debug("Failed to bind illegal {%u,%u,%u} with scope %u\n",
			 type, lower, upper, scope);
		return NULL;
	}
	sc = tipc_service_find(net, type);
	if (!sc)
		sc = tipc_service_create(type, &nt->services[hash(type)]);
	if (!sc)
		return NULL;

	spin_lock_bh(&sc->lock);
	p = tipc_service_insert_publ(net, sc, type, lower, upper,
				     scope, node, port, key);
	spin_unlock_bh(&sc->lock);
	return p;
}