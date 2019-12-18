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
struct kernfs_node {int /*<<< orphan*/  active; int /*<<< orphan*/  dep_map; } ;
struct TYPE_2__ {int /*<<< orphan*/  deactivate_waitq; } ;

/* Variables and functions */
 int KN_DEACTIVATED_BIAS ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 scalar_t__ kernfs_lockdep (struct kernfs_node*) ; 
 TYPE_1__* kernfs_root (struct kernfs_node*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rwsem_release (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void kernfs_put_active(struct kernfs_node *kn)
{
	int v;

	if (unlikely(!kn))
		return;

	if (kernfs_lockdep(kn))
		rwsem_release(&kn->dep_map, 1, _RET_IP_);
	v = atomic_dec_return(&kn->active);
	if (likely(v != KN_DEACTIVATED_BIAS))
		return;

	wake_up_all(&kernfs_root(kn)->deactivate_waitq);
}