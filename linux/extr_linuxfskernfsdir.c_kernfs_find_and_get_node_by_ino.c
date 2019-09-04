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
struct kernfs_root {int /*<<< orphan*/  ino_idr; } ;
struct TYPE_2__ {unsigned int ino; } ;
struct kernfs_node {TYPE_1__ id; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 struct kernfs_node* idr_find (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct kernfs_node *kernfs_find_and_get_node_by_ino(struct kernfs_root *root,
						    unsigned int ino)
{
	struct kernfs_node *kn;

	rcu_read_lock();
	kn = idr_find(&root->ino_idr, ino);
	if (!kn)
		goto out;

	/*
	 * Since kernfs_node is freed in RCU, it's possible an old node for ino
	 * is freed, but reused before RCU grace period. But a freed node (see
	 * kernfs_put) or an incompletedly initialized node (see
	 * __kernfs_new_node) should have 'count' 0. We can use this fact to
	 * filter out such node.
	 */
	if (!atomic_inc_not_zero(&kn->count)) {
		kn = NULL;
		goto out;
	}

	/*
	 * The node could be a new node or a reused node. If it's a new node,
	 * we are ok. If it's reused because of RCU (because of
	 * SLAB_TYPESAFE_BY_RCU), the __kernfs_new_node always sets its 'ino'
	 * before 'count'. So if 'count' is uptodate, 'ino' should be uptodate,
	 * hence we can use 'ino' to filter stale node.
	 */
	if (kn->id.ino != ino)
		goto out;
	rcu_read_unlock();

	return kn;
out:
	rcu_read_unlock();
	kernfs_put(kn);
	return NULL;
}