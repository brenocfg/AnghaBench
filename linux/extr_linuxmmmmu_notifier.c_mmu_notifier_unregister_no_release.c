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
struct mmu_notifier {int /*<<< orphan*/  hlist; } ;
struct mm_struct {int /*<<< orphan*/  mm_count; TYPE_1__* mmu_notifier_mm; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmdrop (struct mm_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void mmu_notifier_unregister_no_release(struct mmu_notifier *mn,
					struct mm_struct *mm)
{
	spin_lock(&mm->mmu_notifier_mm->lock);
	/*
	 * Can not use list_del_rcu() since __mmu_notifier_release
	 * can delete it before we hold the lock.
	 */
	hlist_del_init_rcu(&mn->hlist);
	spin_unlock(&mm->mmu_notifier_mm->lock);

	BUG_ON(atomic_read(&mm->mm_count) <= 0);
	mmdrop(mm);
}