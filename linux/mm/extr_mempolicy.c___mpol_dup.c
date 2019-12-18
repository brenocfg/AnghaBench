#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mempolicy {int /*<<< orphan*/  refcnt; } ;
typedef  int /*<<< orphan*/  nodemask_t ;
struct TYPE_5__ {struct mempolicy* mempolicy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mempolicy* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpuset_mems_allowed (TYPE_1__*) ; 
 TYPE_1__* current ; 
 scalar_t__ current_cpuset_is_being_rebound () ; 
 struct mempolicy* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpol_rebind_policy (struct mempolicy*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  policy_cache ; 
 int /*<<< orphan*/  task_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_1__*) ; 

struct mempolicy *__mpol_dup(struct mempolicy *old)
{
	struct mempolicy *new = kmem_cache_alloc(policy_cache, GFP_KERNEL);

	if (!new)
		return ERR_PTR(-ENOMEM);

	/* task's mempolicy is protected by alloc_lock */
	if (old == current->mempolicy) {
		task_lock(current);
		*new = *old;
		task_unlock(current);
	} else
		*new = *old;

	if (current_cpuset_is_being_rebound()) {
		nodemask_t mems = cpuset_mems_allowed(current);
		mpol_rebind_policy(new, &mems);
	}
	atomic_set(&new->refcnt, 1);
	return new;
}