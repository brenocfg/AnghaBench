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
struct kernfs_node {int flags; int /*<<< orphan*/  active; int /*<<< orphan*/  rb; scalar_t__ parent; } ;

/* Variables and functions */
 int KERNFS_ACTIVATED ; 
 scalar_t__ KN_DEACTIVATED_BIAS ; 
 scalar_t__ RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernfs_mutex ; 
 struct kernfs_node* kernfs_next_descendant_post (struct kernfs_node*,struct kernfs_node*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void kernfs_activate(struct kernfs_node *kn)
{
	struct kernfs_node *pos;

	mutex_lock(&kernfs_mutex);

	pos = NULL;
	while ((pos = kernfs_next_descendant_post(pos, kn))) {
		if (!pos || (pos->flags & KERNFS_ACTIVATED))
			continue;

		WARN_ON_ONCE(pos->parent && RB_EMPTY_NODE(&pos->rb));
		WARN_ON_ONCE(atomic_read(&pos->active) != KN_DEACTIVATED_BIAS);

		atomic_sub(KN_DEACTIVATED_BIAS, &pos->active);
		pos->flags |= KERNFS_ACTIVATED;
	}

	mutex_unlock(&kernfs_mutex);
}