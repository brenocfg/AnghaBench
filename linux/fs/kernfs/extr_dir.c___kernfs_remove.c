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
struct kernfs_node {int flags; TYPE_1__* parent; int /*<<< orphan*/  active; int /*<<< orphan*/  name; int /*<<< orphan*/  rb; } ;
struct kernfs_iattrs {int /*<<< orphan*/  ia_ctime; int /*<<< orphan*/  ia_mtime; } ;
struct TYPE_2__ {struct kernfs_iattrs* iattr; } ;

/* Variables and functions */
 int KERNFS_ACTIVATED ; 
 scalar_t__ KN_DEACTIVATED_BIAS ; 
 scalar_t__ RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ kernfs_active (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_drain (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_get (struct kernfs_node*) ; 
 struct kernfs_node* kernfs_leftmost_descendant (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_mutex ; 
 struct kernfs_node* kernfs_next_descendant_post (struct kernfs_node*,struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 
 scalar_t__ kernfs_unlink_sibling (struct kernfs_node*) ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __kernfs_remove(struct kernfs_node *kn)
{
	struct kernfs_node *pos;

	lockdep_assert_held(&kernfs_mutex);

	/*
	 * Short-circuit if non-root @kn has already finished removal.
	 * This is for kernfs_remove_self() which plays with active ref
	 * after removal.
	 */
	if (!kn || (kn->parent && RB_EMPTY_NODE(&kn->rb)))
		return;

	pr_debug("kernfs %s: removing\n", kn->name);

	/* prevent any new usage under @kn by deactivating all nodes */
	pos = NULL;
	while ((pos = kernfs_next_descendant_post(pos, kn)))
		if (kernfs_active(pos))
			atomic_add(KN_DEACTIVATED_BIAS, &pos->active);

	/* deactivate and unlink the subtree node-by-node */
	do {
		pos = kernfs_leftmost_descendant(kn);

		/*
		 * kernfs_drain() drops kernfs_mutex temporarily and @pos's
		 * base ref could have been put by someone else by the time
		 * the function returns.  Make sure it doesn't go away
		 * underneath us.
		 */
		kernfs_get(pos);

		/*
		 * Drain iff @kn was activated.  This avoids draining and
		 * its lockdep annotations for nodes which have never been
		 * activated and allows embedding kernfs_remove() in create
		 * error paths without worrying about draining.
		 */
		if (kn->flags & KERNFS_ACTIVATED)
			kernfs_drain(pos);
		else
			WARN_ON_ONCE(atomic_read(&kn->active) != KN_DEACTIVATED_BIAS);

		/*
		 * kernfs_unlink_sibling() succeeds once per node.  Use it
		 * to decide who's responsible for cleanups.
		 */
		if (!pos->parent || kernfs_unlink_sibling(pos)) {
			struct kernfs_iattrs *ps_iattr =
				pos->parent ? pos->parent->iattr : NULL;

			/* update timestamps on the parent */
			if (ps_iattr) {
				ktime_get_real_ts64(&ps_iattr->ia_ctime);
				ps_iattr->ia_mtime = ps_iattr->ia_ctime;
			}

			kernfs_put(pos);
		}

		kernfs_put(pos);
	} while (pos != kn);
}