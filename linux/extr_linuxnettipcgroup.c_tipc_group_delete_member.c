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
struct tipc_member {int /*<<< orphan*/  node; int /*<<< orphan*/  small_win; int /*<<< orphan*/  list; int /*<<< orphan*/  bc_acked; int /*<<< orphan*/  tree_node; } ;
struct tipc_group {int /*<<< orphan*/  dests; scalar_t__ bc_ackers; scalar_t__ bc_snd_nxt; int /*<<< orphan*/  member_cnt; int /*<<< orphan*/  members; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tipc_member*) ; 
 scalar_t__ less (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_group_decr_active (struct tipc_group*,struct tipc_member*) ; 
 int /*<<< orphan*/  tipc_group_find_node (struct tipc_group*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_nlist_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tipc_group_delete_member(struct tipc_group *grp,
				     struct tipc_member *m)
{
	rb_erase(&m->tree_node, &grp->members);
	grp->member_cnt--;

	/* Check if we were waiting for replicast ack from this member */
	if (grp->bc_ackers && less(m->bc_acked, grp->bc_snd_nxt - 1))
		grp->bc_ackers--;

	list_del_init(&m->list);
	list_del_init(&m->small_win);
	tipc_group_decr_active(grp, m);

	/* If last member on a node, remove node from dest list */
	if (!tipc_group_find_node(grp, m->node))
		tipc_nlist_del(&grp->dests, m->node);

	kfree(m);
}