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
struct mmu_notifier_mm {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct mmu_notifier {int users; int /*<<< orphan*/  hlist; struct mm_struct* mm; } ;
struct mm_struct {int /*<<< orphan*/  mm_users; struct mmu_notifier_mm* mmu_notifier_mm; int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CONFIG_LOCKDEP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mmu_notifier_invalidate_range_start_map ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_reclaim_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_reclaim_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mmu_notifier_mm*) ; 
 struct mmu_notifier_mm* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_map_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_map_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_drop_all_locks (struct mm_struct*) ; 
 int mm_take_all_locks (struct mm_struct*) ; 
 int /*<<< orphan*/  mmgrab (struct mm_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int __mmu_notifier_register(struct mmu_notifier *mn, struct mm_struct *mm)
{
	struct mmu_notifier_mm *mmu_notifier_mm = NULL;
	int ret;

	lockdep_assert_held_write(&mm->mmap_sem);
	BUG_ON(atomic_read(&mm->mm_users) <= 0);

	if (IS_ENABLED(CONFIG_LOCKDEP)) {
		fs_reclaim_acquire(GFP_KERNEL);
		lock_map_acquire(&__mmu_notifier_invalidate_range_start_map);
		lock_map_release(&__mmu_notifier_invalidate_range_start_map);
		fs_reclaim_release(GFP_KERNEL);
	}

	mn->mm = mm;
	mn->users = 1;

	if (!mm->mmu_notifier_mm) {
		/*
		 * kmalloc cannot be called under mm_take_all_locks(), but we
		 * know that mm->mmu_notifier_mm can't change while we hold
		 * the write side of the mmap_sem.
		 */
		mmu_notifier_mm =
			kmalloc(sizeof(struct mmu_notifier_mm), GFP_KERNEL);
		if (!mmu_notifier_mm)
			return -ENOMEM;

		INIT_HLIST_HEAD(&mmu_notifier_mm->list);
		spin_lock_init(&mmu_notifier_mm->lock);
	}

	ret = mm_take_all_locks(mm);
	if (unlikely(ret))
		goto out_clean;

	/* Pairs with the mmdrop in mmu_notifier_unregister_* */
	mmgrab(mm);

	/*
	 * Serialize the update against mmu_notifier_unregister. A
	 * side note: mmu_notifier_release can't run concurrently with
	 * us because we hold the mm_users pin (either implicitly as
	 * current->mm or explicitly with get_task_mm() or similar).
	 * We can't race against any other mmu notifier method either
	 * thanks to mm_take_all_locks().
	 */
	if (mmu_notifier_mm)
		mm->mmu_notifier_mm = mmu_notifier_mm;

	spin_lock(&mm->mmu_notifier_mm->lock);
	hlist_add_head_rcu(&mn->hlist, &mm->mmu_notifier_mm->list);
	spin_unlock(&mm->mmu_notifier_mm->lock);

	mm_drop_all_locks(mm);
	BUG_ON(atomic_read(&mm->mm_users) <= 0);
	return 0;

out_clean:
	kfree(mmu_notifier_mm);
	return ret;
}