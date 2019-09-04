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
struct vm_area_struct {int /*<<< orphan*/  vm_end; } ;
struct shared_policy {int /*<<< orphan*/  lock; int /*<<< orphan*/  root; } ;
struct TYPE_2__ {int /*<<< orphan*/  user_nodemask; } ;
struct mempolicy {TYPE_1__ w; int /*<<< orphan*/  flags; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mempolicy*) ; 
 int /*<<< orphan*/  NODEMASK_SCRATCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NODEMASK_SCRATCH_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  TASK_SIZE ; 
 int /*<<< orphan*/  current ; 
 struct mempolicy* mpol_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpol_put (struct mempolicy*) ; 
 int mpol_set_nodemask (struct mempolicy*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpol_set_shared_policy (struct shared_policy*,struct vm_area_struct*,struct mempolicy*) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scratch ; 
 int /*<<< orphan*/  task_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vma_init (struct vm_area_struct*,int /*<<< orphan*/ *) ; 

void mpol_shared_policy_init(struct shared_policy *sp, struct mempolicy *mpol)
{
	int ret;

	sp->root = RB_ROOT;		/* empty tree == default mempolicy */
	rwlock_init(&sp->lock);

	if (mpol) {
		struct vm_area_struct pvma;
		struct mempolicy *new;
		NODEMASK_SCRATCH(scratch);

		if (!scratch)
			goto put_mpol;
		/* contextualize the tmpfs mount point mempolicy */
		new = mpol_new(mpol->mode, mpol->flags, &mpol->w.user_nodemask);
		if (IS_ERR(new))
			goto free_scratch; /* no valid nodemask intersection */

		task_lock(current);
		ret = mpol_set_nodemask(new, &mpol->w.user_nodemask, scratch);
		task_unlock(current);
		if (ret)
			goto put_new;

		/* Create pseudo-vma that contains just the policy */
		vma_init(&pvma, NULL);
		pvma.vm_end = TASK_SIZE;	/* policy covers entire file */
		mpol_set_shared_policy(sp, &pvma, new); /* adds ref */

put_new:
		mpol_put(new);			/* drop initial ref */
free_scratch:
		NODEMASK_SCRATCH_FREE(scratch);
put_mpol:
		mpol_put(mpol);	/* drop our incoming ref on sb mpol */
	}
}