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
struct afs_vnode {int /*<<< orphan*/  lock; int /*<<< orphan*/  permit_cache; } ;
struct afs_permits {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  afs_put_permits (struct afs_permits*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct afs_permits* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void afs_clear_permits(struct afs_vnode *vnode)
{
	struct afs_permits *permits;

	spin_lock(&vnode->lock);
	permits = rcu_dereference_protected(vnode->permit_cache,
					    lockdep_is_held(&vnode->lock));
	RCU_INIT_POINTER(vnode->permit_cache, NULL);
	spin_unlock(&vnode->lock);

	afs_put_permits(permits);
}