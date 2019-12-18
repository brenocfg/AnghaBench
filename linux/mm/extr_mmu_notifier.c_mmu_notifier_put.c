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
struct mmu_notifier {int /*<<< orphan*/  rcu; int /*<<< orphan*/  hlist; scalar_t__ users; struct mm_struct* mm; } ;
struct mm_struct {TYPE_1__* mmu_notifier_mm; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  call_srcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmu_notifier_free_rcu ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu ; 

void mmu_notifier_put(struct mmu_notifier *mn)
{
	struct mm_struct *mm = mn->mm;

	spin_lock(&mm->mmu_notifier_mm->lock);
	if (WARN_ON(!mn->users) || --mn->users)
		goto out_unlock;
	hlist_del_init_rcu(&mn->hlist);
	spin_unlock(&mm->mmu_notifier_mm->lock);

	call_srcu(&srcu, &mn->rcu, mmu_notifier_free_rcu);
	return;

out_unlock:
	spin_unlock(&mm->mmu_notifier_mm->lock);
}