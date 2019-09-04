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
struct kernfs_node {int /*<<< orphan*/  dep_map; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ kernfs_lockdep (struct kernfs_node*) ; 
 int /*<<< orphan*/  rwsem_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void kernfs_unbreak_active_protection(struct kernfs_node *kn)
{
	/*
	 * @kn->active could be in any state; however, the increment we do
	 * here will be undone as soon as the enclosing kernfs operation
	 * finishes and this temporary bump can't break anything.  If @kn
	 * is alive, nothing changes.  If @kn is being deactivated, the
	 * soon-to-follow put will either finish deactivation or restore
	 * deactivated state.  If @kn is already removed, the temporary
	 * bump is guaranteed to be gone before @kn is released.
	 */
	atomic_inc(&kn->active);
	if (kernfs_lockdep(kn))
		rwsem_acquire(&kn->dep_map, 0, 1, _RET_IP_);
}