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
struct tipc_net {int /*<<< orphan*/  nametbl_lock; struct name_table* nametbl; } ;
struct net {int dummy; } ;
struct name_table {int /*<<< orphan*/  cluster_scope_lock; int /*<<< orphan*/  cluster_scope; int /*<<< orphan*/  node_scope; int /*<<< orphan*/ * services; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int TIPC_NAMETBL_SIZE ; 
 struct name_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct tipc_net* tipc_net (struct net*) ; 

int tipc_nametbl_init(struct net *net)
{
	struct tipc_net *tn = tipc_net(net);
	struct name_table *nt;
	int i;

	nt = kzalloc(sizeof(*nt), GFP_KERNEL);
	if (!nt)
		return -ENOMEM;

	for (i = 0; i < TIPC_NAMETBL_SIZE; i++)
		INIT_HLIST_HEAD(&nt->services[i]);

	INIT_LIST_HEAD(&nt->node_scope);
	INIT_LIST_HEAD(&nt->cluster_scope);
	rwlock_init(&nt->cluster_scope_lock);
	tn->nametbl = nt;
	spin_lock_init(&tn->nametbl_lock);
	return 0;
}